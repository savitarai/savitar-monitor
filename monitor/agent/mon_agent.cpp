/**
 * @file        mon_agent.cpp
 * @brief       Agent实现
 * @version     1.0
 * @date        01/17/2019 06:21:31 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "mon_agent.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "util/shm.h"
#include "util/log.h"
#include "util/log.h"
#include "config.h"

namespace savitar {
namespace monitor {

int Agent::Init()
{
    int rt = 0;
    do {
        hostname_=util::UtilNet::GetHostName();
        hostip_=Config::get_mutable_instance().LocalIp();
        report_url_=Config::get_mutable_instance().ReportUrl();
    } while (0);
    return rt;
}

int Agent::Run()
{
    int rt = 0;
    do {
        do {
            time_t now = time(NULL);
            int sleep_time = 60 - (now % 60);
            sleep(sleep_time); // sleep到下一个时间整点

            int time_min = now / 60; // sleep前的分钟

            //收集数据
            std::string data;
            rt = CollectData(time_min, data);
            if (rt != 0) {
                LOG_ERROR("CollectData return error[%d]\n", rt);
                continue;
            }
            LOG_DEBUG("data[%s]\n",data.c_str());

            //数据上报
            rt = Report(data);
            if (rt != 0) {
                LOG_ERROR("Report return error[%d]\n", rt);
                continue;
            }
        } while (1);
    } while (0);
    return rt;
}

template<typename T>
int update_index(T & t)
{
    int old_index=t.index_;
    int new_index=(t.index_+1)%RESERVE_MIN_CNT;
    memset(&(t.data_[new_index]), 0x00, sizeof(decltype(t.data_[new_index])));
    t.index_=new_index;
    return old_index;
}

int Agent::CollectData(int min, std::string &data)
{
    int rt = 0;
    do {
        rapidjson::Document doc;
        doc.SetObject();
        doc.AddMember("seq", min, doc.GetAllocator());
        doc.AddMember("hostname", rapidjson::Value(hostname_.c_str(), hostname_.length()), doc.GetAllocator());
        doc.AddMember("hostip", rapidjson::Value(hostip_.c_str(), hostip_.length()), doc.GetAllocator());
        doc.AddMember("time_min", min, doc.GetAllocator());

        ///{{{"commattr"
        rapidjson::Value arraycomm;
        arraycomm.SetArray();
        auto &commattr = accessor_.CommAttrs();
        for (auto &item : commattr) {
            rapidjson::Value v;
            v.SetObject();
            //赋值
            
            //先更新index,再从老的读取数据
            int old_index=update_index(item);
            usleep(1);  //让其他获取old_index的进程有时间完成后面的操作
            v.AddMember("attrid", item.attr_id_, doc.GetAllocator());
            v.AddMember("value", item.data_[old_index].value_,doc.GetAllocator());
            arraycomm.PushBack(v, doc.GetAllocator());
        }
        doc.AddMember("commattr", arraycomm, doc.GetAllocator());
        ///}}}"commattr"
        
        
        ///{{{"statattr"
        rapidjson::Value arraystat;
        arraystat.SetArray();
        auto &statattr = accessor_.StatAttrs();
        for (auto &item : statattr) {
            rapidjson::Value v;
            v.SetObject();
            //赋值
            
            //先更新index,再从老的读取数据
            int old_index=update_index(item);
            usleep(1);  //让其他获取old_index的进程有时间完成后面的操作
            v.AddMember("attrid", item.attr_id_, doc.GetAllocator());
            v.AddMember("min", item.data_[old_index].min_val_, doc.GetAllocator());
            v.AddMember("max", item.data_[old_index].max_val_, doc.GetAllocator());
            v.AddMember("count", item.data_[old_index].count_, doc.GetAllocator());
            v.AddMember("sum", item.data_[old_index].sum_val_, doc.GetAllocator());
            arraystat.PushBack(v, doc.GetAllocator());
        }
        doc.AddMember("statattr", arraystat, doc.GetAllocator());
        ///}}}"statattr"
        
        //TODO:更新index
        
        //把document转为字符串
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> wr(buffer);
        doc.Accept(wr);
        data=buffer.GetString();
    } while (0);
    return rt;
}

int Agent::Report(const std::string &data)
{
    int rt=0;
    do{
    }while(0);
    return rt;
}

} // monitor

} // savitar
