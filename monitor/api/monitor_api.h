/**
 * @file        monitor_api.h
 * @brief       monitor API接口
 * @version     1.0
 * @date        01/14/2019 12:54:38 AM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */
#ifndef _MONITOR_API_MONITOR_API_H_
#define _MONITOR_API_MONITOR_API_H_

#include <boost/serialization/singleton.hpp>

namespace savitar 
{
namespace monitor
{

class MonitorLayout;
class Api:public boost::serialization::singleton<Api>
{
public:

    Api():init_(false)
    {
    }

    /**
     * @brief       初始化
     **/
    int Init();

    /**
     * @brief       属性上报add
     **/
    void MonAdd(int attr_id, int val);

    /**
     * @brief       属性上报set
     **/
    void MonSet(int attr_id, int val);


    /**
     * @brief               统计属性ID对应值的分布
     *
     * @param attr_id       [in],要上报的属性ID
     * @param val           [in],属性ID对应的值
     */
    void MonStat(int attr_id, int val);

private:

    bool init_;                     ///<是否初始化
    MonitorLayout * layout_;        ///<内存布局

};//Api
}//monitor
}//savitar

#define MON_ADD(attr, val) savitar::monitor::Api::get_mutable_instance().MonAdd(attr, val)
#define MON_SET(attr, val) savitar::monitor::Api::get_mutable_instance().MonSet(attr, val)
#define MON_STAT(attr, val) savitar::monitor::Api::get_mutable_instance().MonStat(attr, val)

#endif ///< _MONITOR_API_MONITOR_API_H_

