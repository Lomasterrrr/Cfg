echo "			CHECK"
echo ""
if fc-list | grep -iq 'freemono'; then
	echo "AE	FreeMono found!"
else
	echo "ERR	FreeMono NOT FOUNDNDNDND!."
	exit 1
fi
check_commands() {
	missing=0
	for cmd in "$@"; do
		if ! command -v "$cmd" >/dev/null 2>&1; then
			echo "ERR	$cmd not found!"
			missing=1
		else
			echo "AE	$cmd found!"
		fi
	done
	if [ $missing -ne 0 ]; then
		echo "ERR       Missing commands detected. Exiting."
		exit 1
	fi
}
check_files() {
        for file in "$@"; do
                if [ -e "$file" ]; then
                        echo "AE	file $file exists!"
                else
                        echo "ERR	file $file not found! Exiting."
                        exit 1
                fi
        done
}
check_dirs() {
	for dir in "$@"; do
		if [ -d "$dir" ]; then
			echo "AE	directory $dir exists!"
		else
			echo "ERR	directory $dir not found! Exiting."
			exit 1
		fi
	done
}
check_commands i3 i3bar i3blocks scrot xclip gcc make vim ldconfig setxkbmap xmodmap xrandr ip
check_files ./configs/i3 ./configs/i3blocks ./configs/i3status
check_files ./configs/vim ./scripts/cpu.sh ./scripts/network.sh ./scripts/memory.sh ./scripts/lay.sh ./scripts/mon.sh ./scripts/sc.sh
check_dirs ./apps ./apps/sout ./apps/st
if ldconfig -p 2>/dev/null | grep -q "libncurses.so"; then
	echo "AE	ncurses found!"
else
	echo "ERR	ncurses not found"
	exit 1
fi

echo ""
echo "			INSTALLL"
echo ""

# i3
mkdir ~/.config/i3 >/dev/null 2>&1
echo "AE	create dir ~/.config/i3!"
cp -f ./configs/i3 ~/.config/i3/config
echo "AE	copy './configs/i3' in '~/.config/i3/config'"
cp -f ./scripts/lay.sh ~/.config/i3/lay.sh
echo "AE	copy './scripts/lay.sh' in '~/.config/i3blocks/lay.sh'"
cp -f ./scripts/sc.sh ~/.config/i3/sc.sh
echo "AE	copy './scripts/sc.sh' in '~/.config/i3blocks/sc.sh'"
cp -f ./scripts/mon.sh ~/.config/i3/mon.sh
echo "AE	copy './scripts/mon.sh' in '~/.config/i3blocks/mon.sh'"

# i3blocks (bar)
mkdir ~/.config/i3blocks >/dev/null 2>&1
echo "AE	create dir ~/.config/i3blocks!"
cp -f ./configs/i3blocks ~/.config/i3blocks/config
echo "AE	copy './configs/i3blocks' in '~/.config/i3blocks/config'"
cp -f ./scripts/cpu.sh ~/.config/i3blocks/cpu.sh
echo "AE	copy './scripts/cpu.sh' in '~/.config/i3blocks/cpu.sh'"
cp -f ./scripts/memory.sh ~/.config/i3blocks/memory.sh
echo "AE	copy './scripts/memory.sh' in '~/.config/i3blocks/memory.sh'"
cp -f ./scripts/network.sh ~/.config/i3blocks/network.sh
echo "AE	copy './scripts/network.sh' in '~/.config/i3blocks/network.sh'"

# i3status (even though I don't need to)
cp -f ./configs/i3status ~/.i3status.conf
echo "AE	copy './configs/i3status' in '~/.i3status.conf'"

# vim
cp -f ./configs/vim ~/.vimrc
echo "AE	copy './configs/vim' in '~/.vimrc'"

# st
rm -rf ~/st
mkdir ~/st >/dev/null 2>&1
echo "AE	create dir ~/st!"
echo "AE	COMPILE ST......"
cd ./apps/st
make clean >/dev/null 2>&1
make
cd ../../
echo "AE	copy './apps/st' in '~/st'"
cp -fr ./apps/st/* ~/st/

# sout
rm -rf ~/sout
mkdir ~/sout >/dev/null 2>&1
echo "AE	create dir ~/sout!"
echo "AE	COMPILE SOUT......"
cd ./apps/sout
make clean >/dev/null 2>&1
make
cd ../../
echo "AE	copy './apps/sout' in '~/sout'"
cp -fr ./apps/sout/* ~/sout/

# tcsh
rm -rf ~/tcsh
mkdir ~/tcsh >/dev/null 2>&1
echo "AE	create dir ~/tcsh!"
echo "AE	COMPILE TCSH......"
cd ./apps/tcsh
make clean >/dev/null 2>&1
./configure
make install -j
cd ../../
cp -fr ./apps/tcsh/* ~/tcsh/
echo "AE	copy './apps/tcsh' in '~/tcsh'"
cp -f ./configs/tcsh ~/.tcshrc
echo "AE	copy './configs/tcsh' in '~/.tcshrc'"
chsh -s /bin/tcsh
echo "AE	set tcsh for main shell (chsh -s)"

echo ""
echo "			FINISH"
echo "		PLEASE RESTART I3!"
echo ""
echo "CONFIG I3		~/.config/i3/config"
echo "CONFIG I3BLOCKS		~/.config/i3blocks/config"
echo "CONFIG I3STATUS		~/.i3status.conf"
echo "CONFIG VIM		~/.vimrc"
echo "CONFIG TCSH		~/.tcshrc"
echo "APP SOUT		~/sout"
echo "APP ST			~/st"
echo "APP TCSH			~/tcsh"
echo ""
echo "super + enter		st (terminal)"
echo "super + d		sout (apps)"
echo "super + z		screenshots (check ~/screenshots)"
echo "capslock == escape	for vim"

