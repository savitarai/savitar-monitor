/**
 * @file        monitor_api.cpp
 * @brief       监控API实现
 * @version     1.0
 * @created     01/14/2019 01:15:10 AM
 * @compiler    gcc/g++
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "monitor_api.h"
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include "util/shm.h"
#include "common/define.h"

namespace savitar {
namespace monitor {

/**
 * @brief       初始化
 **/
int Api::Init()
{
    int rt = 0;
    do {
        layout_ = (MonitorLayout *)util::Shm::ShmAttach(
            MONITOR_KEY, sizeof(MonitorLayout), 0666);
        if (layout_ == NULL) {
            rt = -1;
            break;
        }
        init_ = true;
    } while (0);
    return rt;
}

/**
 * @brief       属性上报add
 **/
void Api::MonAdd(int attr_id, int val)
{
    if (attr_id < 0 || attr_id > MAX_ATTR_ID || val < 0) {
        return;
    }
    if (!init_) {
        if (Init() != 0) {
            return;
        }
    }

    CommAttr &attr = layout_->body_.commattr_[attr_id];
    if (attr.usedflag_ != USED_FLAG) {
        attr.usedflag_ = USED_FLAG;
        attr.attr_id_ = attr_id;
        attr.index_ = 0;
        attr.data_[0].min_ = time(NULL) / 60;
        attr.data_[0].value_ = 0;
    }
    if (attr_id > layout_->head_.max_comm_attr_id_) {
        layout_->head_.max_comm_attr_id_ = attr_id;
    }
    if(attr_id < layout_->head_.min_comm_attr_id_)
    {
        layout_->head_.min_comm_attr_id_=attr_id;
    }


    //先取出index字段,保证下面代码都是在同一个index里面操作的,注意:attr.index_有可能被其他进程修改
    int index=attr.index_;

    CommMinData &mindata = attr.data_[index];
    __sync_fetch_and_add(&mindata.value_, (int64_t)val);
}

/**
 * @brief       属性上报set
 **/
void Api::MonSet(int attr_id, int val)
{
    if (attr_id < 0 || attr_id > MAX_ATTR_ID || val < 0) {
        return;
    }
    if (!init_) {
        if (Init() != 0) {
            return;
        }
    }

    CommAttr &attr = layout_->body_.commattr_[attr_id];
    if (attr.usedflag_ != USED_FLAG) {
        attr.usedflag_ = USED_FLAG;
        attr.attr_id_ = attr_id;
        attr.index_ = 0;
        attr.data_[0].min_ = time(NULL) / 60;
        attr.data_[0].value_ = 0;
    }
    if (attr_id > layout_->head_.max_comm_attr_id_) {
        layout_->head_.max_comm_attr_id_ = attr_id;
    }
    if(attr_id < layout_->head_.min_comm_attr_id_)
    {
        layout_->head_.min_comm_attr_id_=attr_id;
    }

    //先取出index字段,保证下面代码都是在同一个index里面操作的,注意:attr.index_有可能被其他进程修改
    int index=attr.index_;
    CommMinData &mindata = attr.data_[index];
    mindata.value_ = (int64_t)val;
}

void Api::MonStat(int attr_id, int val)
{
    if (attr_id < 0 || attr_id > MAX_ATTR_ID || val < 0) {
        return;
    }
    if (!init_) {
        if (Init() != 0) {
            return;
        }
    }

    StatAttr &attr = layout_->body_.statattr_[attr_id];
    if (attr.usedflag_ != USED_FLAG) {
        attr.usedflag_ = USED_FLAG;
        attr.attr_id_ = attr_id;
        attr.index_ = 0;
        attr.data_[0].min_ = time(NULL) / 60;
        attr.data_[0].min_val_ = 0;
        attr.data_[0].max_val_ = 0;
        attr.data_[0].count_ = 0;
        attr.data_[0].sum_val_ = 0;
    }
    if (attr_id > layout_->head_.MonitorHead::max_stat_attr_id_) {
        layout_->head_.MonitorHead::max_stat_attr_id_ = attr_id;
    }
    if (attr_id < layout_->head_.MonitorHead::min_stat_attr_id_) {
        layout_->head_.MonitorHead::min_stat_attr_id_ = attr_id;
    }

    //先取出index字段,保证下面代码都是在同一个index里面操作的,注意:attr.index_有可能被其他进程修改
    int index=attr.index_;
    StatMinData &mindata = attr.data_[index];


    //CAS
    do {
        int64_t old_val = mindata.max_val_;
        if (val > old_val || mindata.count_ == 0) {
            if (!__sync_bool_compare_and_swap(&mindata.max_val_, old_val,
                                              (int64_t)val)) {
                continue;
            }
        }
    } while (0);

    //CAS
    do {
        int64_t old_val = mindata.min_val_;
        if (val < old_val || mindata.count_ == 0) {
            if (!__sync_bool_compare_and_swap(&mindata.min_val_, old_val,
                                              (int64_t)val)) {
                continue;
            }
        }
    } while (0);

    __sync_fetch_and_add(&mindata.sum_val_, (int64_t)val);
    __sync_fetch_and_add(&mindata.count_, (int64_t)1);
}

} // monitor
} // savitar
