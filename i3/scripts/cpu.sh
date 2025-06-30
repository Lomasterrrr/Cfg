#!/bin/sh
if [ -f /tmp/.cpustat ]; then
	read prev_user prev_nice prev_system prev_idle < /tmp/.cpustat
	read cpu user nice system idle rest < /proc/stat
	total=$(( (user + nice + system + idle) - (prev_user + prev_nice + prev_system + prev_idle) ))
	idle_diff=$(( idle - prev_idle ))

	if [ $total -gt 0 ]; then
		usage=$(( (100 * (total - idle_diff)) / total ))
		echo "${usage}%"
	else
		echo "?"
	fi
	else
		echo "-"
		read cpu user nice system idle rest < /proc/stat
	fi

echo "$user $nice $system $idle" > /tmp/.cpustat
			      
