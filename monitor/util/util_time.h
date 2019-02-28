/**
 * @file        util_time.h
 * @brief       
 * @version     1.0
 * @date        01/15/2019 07:00:00 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _UTIL_TIME_H_
#define _UTIL_TIME_H_

#include <ctime>
#include <memory>

namespace savitar
{
namespace util
{
/**
 * @brief   时间操作的类
 */
class UtilTime
{
public:
    static constexpr const char * default_fmt(){ return "%Y-%m-\%d:%H%M%S"; }

    /**
     * @brief   通过time_t 创建UtilTime对象
     */
    UtilTime(time_t t)
    {
        t_=t;
    }


    /**
     * @brief   通过字符串创建UtilTime对象
     */
    UtilTime(const char * timestr, const char * fmt=default_fmt())
    {
        struct tm timeinfo;
        strptime(timestr, fmt, &timeinfo);
        t_=mktime(&timeinfo);
    }

    /**
     * @brief 返回制定格式的时间格式
     *
     * @param fmt   in,格式如["%Y%m%d-%H%M%S"]
     *
     * @return  返回制定的字符
     */
    std::string Format(const char * fmt=default_fmt())
    {
        char str[32];
        struct tm timeinfo;
        localtime_r(&t_, &timeinfo);
        strftime(str, 32, fmt, &timeinfo);
        return std::string(str);
    }


    /**
     * @brief           创建一个表示当前时间的UtilStr
     */
    static std::shared_ptr<UtilTime> Now()
    {
        return std::make_shared<UtilTime>(time(NULL));
    }

    static std::shared_ptr<UtilTime> MakeUtilTime(const char * strtime, const char * fmt=default_fmt() )
    {
        return std::make_shared<UtilTime>(strtime, fmt);
    }


private:
    time_t t_;

};//UtilTime
}//util
}//savitar
#endif
