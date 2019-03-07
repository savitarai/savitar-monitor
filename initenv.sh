#!/bin/sh

#配置环境，注意，必须在当前目录执行

PROJECT_DIR=$(pwd)

if [ ! -f ${PROJECT_DIR}/initenv.sh ]
then
    echo "this script must be executed in project root dir!"
    exit 1
fi
if [ -f ${PROJECT_DIR}/.initdone ]
then
    echo "this scrip has been executed last time!"
    exit 1
fi


echo "export SAVITAR_MONITOR_ROOT=${PROJECT_DIR}" >>~/.bash_profile
echo "export PATH=\$SAVITAR_MONITOR_ROOT:\$PATH" >>~/.bash_profile

git submodule init
git submodule update 

#初始化成功标记
touch ${PROJECT_DIR}/.initdone
