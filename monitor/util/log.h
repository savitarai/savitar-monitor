/**
 * @file        log.h
 * @brief       日志输出接口
 * @version     1.0
 * @date        01/17/2019 11:43:37 AM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */
#ifndef _UTIL_LOG_H_
#define _UTIL_LOG_H_

#include <string>
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/OstreamAppender.hh>
#include <boost/serialization/singleton.hpp>
namespace savitar{
namespace util{

class Log:public boost::serialization::singleton<Log>
{
public:
    Log():init_(false),pcategory_(NULL)
    {
    }
    
    /**
     * @brief  初始化日志
     **/
    bool Init(const std::string conffile, const std::string category);

    
    /**
     * @brief  返回log4cpp的category
     **/
    log4cpp::Category & Category();

private:

    bool init_;
    log4cpp::Category * pcategory_;
};//class Log


}//namespace util
}//savitar

//初始化日志
#define LOG_INIT(conffile, category) savitar::util::Log::get_mutable_instance().Init(conffile, category)

//打印日志的宏
//因为log4cpp不支持打印行号、文件名等信息，这里用宏实现
//注意，LOG_XXXX(fmt, ...)这里的fmt不能是变量，必须是字符串,
//因为变量不支持默认连接操作,
//所以如果
//char * str="I am a str";
//LOG_DEBUG(str);    //error, because debug("%d in %s"str);编译不过去
//解决办法==>LOG_DEBUG("I am a str") or LOG_DEBUG("%s", str)
//
//注意：不直接调用debug&info，主要是因为函数调用的参数在调用前就会被执行，DEBUG的日志可能会比较多，影响线上执行的性能
//如 debug("%d", busy_func()); 虽然最后可能没有打印任何东西，但busy_func()都会被执行，用下面宏则不然。
#define LOG_DEBUG(fmt, a...) do{\
    auto &cate= savitar::util::Log::get_mutable_instance().Category();\
    if(cate.isDebugEnabled())\
    {\
        cate.debug("[%d in %s]" fmt, __LINE__, __FILE__, ##a);\
    }\
}while(0)

#define LOG_INFO(fmt, a...) savitar::util::Log::get_mutable_instance().Category().info("[%d in %s]" fmt, __LINE__, __FILE__, ##a)
#define LOG_NOTICE(fmt, a...) savitar::util::Log::get_mutable_instance().Category().notice("[%d in %s]" fmt, __LINE__, __FILE__, ##a)
#define LOG_WARN(fmt, a...) savitar::util::Log::get_mutable_instance().Category().warn("[%d in %s]" fmt, __LINE__, __FILE__, ##a)
#define LOG_ERROR(fmt, a...) savitar::util::Log::get_mutable_instance().Category().error("[%d in %s]" fmt, __LINE__, __FILE__, ##a)
#define LOG_FATAL(fmt, a...) savitar::util::Log::get_mutable_instance().Category().fatal("[%d in %s]" fmt, __LINE__, __FILE__, ##a)

#endif // _UTIL_LOG_H_

