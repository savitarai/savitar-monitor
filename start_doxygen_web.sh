#!/bin/sh

source deactivate;source activate python2
cd ./doxygen/html
setsid python -m SimpleHTTPServer 8002 >/tmp/monitor_doxygen.log 2>&1 &
