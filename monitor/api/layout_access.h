/**
 * @file        Layout_accessor.h
 * @brief       内存Layout访问器
 * @version     1.0
 * @date        01/18/2019 11:31:40 AM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _LAYOUT_ACCESS_H_
#define _LAYOUT_ACCESS_H_
#include <cstdlib>
#include <string.h>
#include <iterator>
#include <memory>
#include "common/define.h"
#include "util/shm.h"

namespace savitar {
namespace monitor {
class LayoutAccessor {
public:
    class CommAttrList {
    public:
        /**
         * @brief   CommAttr迭代器
         */
        class Iterator
            : public std::iterator<std::forward_iterator_tag, CommAttr> {

        public:
            Iterator(MonitorLayout *layout, int idx = 0)
                : idx_(idx), layout_(layout)
            {
            }
            Iterator(const Iterator &it) : idx_(it.idx_), layout_(it.layout_)
            {
            }

            bool operator==(Iterator it)
            {
                return (it.layout_ == layout_) && (it.idx_ == idx_);
            }

            bool operator!=(Iterator it)
            {
                return !(operator==)(it);
            }

            /**
             * @brief   ++it
             */
            Iterator &operator++()
            {
                do {
                    if (idx_ > layout_->head_.max_comm_attr_id_) {
                        break;
                    }
                    ++idx_;
                } while (layout_->body_.commattr_[idx_].usedflag_ != USED_FLAG);
                return *this;
            }

            /**
             * @brief   it++
             */
            Iterator operator++(int)
            {
                auto tmp = *this;
                (operator++)();
                return tmp;
            }

            reference operator*()
            {
                return layout_->body_.commattr_[idx_];
            }

            pointer operator->()
            {
                return &(operator*)();
            }

        private:
            int idx_;               // layout中的索引
            MonitorLayout *layout_; //指向layout的指针
        };

        CommAttrList() : layout_(nullptr)
        {
        }

        explicit CommAttrList(MonitorLayout *layout) : layout_(layout)
        {
        }

        Iterator begin()
        {
            if (empty()) {
                return end();
            } else {
                return Iterator(layout_, layout_->head_.min_comm_attr_id_);
            }
        }
        Iterator end()
        {
            return Iterator(layout_, layout_->head_.max_comm_attr_id_ + 1);
        }
        bool empty()
        {
            return (layout_->head_.max_comm_attr_id_ < 0);
        }

    private:
        MonitorLayout *layout_; //指向layout的指针
    };

    class StatAttrList {

    public:
        /**
         * @brief   StatAttr迭代器
         */
        class Iterator
            : public std::iterator<std::forward_iterator_tag, StatAttr> {

        public:
            Iterator(MonitorLayout *layout, int idx = 0)
                : idx_(idx), layout_(layout)
            {
            }
            Iterator(const Iterator &it) : idx_(it.idx_), layout_(it.layout_)
            {
            }

            bool operator==(Iterator it)
            {
                return (it.layout_ == layout_) && (it.idx_ == idx_);
            }

            bool operator!=(Iterator it)
            {
                return !(operator==)(it);
            }

            /**
             * @brief   ++it
             */
            Iterator &operator++()
            {
                do {
                    if (idx_ > layout_->head_.max_stat_attr_id_) {
                        break;
                    }
                    ++idx_;
                } while (layout_->body_.statattr_[idx_].usedflag_ != USED_FLAG);
                return *this;
            }

            /**
             * @brief   it++
             */
            Iterator operator++(int)
            {
                auto tmp = *this;
                (operator++)();
                return tmp;
            }

            reference operator*()
            {
                return layout_->body_.statattr_[idx_];
            }

            pointer operator->()
            {
                return &(operator*)();
            }

        private:
            int idx_;               // layout中的索引
            MonitorLayout *layout_; //指向layout的指针
        };                          // Iterator

        StatAttrList() : layout_(nullptr)
        {
        }
        explicit StatAttrList(MonitorLayout *layout) : layout_(layout)
        {
        }

        Iterator begin()
        {
            if (empty()) {
                return end();
            } else {
                return Iterator(layout_, layout_->head_.min_stat_attr_id_);
            }
        }
        Iterator end()
        {
            return Iterator(layout_, layout_->head_.max_stat_attr_id_ + 1);
        }
        bool empty()
        {
            return (layout_->head_.max_stat_attr_id_ < 0);
        }

    private:
        MonitorLayout *layout_; //指向layout的指针
    };                          // StatAttrList

    explicit LayoutAccessor(int key = MONITOR_KEY)
    {
        layout_ =
            (MonitorLayout *)util::Shm::ShmAttach(key, sizeof(MonitorLayout));
        if (layout_ == nullptr) {
            layout_ = (MonitorLayout *)util::Shm::ShmCreate(
                key, sizeof(MonitorLayout));
            //            memset((void *)&(layout_->head_), 0x00,
            // sizeof(MonitorHead));
            layout_->head_.max_comm_attr_id_ = -1;
            layout_->head_.min_comm_attr_id_ = MAX_ATTR_ID;
            layout_->head_.max_stat_attr_id_ = -1;
            layout_->head_.min_stat_attr_id_ = MAX_ATTR_ID;
        }
        comm_attr_list_ = CommAttrList(layout_);
        stat_attr_list_ = StatAttrList(layout_);
    }

    explicit LayoutAccessor(MonitorLayout *layout)
        : layout_(layout), comm_attr_list_(layout), stat_attr_list_(layout)
    {
    }

    ~LayoutAccessor()
    {
    }

    StatAttrList &StatAttrs()
    {
        return stat_attr_list_;
    }

    CommAttrList &CommAttrs()
    {
        return comm_attr_list_;
    }

private:
    MonitorLayout *layout_;
    CommAttrList comm_attr_list_;
    StatAttrList stat_attr_list_;
}; // LayoutAccessor
}
}
#endif //_MONITOR_LAYOUT_H_
