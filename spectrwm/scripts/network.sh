#!/bin/sh
iface=$(ip route | awk '/default/ {print $5; exit}')
ip=$(ip addr show "$iface" | awk '/inet / {print $2}' | cut -d/ -f1)

if [ "$1" = "f" ]; then
	printf "%s (%s Mbit/s)\n" "$ip" "100"
else
	printf "<u>%s (%s Mbit/s)</u>\n" "$ip" "100"
fi

