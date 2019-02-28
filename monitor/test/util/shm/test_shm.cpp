/**
 * @file        test_shm.cpp
 * @brief       测试util shm
 * @version     1.0
 * @date        01/16/2019 09:34:03 AM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */


#include "util/shm.h"



int main()
{
    savitar::util::Shm::ShmCreate(0x1234, 1024);
    return 0;
}

