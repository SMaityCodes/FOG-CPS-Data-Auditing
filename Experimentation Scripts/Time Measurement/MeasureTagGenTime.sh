#!/bin/bash
dataFileName="../Data/15MBData.csv"
executionCommand="./DataAudit TagGen Params.bin alpha.bin $dataFileName"
TESTCOUNT=10
TotTime=0
counter=0
for i in $(seq 1 $TESTCOUNT)
do
	echo "Round $((counter + 1)) . Performing necessary pre-processing ..."
	x=$(./DataAudit Setup) # taking the ouput in a varialbe so that it is not printed on screen
	echo "Executing The Main Algo. ..."
	timeTaken=$($executionCommand)
	echo "Execution Complete. Time taken = $timeTaken"
	TotTime=$(awk "BEGIN {print $TotTime + $timeTaken}")
	counter=$((counter + 1))
done
avgTime=$(awk "BEGIN {print $TotTime / $counter}")
echo "Avg Execution time = $avgTime" 



