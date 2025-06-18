#!/bin/bash
#colors=(31 32 33 34 35 36 37)
#styles=(0 1 4 5)
#color=${colors[$RANDOM % ${#colors[@]}]}
#style=${styles[$RANDOM % ${#styles[@]}]}
#echo -e "\033[${style};${color}maeeee\033[0m"

colors=("red" "green" "blue" "orange" "purple" "cyan")
styles=("normal" "bold" "italic" "underline")
msgs=("AEEEEEEEE AEE" "Hong Kong" "ktotonokto" "IGRA IN 16 TAKTOV" "Bez prava na oshibku" "aeeee" "Isskustvo levitacii" "True" "ISTINA" "verum")

color=${colors[$RANDOM % ${#colors[@]}]}
style=${styles[$RANDOM % ${#styles[@]}]}
msg=${msgs[$RANDOM % ${#msgs[@]}]}

case "$style" in
  "bold")
    pango="<span foreground=\"$color\"><b>$msg</b></span>"
    ;;
  "italic")
    pango="<span foreground=\"$color\"><i>$msg</i></span>"
    ;;
  "underline")
    pango="<span foreground=\"$color\" underline=\"single\">$msg</span>"
    ;;
  *)
    pango="<span foreground=\"$color\">$msg</span>"
    ;;
esac

#echo "\"$pango\""
#echo "( $pango )"
echo "[ $pango ]"

