/**
 * @file        main.cpp
 * @brief       agent 主程序
 * @version     1.0
 * @date        01/17/2019 05:17:38 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "mon_agent.h"
#include "config.h"
#include "util/log.h"
#include "util/util_daemon.h"
#include "util/util_time.h"

void usage(const char *basename)
{
    fprintf(stderr, "usage: %s config_file\n", basename);
}

int main(int argc, char *argv[])
{
    int rt = 0;
    do {
        if (argc < 2) {
            usage(argv[0]);
            return -1;
        }

        //解析配置文件        
        rt = savitar::monitor::Config::get_mutable_instance().Parse(argv[1]);
        if(rt != 0)
        {
            fprintf(stderr, "config file parse error[%d]\n", rt);
            break;
        }

        //放到后台
        savitar::util::UtilDaemon::Daemonize();

        if(!savitar::util::UtilDaemon::LockPidfile("./mon_agent.pid"))
        {
            fprintf(stderr, "已经有进程在跑，不能重复起进程\n", rt);
            rt=-1;
            break;
        }

        //初始化日志
        if(!LOG_INIT(savitar::monitor::Config::get_mutable_instance().LogConf(), savitar::monitor::Config::get_mutable_instance().LogCategory()))
        {
            fprintf(stderr, "LOG_INIT return false\n");
            rt=-1;
            break;
        }
        LOG_INFO("mon_agent start at %s", savitar::util::UtilTime::Now()->Format().c_str());
        
        savitar::monitor::Agent::get_mutable_instance().Init();
        savitar::monitor::Agent::get_mutable_instance().Run();
    } while (0);
    return rt;
}
