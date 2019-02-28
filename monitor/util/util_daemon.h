/**
 * @file        util_daemon.h
 * @brief       daemon程序常用函数
 * @version     1.0
 * @date        01/19/2019 11:38:02 PM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */
#ifndef _UTIL_DAEMON_H_
#define _UTIL_DAEMON_H_

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

namespace savitar {
namespace util {
class UtilDaemon {
public:
    /**
     * @brief   把进程放到后台执行
     */
    static void Daemonize()
    {
        int fd;

        // shield some signals
        signal(SIGALRM, SIG_IGN);
        signal(SIGHUP, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGPIPE, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);

        // fork child process
        if (fork())
            exit(0);

        // creates  a new session
        if (setsid() == -1)
            exit(1);

        if (fork())
            exit(0);

        // If you needn't STDIN,STDOUT,STDERR, close fd from 0;
        for (fd = 3; fd < 64 ; fd++)
            close(fd);
        umask(0);
        return;
    }



    /**
     * @brief           文件锁
     *
     * @return
     * @retval <0       锁文件失败(其他进程锁住该文件了) 
     */
    static int lockfile(int fd)
    {
        struct flock fl;

        fl.l_type = F_WRLCK;
        fl.l_start = 0;
        fl.l_whence = SEEK_SET;
        fl.l_len = 0;
        return (fcntl(fd, F_SETLK, &fl));
    }

    /**
     * @brief           锁住PID文件，保证只有一个进程在执行
     * @param pid_file
     * @return
     * @retval true     成功锁住文件
     * @retval false    锁文件失败
     */
    static bool LockPidfile(const char *pid_file)
    {
        int fd;
        char buf[16];
        fd = open(pid_file, O_RDWR | O_CREAT,
                  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
        if (fd < 0) {
            return false;
        }
        if (lockfile(fd) < 0) {
            close(fd);
            return false;
        }
        ftruncate(fd, 0);
        sprintf(buf, "%ld", (long)getpid());
        write(fd, buf, strlen(buf) + 1);
        //注意：这里fd不要close掉，这个fd随进程生存期一直保留
        return true;
    }
};
}
}
#endif //_UTIL_DAEMON_H_
