setxkbmap -layout us,ru -option grp:alt_shift_toggle
xmodmap -e "clear lock"
xmodmap -e "keycode 66 = Escape"
