#!/bin/bash
executionCommand="./DataAudit Setup"
TESTCOUNT=500
TotTime=0
counter=0
for i in $(seq 1 $TESTCOUNT)
do
	echo "Round $((counter + 1)) . Performing necessary pre-processing ..."
	# nothing
	echo "Executing The Main Algo. ..."
	timeTaken=$($executionCommand)
	echo "Execution Complete. Time taken = $timeTaken"
	TotTime=$(awk "BEGIN {print $TotTime + $timeTaken}")
	counter=$((counter + 1))
done
avgTime=$(awk "BEGIN {print $TotTime / $counter}")
echo "Avg Execution time = $avgTime" 



