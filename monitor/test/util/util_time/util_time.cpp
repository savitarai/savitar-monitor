/**
 * @file        util_time.cpp
 * @brief       
 * @version     1.0
 * @date        01/16/2019 12:22:18 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "util/util_time.h"
#include <iostream>

int main()
{
    std::cout<<savitar::util::UtilTime::Now()->Format("%Y%m%d")<<std::endl;
    std::cout<<savitar::util::UtilTime::Now()->Format()<<std::endl;
    std::cout<<savitar::util::UtilTime::MakeUtilTime("2017-01-01:121212")->Format("%Y%m%d")<<std::endl;
    return 0;
}
