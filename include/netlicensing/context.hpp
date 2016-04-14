#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

#include <string>
#include <list>

namespace netlicensing {

    /**
    * @brief configure your connection to rest server using this Context class
    *    
    */
    class context {
    public:
        typedef std::list<std::pair<std::string, std::string> > parameters_type;
        context();
        ~context();

        void set_username(const std::string&);
        void set_password(const std::string&);
        void set_base_url(const std::string&);
        std::string username() const;
        std::string password() const;
        std::string base_url() const;

        std::string post(const std::string& endpoint, const parameters_type& params);
    private:
        context(const context&);
        context& operator=(const context&);
        class network_service;
        network_service* m_instance;
        std::string m_username;
        std::string m_password;
        std::string m_base_url;
    };

}

#endif //__CONTEXT_HPP__