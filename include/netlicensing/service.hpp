#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#include <string>
#include <list>
#include <stdexcept>

namespace netlicensing {

    enum RequestType { GET, POST, PUT, DEL };

    /**
    *   dummy service class
    */
    class service {
        public:
            typedef std::list<std::pair<std::string, std::string> > request_params;

            service();

            ~service();

            static std::string get(const std::string &endpoint)  { 
                return instance().get_(endpoint); 
            }

            static std::string post(const std::string &endpoint, const std::string &body) {
                return instance().post_(endpoint, body);
            }

            static std::string put(const std::string &endpoint, const std::string &body) {
                return instance().put_(endpoint, body);
            }

            static std::string del(const std::string &endpoint) {
                return instance().del_(endpoint);
            }

            static std::string escape(const std::string &value) {
                return instance().escape_(value);
            }

            static std::string query_param(const std::string &url, 
                const std::string &param, 
                const std::string &value) {
                return instance().query_param_(url, param, value);
            }

            static std::string url() {
                return instance().url_;
            }

            static std::string url(const std::string &endpoint) {
                return instance().url_ + endpoint;
            }

            static std::string set_url(const std::string &url) {
                return instance().url_ = url;
            }

            static std::string proxy() {
                return instance().proxy_;
            }

            static std::string set_proxy(const std::string &proxy) {
                return instance().proxy_ = proxy;
            }

            static void clear_proxy() {
                instance().read_environment_proxy();
            }

            static std::string username() {
                return instance().username_;
            }

            static std::string set_username(const std::string &username) {
                return instance().username_ = username;
            }

            static std::string password() {
                return instance().password_;
            }

            static std::string set_password(const std::string &password) {
                return instance().password_ = password;
            }

    private:
        std::string url_;
        std::string proxy_;
        std::string username_;
        std::string password_;
        static const char *user_agent_;
        static const char *content_type_;
        void *curl_handle_;

        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
        service(service const &);            // Don't Implement
        void operator=(service const &); // Don't implement

                                     /**
                                     * Return the singleton instance
                                     */
        static service& instance() {
            static service instance;  // Guaranteed to be destroyed, instantiated on first use
            return instance;
        }

        // Curl read callback function
        std::string send_request(const RequestType &type, const std::string &endpoint, const std::string &body) const;

        // Curl write callback function
        static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

        // Curl read callback function
        static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

        // Check whether an error occurred
        static void check_http_error(const RequestType &type, const std::string &endpoint, long &http_code, const std::string &response_body);

        // Get environment proxy into proxy_
        void read_environment_proxy();

        // Request methods
        std::string get_(const std::string &endpoint) const;
        std::string post_(const std::string &endpoint, const std::string &body) const;
        std::string put_(const std::string &endpoint, const std::string &body) const;
        std::string del_(const std::string &endpoint) const;

        // String methods
        std::string escape_(const std::string &value) const;
        std::string query_param_(const std::string &url, const std::string &param, const std::string &value) const;
    };

    class ServiceError : public std::runtime_error {
    private:
        int m_code;
    public:
        ServiceError(const std::string& str, int code) : std::runtime_error(str), m_code(code) {}
    };

    class ResponseError : public ServiceError {
    public:
        ResponseError(const std::string& str, int code, const std::string&) : ServiceError(str, code) {}
    };

    class BadRequestError : public ServiceError {
    public:
        BadRequestError(const std::string& str) : ServiceError(str, 0) {}
    };

    class ValidationError : public ServiceError {
    public:
        ValidationError(const std::string& str) : ServiceError(str, 0) {}
    };

    class AuthenticationError : public ServiceError {
    public:
        AuthenticationError() : ServiceError("", 0) { }
    };
};



#endif //__SERVICE_HPP__