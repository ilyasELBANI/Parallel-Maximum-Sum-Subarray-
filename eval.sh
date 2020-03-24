#!/bin/bash
if [ $# -eq 1 ]
then
    python3 ./utils/eval.py $1
fi

if [ $# -eq 2 ]
then
    # ./generatorKadane.exe $1
    python3 ./utils/eval.py $1 $2
fi
