/**
 * @file        data_processor_file.h
 * @brief       监控数据处理（写文件）
 * @version     1.0
 * @date        03/15/2019 08:09:31 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */
#ifndef _AGENT_DATA_PROCESSOR_FILE_H_
#define _AGENT_DATA_PROCESSOR_FILE_H_

#include "data_processor_inf.h"

namespace savitar{
namespace monitor{
class DataProcessorFile: public DataProcessorInf 
{
public:
    /**
     * @brief       处理接受到的监控数据
     *
     * @param data  [in], 待处理的数据,JSON格式, 参照api说明
     * @return      成功返回0， 否则返回其他的错误码
     */
    virtual int Proc(const char * data);
};//DataProcFile

}//monitor
}//savitar

#endif //_AGENT_DATA_PROCESSOR_FILE_H_

