/**
 * @file        define.h
 * @brief       监控模块的公共定义
 * @version     1.0
 * @date        01/13/2019 11:56:39 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _MONITOR_COMMON_DEFINE_H_
#define _MONITOR_COMMON_DEFINE_H_

#include <cstdint>

namespace savitar 
{

namespace monitor
{

#define MONITOR_KEY 0x170209
//TODO:支持多种监控数据类型

//支持的最大ID数，根据业务需求可以修改
#ifndef MAX_ATTR_ID
#define MAX_ATTR_ID 100000
#endif

#ifndef RESERVE_MIN_CNT 
#define RESERVE_MIN_CNT 3
#endif

#define USED_FLAG 255

#pragma pack(1)

struct MonitorHead
{
    int min_comm_attr_id_;      ///<最大的Comm属性ID
    int max_comm_attr_id_;      ///<最大的Comm属性ID
    int min_stat_attr_id_;      ///<最大的统计属性id
    int max_stat_attr_id_;      ///<最大的统计属性id
    int reserve_[14];           ///<保留字段，供扩展
};

/*分钟数据*/
struct CommMinData
{
    int min_;               ///<分钟seq,(unix_time(sec)/60)
    int64_t value_;         ///<value
};


/** 
 * @brief       通用属性上报
 */
struct CommAttr
{
    int usedflag_;                  ///<是否正在使用, 如果在使用，为USED_FLAG, 否则没用到
    int attr_id_;                   ///<属性ID，在这里主要是为了方便访问
    int update_time_;               ///<更新index时间
    int index_;                     ///<指定当前分钟用的是data_中哪个数据
    CommMinData data_[RESERVE_MIN_CNT]; ///<保留最近RESERVE_MIN_CNT分钟的数据，index指定当前分钟
};


/**
 * @name    StatMinData
 * @brief   分钟内统计值，支持最大值(max)，最小值(min)，计算(count)，总计(sum), 平均值(sum/count)
 */
struct StatMinData
{
    int min_;               ///<分钟seq,(unix_time(sec)/60)
    int64_t min_val_;       ///<min value
    int64_t max_val_;       ///<max value
    int64_t count_;         ///<count value
    int64_t sum_val_;       ///<sum
    int reserve_[7];         ///<保留字段，供后续添加新字段用
};
struct StatAttr
{
    int usedflag_;                      ///< 是否正在使用, 如果在使用，为USED_FLAG, 否则没用到
    int attr_id_;                       ///<属性ID，在这里主要是为了方便访问
    int update_time_;                   ///<更新index时间
    int index_;                         ///<指向data_中当前使用的是哪一个数据
    StatMinData data_[RESERVE_MIN_CNT];
};

struct MonitorBody
{
    CommAttr commattr_[MAX_ATTR_ID];    ///<常规监控属性
    StatAttr statattr_[MAX_ATTR_ID];    ///<统计监控属性
};


/**
 * @name    MonitorLayOut
 * @brief   监控信息共享内存布局
 */
struct MonitorLayout
{
    MonitorHead head_;     
    MonitorBody body_;      
};
#pragma pack()

}//monitor
}//poseidon


#endif
