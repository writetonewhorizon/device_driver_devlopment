#!/bin/bash

#pid=`pgrep -x "mutex"`
pid=`pgrep -x "attr_mutex"`
echo $pid
kill -SIGKILL $pid
