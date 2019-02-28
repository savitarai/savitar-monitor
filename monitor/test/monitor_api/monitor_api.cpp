/**
 * @file        monitor_api.cpp
 * @brief       测试monitor_api
 * @version     1.0
 * @date        01/18/2019 07:24:27 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include <string.h>
#include <iostream>
#include "api/monitor_api.h"

void usage(char * basename)
{
//    fprintf(stderr, "%s attr_id val\n", basename )
    std::cerr<<"usage:"<<basename<<"[mon_add|mon_set|mon_stat] attrid val"<<std::endl;
}

int main(int argc, char * argv[])
{
    if(argc < 4)
    {
        usage(argv[0]);
        return -1;
    }
    int id=atoi(argv[2]);
    int val=atoi(argv[3]);

    if(strcmp(argv[1], "mon_add")==0)
    {
        MON_ADD(id, val);
    }else if(strcmp(argv[1], "mon_set")==0)
    {
        MON_SET(id, val);
    }else
    {
        MON_STAT(id, val);
    }
    return 0;
}
