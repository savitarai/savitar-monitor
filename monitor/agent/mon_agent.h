/**
 * @file        mon_agent.h
 * @brief       监控agent实现代码
 * @version     1.0
 * @date        01/17/2019 05:45:59 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _AGENT_MON_AGENT_H_
#define _AGENT_MON_AGENT_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "api/layout_access.h"
#include "boost/serialization/singleton.hpp"

namespace savitar {
namespace monitor {

class Agent : public boost::serialization::singleton<Agent> {

public:

    /**
     * @brief           初始化
     *
     * @return          成功返回0, 否则返回对应的错误码
     */
    int Init();

    /**
     * @brief   运行，这个函数正常情况会不会返回
     *
     * @return  正常情况下不会返回
     */
    int Run();

private:

    /**
     * @brief           收集监控数据
     *
     * @param min       in, 收集的分钟时间
     * @param data      out,返回收集后的内容
     *
     * @return          返回errcode
     * @retval 0        成功
     * @retval <0       失败     
     */
    int CollectData(int min, std::string & data);

    /**
     * @brief           属性上报
     *
     * @param data      in,report的报文
     *
     * @return          返回errcode
     * @retval 0        成功
     * @retval <0       失败     
     */
    int Report(const std::string & data);

private:
    savitar::monitor::LayoutAccessor accessor_; ///<用于访问本地共享内存
    std::string hostname_;          ///<主机名
    std::string hostip_;            ///<主机IP
    std::string report_url_;        ///<API URL

};//Agent

} // monitor
} // savitar
#endif //_AGENT_MON_AGENT_H_
