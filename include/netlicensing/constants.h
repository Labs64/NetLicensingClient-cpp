#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <list>
#include <string>

namespace netlicensing {
    static const char* ID      = "id";
    static const char* ACTIVE  = "active";
    static const char* NUMBER  = "number";
    static const char* NAME    = "name";
    static const char* VERSION = "version";
    static const char* DELETED = "deleted";
    static const char* CASCADE = "forceCascade";
    static const char* PRICE   = "price";
    static const char* DISCOUNT = "discount";
    static const char* CURRENCY = "currency";
    static const char* IN_USE  = "inUse";
    static const char* FILTER  = "filter";
    static const char* BASE_URL = "baseUrl";
    static const char* USERNAME = "username";
    static const char* PASSWORD = "password";
    static const char* SECURITY_MODE = "securityMode";
    static const char* PROP_ID     = "ID";
    static const char* PROP_TTL    = "TTL";

    typedef std::list<std::pair<std::string, std::string> > parameters_type;
}

#endif //__CONSTANTS_H__