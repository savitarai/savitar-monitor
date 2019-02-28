/**
 * @file        util_str.cpp
 * @brief       test util_str
 * @version     1.0
 * @date        01/16/2019 10:39:27 AM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include <iostream>

#include "util/util_str.h"


int main()
{
    std::cout<<savitar::util::UtilStr::Inst("   abEfg\t")->Trim().ToLower().Str()<<std::endl;
    std::cout<<savitar::util::UtilStr::Inst("abEfg")->ToUpper().Str()<<std::endl;
    std::cout<<savitar::util::UtilStr::Inst("")->Format("%d in %s", __LINE__, __FILE__).Str()<<std::endl;
    return 0;
}
