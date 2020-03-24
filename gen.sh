#!/bin/bash
if [ $# -eq 1 ]
then
    ./utils/generatorKadane.exe $1
fi

if [ $# -eq 2 ]
then
    # ./generatorKadane.exe $1
    for i in `seq $1 $2`
	do
    	echo "Running gen" $i
        ./utils/generatorKadane.exe $i
    done
fi
