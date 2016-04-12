#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

#include <map>
#include <string>
#include <cassert>

namespace netlicensing {

    /**
    * @brief Trivial generic context based on std::map like in Java client
    */
    template<class T>
    class context {
    private:
        std::map<std::string, T>    contextMap;
    public:

        context<T>& set_value(const std::string& key, const T& value) {
            contextMap.insert(std::make_pair(key, value));
            return *this;
        }

        bool contains(const std::string& key) const {
            return contextMap.find(key) != contextMap.end();
        }

        const T& get_value(const std::string& key) const {
            assert(contains(key));
            std::map<std::string, T>::const_iterator itr = contextMap.find(key);
            return itr->second;
        }
    };

    /**
    * @brief String context
    */
    typedef context<std::string> string_context;
}

#endif //__CONTEXT_HPP__