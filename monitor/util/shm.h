/**
 * @file        shm.h
 * @brief       共享内存常用操作
 * @version     1.0
 * @date        01/14/2019 12:55:55 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#ifndef _UTIL_SHM_H_
#define _UTIL_SHM_H_

// include STD C/C++ head files
#include <stdint.h>
#include <stddef.h>

// include third_party_lib head files

namespace savitar {
namespace util {
class Shm {

public:

    /**
     * @brief           创建共享内存
     * @return          成功返回对应的指针，失败返回NULL
     */
    static void *ShmCreate(uint32_t key, size_t size, int shmflag = 0600);

    /**
     * @brief           attach共享内存
     * @return          成功返回对应的指针，失败返回NULL
     */
    static void *ShmAttach(uint32_t key, size_t size, int shmflag = 0600);

    /**
     * @brief           detach共享内存
     */
    static int ShmDetach(void *addr);

    /**
     * @brief           删除共享内存
     */
    static int ShmDelete(uint32_t key, size_t size);

    /**
     * @brief       获取共享内存大小
     * @return      成功返回对应的共享内存的大小，否则返回-1
     */
    static size_t ShmSize(uint32_t key);

}; // class Shm

} // namespace util
} // namespace poseidon

#endif ///<_UTIL_SHM_H_
