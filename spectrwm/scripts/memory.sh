#!/bin/sh
used=$(free -m | awk '/^Mem:/ {printf "%.2f", $3/1024}')
free=$(free -m | awk '/^Mem:/ {printf "%.2f", $4/1024}')
echo "${used} GiB ${free} GiB"
