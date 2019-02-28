/**
 * @file        test_curl.cpp
 * @brief       test curl usage
 * @version     1.0
 * @date        01/25/2019 12:24:02 AM
 * @author      tashanji (jitashan), jitashan@gmail.com
 */

#include "curl/curl.h"


int main(int argc, char * argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);

    curl_global_cleanup();
    return 0;
}
