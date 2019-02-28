/**
 * @file        util_net.cpp
 * @brief       util net 实现
 * @version     1.0
 * @date        01/19/2019 04:56:05 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "util_net.h"

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <net/if.h>
#include <sys/ioctl.h>

namespace savitar {
namespace util {
int UtilNet::GetLocalIp(std::string &ip)
{
    int rt = 0;
    int sock = -1;
    do {
        struct ifreq ifr[32];
        struct ifconf ifc;
        int num;
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            rt = -1;
            break;
        }
        char ip_buf[64];
        int ip_size = 64;

        //获取网卡列表
        ifc.ifc_len = sizeof ifr;
        ifc.ifc_buf = (caddr_t)ifr;
        ifc.ifc_req = ifr;
        if (!ioctl(sock, SIOCGIFCONF, (char *)&ifc)) {
            // if 数目
            num = ifc.ifc_len / sizeof(struct ifreq);
            rt = -1; //默认找不到ip
            while (num >= 0) {
                if (!ioctl(sock, SIOCGIFADDR, (char *)&ifr[num])) {
                    memset(ip_buf, 0x00, 64);
                    snprintf(ip_buf, ip_size,
                             (char *)inet_ntoa(
                                 ((struct sockaddr_in *)(&ifr[num].ifr_addr))
                                     ->sin_addr));
                    //过滤lo地址
                    if (strncmp(ip_buf, "127", 3) != 0 &&
                        strncmp(ip_buf, "0.0.0.0", 7)) {
                        ip = ip_buf;
                        rt = 0;
                        break;
                    }
                }
                num--;
            }
        }
    } while (0);
    if (sock > 0) {
        close(sock);
    }
    return rt;
}

}
}
