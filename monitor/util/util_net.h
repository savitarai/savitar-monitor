/**
 * @file        util_net.h
 * @brief       util 网络相关操作
 * @version     1.0
 * @date        01/17/2019 12:31:07 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _UTIL_NET_H_
#define _UTIL_NET_H_
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace savitar {
namespace util {
class UtilNet {
public:

    /**
     * @brief   获取本地IP(排除127.0.0.1, 如果本机有多个网卡，返回第一个)
     *
     * @param ip    out,返回得到的ip
     *
     * @return  成功返回0， 否则返回对应的错误码
     */
    static int GetLocalIp(std::string &ip);

    /**
     * @brief       获取主机名
     *
     * @return
     *
     * @retval hostname 主机名
     * @retval nullptr  失败 
     */
    static const char * GetHostName()
    {
        static char hostname[256];
        gethostname(hostname, 256);
        return hostname;
    }

};

#define MakeAddr(toaddr, ip, port)                                             \
    do {                                                                       \
        toaddr.sin_family = AF_INET;                                           \
        toaddr.sin_port = htons(port);                                         \
        inet_aton(ip, &toaddr.sin_addr);                                       \
    } while (0)

} // namespace util
} // namespace savitar

#endif //_UTIL_NET_H_
