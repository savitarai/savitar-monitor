/**
 * @file        data_processor_inf.h
 * @brief       数据处理接口
 * @version     1.0
 * @date        03/15/2019 07:56:55 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _AGENT_DATA_PROCESSOR_INF_H_
#define _AGENT_DATA_PROCESSOR_INF_H_

namespace savitar {
namespace monitor {

/**
 * @brief       监控数据处理接口
 */
class DataProcessorInf
{
public:
    /**
     * @brief       处理接受到的监控数据(默认什么都不做，子类进行实现)
     *
     * @param data  [in], 待处理的数据,JSON格式, 参照api说明
     * @return      成功返回0， 否则返回其他的错误码
     */
    virtual int Proc(const char * data)
    {
        return 0;
    }

};//DataProcessorInf

}///monitor
}///savitar



#endif //_AGENT_DATA_PROCESSOR_INF_H_


