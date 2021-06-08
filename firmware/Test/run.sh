#!/bin/bash
for file in build/Test/UT_*
do
    ./$file
    if [ $? == 0 ]
    then
        GOODCOUNT=$(($GOODCOUNT+1))
    fi
    TOTCOUNT=$(($TOTCOUNT+1))
done
echo -n "Total of tests" $TOTCOUNT", completed successfully" $GOODCOUNT
if [ $GOODCOUNT == $TOTCOUNT ]
    then
    exit 0
else
    exit &(( $TOTCOUNT - $GOODCOUNT ))
fi
