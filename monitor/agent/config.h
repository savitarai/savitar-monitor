/**
 * @file        config.h
 * @brief       agent配置文件解析
 * @version     1.0
 * @date        01/15/2019 04:41:26 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */
#ifndef _AGENT_CONFIG_H_
#define _AGENT_CONFIG_H_

#include <boost/serialization/singleton.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "util/util_net.h"

namespace savitar {
namespace monitor {
class Config : public boost::serialization::singleton<Config> {
public:
    enum EC {
        EC_SUCCESS = 0,
        EC_REPARSE,
    };
    Config() : isparse_(false)
    {
    }
    ~Config()
    {
    }

    /**
     * @brief  解析配置文件
     * @return
     * @retval 0    成功
     * @retval -1   重复parse
     **/
    int Parse(const std::string &conf_file)
    {
        if (isparse_) {
            return -1;
        }

        boost::property_tree::ini_parser::read_ini(conf_file, pt_);
        conf_file_ = conf_file;
        isparse_ = true;
        return 0;
    }

    /**
     * @brief       日志的配置文件
     * @param def   in,缺省值
     * @return      返回日志的配置文件,失败则返回def的值
     **/
    const char *LogConf()
    {
        return pt_.get<std::string>("MonAgent.LogConf", "log.conf").c_str();
    }

    /**
     * @brief   日志的category
     * @param def   in,缺省值
     * @return      成功返回对应的值,失败则返回def的值
     */
    const char *LogCategory()
    {
        return pt_.get<std::string>("MonAgent.LogCategory", "agent").c_str();
    }

    const char * ReportUrl()
    {
        return pt_.get<std::string>("MonAgent.ReportUrl", nullptr).c_str();
    }

    /**
     * @brief       获取本地IP
     *
     */
    const char *LocalIp()
    {
        if (local_ip_.empty()) {
            local_ip_ = pt_.get<std::string>("MonAgent.LocalIp", "");
            if (local_ip_ == "") {
                if (util::UtilNet::GetLocalIp(local_ip_) != 0) {
                    local_ip_ = "127.0.0.1";
                }
            }
        }
        return local_ip_.c_str();
    }

private:
    boost::property_tree::ptree pt_;
    std::string conf_file_;
    std::string local_ip_;
    bool isparse_;
};
} // monitor
} // savitar

#endif //_AGENT_CONFIG_H_
