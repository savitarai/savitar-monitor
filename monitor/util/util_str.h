/**
 * @file        util_str.h
 * @brief       
 * @version     1.0
 * @date        01/15/2019 06:48:04 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _UTIL_STR_H_
#define _UTIL_STR_H_

#include <algorithm>
#include <cstdarg>
#include <string>
#include <cstdio>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace savitar
{
namespace util
{
class UtilStr
{
public:
    UtilStr()
    {
    }

    UtilStr(std::string str)
    {
        str_=str;
    }

    std::string& Str()
    {
        return str_;
    }
    
    UtilStr& Replace(char oldchar, char newchar)
    {
        std::replace(str_.begin(), str_.end(), oldchar, newchar);
        return *this;
    }

    UtilStr& Format(const char * fmt, ...)
    {
        char buf[4096];
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, 4096, fmt, ap);
        va_end(ap);
        str_=buf;
        return *this;
    }

    UtilStr& ToUpper()
    {
        boost::to_upper(str_);
        return *this;
    }
    UtilStr& ToLower()
    {
        boost::to_lower(str_);
        return *this;

    }
    UtilStr& Trim()
    {
        boost::trim(str_);
        return *this;
    }

    UtilStr& TrimRight()
    {
        boost::trim_right(str_);
        return *this;
    }

    UtilStr& TrimLeft()
    {
        boost::trim_left(str_);
        return *this;
    }

    static std::shared_ptr<UtilStr> Inst(std::string str)
    {
        return std::make_shared<UtilStr>(str);
    }


private:
    std::string str_;
};

}
}
#endif  //_UTIL_STR_H_

