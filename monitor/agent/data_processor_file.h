/**
 * @file        data_processor_file.h
 * @brief       监控数据处理（写文件）
 * @version     1.0
 * @date        03/15/2019 08:09:31 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */
#ifndef _AGENT_DATA_PROCESSOR_FILE_H_
#define _AGENT_DATA_PROCESSOR_FILE_H_

#include <stdio.h>

#include "data_processor_inf.h"
#include "boost/serialization/singleton.hpp"

namespace savitar{
namespace monitor{
class DataProcessorFile: public DataProcessorInf, public boost::serialization::singleton<DataProcessorFile> 
{
public:
    DataProcessorFile():fp_(NULL)
    {
    }

    ~DataProcessorFile()
    {
        if(fp_ != NULL)
        {
            fclose(fp_);
            fp_=NULL;
        }
    }

    /**
     * @brief           初始化
     *
     * @param filename  [in],输入写文件的文件名
     *
     * @return          成功返回0， 否则返回其他错误码 
     */
    int Init(const char * filename);

    /**
     * @brief       处理接受到的监控数据
     *
     * @param data  [in], 待处理的数据,JSON格式, 参照api说明
     * @return      成功返回0， 否则返回其他的错误码
     */
    virtual int Proc(const char * data);


private:
    FILE * fp_; ///<文件描述符

};//DataProcFile

}//monitor
}//savitar

#endif //_AGENT_DATA_PROCESSOR_FILE_H_

