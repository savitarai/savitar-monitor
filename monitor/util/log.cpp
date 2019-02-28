/**
 * @file        log.cpp
 * @brief       util-log实现
 * @version     1.0
 * @date        01/17/2019 12:02:16 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "log.h"

namespace savitar{
namespace util{

bool Log::Init(const std::string conffile, const std::string category )
{
    if(init_)
    {
        fprintf(stderr, "repeat initialization\n");
        return false;
    }
    try
    {
        log4cpp::PropertyConfigurator::configure(conffile);
        pcategory_=&( log4cpp::Category::getInstance(category) );
        init_=true; 
        return true;
    }catch (log4cpp::ConfigureFailure& f)
    {
        fprintf(stderr, "log4cpp parse configure error\n");
        return false;
    }
}

log4cpp::Category & Log::Category()
{
    if(!init_)
    {
        fprintf(stderr, "[%d in %s]LOG_INIT isn't called, init log use default\n", __LINE__, __FILE__);
        log4cpp::OstreamAppender* osAppender =new log4cpp::OstreamAppender("osAppender",&std::cout);
        osAppender->setLayout(new log4cpp::BasicLayout());
                  
        pcategory_=&(log4cpp::Category::getRoot());
        pcategory_->addAppender(osAppender);
        pcategory_->setPriority(log4cpp::Priority::DEBUG);
        init_=true;
    }
    return *pcategory_;
}

}//util
}//savitar


