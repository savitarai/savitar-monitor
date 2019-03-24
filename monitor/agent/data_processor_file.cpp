/**
 * @file        data_processor_file.cpp
 * @brief       监控数据写文件处理
 * @version     1.0
 * @date        03/16/2019 01:30:59 AM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "data_processor_file.h"

#include <stdio.h>

namespace savitar {
namespace monitor {

int DataProcessorFile::Init(const char *filename)
{
    int rt = 0;
    do {
        fp_ = fopen(filename, "a+");
        if (fp_ == NULL)
        {
            rt = -1;
            break;
        }
    } while (0);
    return rt;
}

int DataProcessorFile::Proc(const char *data)
{
    int rt = 0;
    do {
        if (fp_ != NULL)
        {
            fprintf(fp_, "%s\n", data);
            fflush(fp_);
        }else
        {
            rt=-1;
        }
    } while (0);
    return rt;
}

} // namespace monitor
} // namespace monitor
