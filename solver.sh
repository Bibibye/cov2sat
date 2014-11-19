#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage : $0 graph.out"
    echo "Where graph.out is an executable file generated whith cov2sat."
    exit
fi

let "i = 1"
let "sat_ok = 0"
while [ $sat_ok -eq 0 ]
do
    ./$1 $i > $1.sat
    minisat $1.sat $1.result > /dev/null 2>&1
    result=`cat $1.result`
    if [ "$result" = "UNSAT" ]
    then
	let "i = $i + 1"
    else
	let "sat_ok = 1"
    fi
done

echo "The minimal vertex cover contains $i vertices."

rm *.sat *.result
