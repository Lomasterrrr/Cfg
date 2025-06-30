SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
while :; do
	NETWORK="$("$SCRIPT_DIR/network.sh" f)"
	MEMORY="$("$SCRIPT_DIR/memory.sh")"
	#echo "+@fg=1;+@bg=1; $NETWORK +@bg=0;+@fg=0; $MEMORY+@bg=0;"
	echo "$NETWORK | $MEMORY"
	sleep 0.5
done
