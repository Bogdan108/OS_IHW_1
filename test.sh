#!/bin/bash

./$1 < $2 > out.txt

d=$(diff out.txt $3)

if [ "$d" == "" ]
then
    echo "Test $1 $2 is Okay!"
else
    echo "Test $1 $2 is not Okay!"
    echo "$d"
fi

rm out.txt