/**
 * @file        shm.cpp
 * @brief       共享内存操作
 * @version     1.0
 * @date        01/14/2019 02:34:43 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "shm.h"

//include STD C/C++ head files
#include <sys/shm.h>
#include <sys/errno.h>
#include <string.h>
#include <stdio.h>

#ifndef LOG_ERROR
//#define LOG_ERROR(fmt, a...) fprintf(stderr, fmt, ##a)
#define LOG_ERROR(fmt, a...) do{}while(0) 
#endif

namespace savitar
{
namespace util 
{

void* Shm::ShmAttach(uint32_t key, size_t size, int shmflag)
{
    int shmid = shmget(key, size, shmflag);
    if (shmid == -1)
    {
        LOG_ERROR("shmget key=%d, size=%d failed! error = %d, msg = %s",
			key, size, errno, strerror(errno));
        return NULL;
    }

    void* addr = shmat(shmid, 0, 0);
    if (addr == (void*)-1)
    {
        LOG_ERROR("shmget key=%d, size=%d failed!", key, size);
        return NULL;
    }

    return addr;
}

void* Shm::ShmCreate(uint32_t key, size_t size, int shmflag)
{
    int shmid = shmget(key, size, shmflag|IPC_CREAT);
    if (shmid == -1)
    {
        LOG_ERROR("shmget key=%d, size=%d failed!", key, size);
        if (errno == EINVAL)
        {
            shmid = shmget(key, 0, SHM_R|SHM_W);
        }
        if (shmid == -1)
        {
            LOG_ERROR("shmget key=%d, size=%d failed!", key, 0);
            return NULL;
        }

        int ret = shmctl(shmid, IPC_RMID, NULL);
        if (ret == 0)
        {
            shmid = shmget(key, size, SHM_R|SHM_W|IPC_CREAT);
        }
        else 
        {
            LOG_ERROR("shmctl remove key=%d, size=%d failed!", key, size);
            return NULL;
        }
        if (shmid == -1)
        {
            LOG_ERROR("shmget key=%d, size=%d failed!", key, size);
            return NULL;
        }
    }

    void* addr = shmat(shmid, 0, 0);
    if (addr == (void*)-1)
    {
        LOG_ERROR("shmat key=%d, size=%d failed!", key, size);
        return NULL;
    }

    return addr;
}

int Shm::ShmDelete(uint32_t key, size_t size)
{
    int shmid = shmget(key, size, SHM_R|SHM_W);
    if (shmid == -1)
    {
        LOG_ERROR("shmget key=%d, size=%d failed!", key, size);
        return -1;
    }

    int ret = shmctl(shmid, IPC_RMID, NULL);
    if (ret != 0)
    {
        LOG_ERROR("shmctl remove key=%d, size=%d failed!", key, size);
    }
    return ret;
}

int Shm::ShmDetach(void* addr)
{
    int ret = shmdt(addr);
    if (ret != 0)
    {
        LOG_ERROR("shmdt addr=%d failed!", addr);
    }
    return ret;
}

size_t Shm::ShmSize(uint32_t key)
{
    int shmid = shmget(key, 0, SHM_R|SHM_W);
    if (shmid == -1)
    {
        LOG_ERROR("shmget key=%d, size=%d failed!", key, 0); 
        return -1;
    }

    struct shmid_ds shm_stat;
    if (shmctl(shmid, IPC_STAT, &shm_stat) == 0)
    { 
        return shm_stat.shm_segsz;
    }

    return -1;
}



} // namespace ors
} // namespace savitar

