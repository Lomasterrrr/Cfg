setxkbmap -layout us,ru -option grp:alt_shift_toggle
xmodmap -e "clear lock"
xmodmap -e "keycode 66 = Control_L"
xmodmap -e "add Control = Control_L"

