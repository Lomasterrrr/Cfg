#!/bin/bash
YEAR=$(date +%Y)
MONTH=$(date +%m)
DIR="$HOME/screenshots/$YEAR/$MONTH"
mkdir -p "$DIR"
FILENAME="$DIR/screenshot_$(date +%Y-%m-%d_%H-%M-%S).png"
scrot -s "$FILENAME"
xclip -selection clipboard -t image/png -i "$FILENAME"
