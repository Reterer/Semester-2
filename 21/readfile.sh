#! /usr/bin/env bash
COUNT=0
LINES=0
IFS=""
while read LINE
do
    ((COUNT=COUNT+${#LINE}))
    ((LINES=LINES+1))
done < "$1"
echo $COUNT
echo $LINES
