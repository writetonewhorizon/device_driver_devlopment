#!/bin/bash

clear

gcc -o attr_mutex attr_mutex.c -lpthread
#gcc -o mutex mutex.c -lpthread

#./mutex
./attr_mutex
