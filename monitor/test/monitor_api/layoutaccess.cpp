/**
 * @file        layoutaccess.cpp
 * @brief       测试LayoutAccess功能
 * @version     1.0
 * @date        01/18/2019 07:11:26 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include <iostream>

#include "api/layout_access.h"


int main()
{
    savitar::monitor::LayoutAccessor acc;
    auto& commattr=acc.CommAttrs();
    for(auto & x:commattr)
    {
        std::cout<<"{";
        std::cout<<"attr_id:"<<x.attr_id_<<",";
        std::cout<<"index:"<<x.index_<<",";
        std::cout<<"update_time:"<<x.update_time_<<",";
        std::cout<<"usedflag:"<<x.usedflag_<<",";
        std::cout<<"min:"<<x.data_[x.index_].min_<<",";
        std::cout<<"value:"<<x.data_[x.index_].value_;
        std::cout<<"}"<<std::endl;
    }
    std::cout<<"-------------------------------------"<<std::endl;
    auto & statattr=acc.StatAttrs();
    for(auto & x:statattr)
    {
        std::cout<<"{";
        std::cout<<"attr_id:"<<x.attr_id_<<",";
        std::cout<<"index:"<<x.index_<<",";
        std::cout<<"update_time:"<<x.update_time_<<",";
        std::cout<<"usedflag:"<<x.usedflag_<<",";
        std::cout<<"min:"<<x.data_[x.index_].min_<<",";
        std::cout<<"min_val_:"<<x.data_[x.index_].min_val_<<",";
        std::cout<<"max_val_:"<<x.data_[x.index_].max_val_<<",";
        std::cout<<"count_:"<<x.data_[x.index_].count_<<",";
        std::cout<<"sum_:"<<x.data_[x.index_].sum_val_<<",";
        std::cout<<"mean_:"<<(double)x.data_[x.index_].sum_val_/x.data_[x.index_].count_<<",";
        std::cout<<"}"<<std::endl;
    }
    return 0;
}
