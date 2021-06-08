#!/bin/bash
#
TMP1=$(cd  $2 &&  git status -s | grep "M User/*" | sed "s,M , $2/,g") 
TMP2=$(cd  $2 &&  git status -s | grep "?? User/*" | sed "s,?? , $2/,g") 

if [[ -n "$TMP1" || -n "$TMP2" ]]
then
    astyle --options=$1/.astylerc $TMP1 $TMP2
fi
exit 0
