#!/bin/bash
dataFileName="../Data/15MBData.csv"
executionCommand="./DataAudit ProofGen Params.bin $dataFileName ChalStr.txt"
TESTCOUNT=70
TotTime=0
counter=0
for i in $(seq 1 $TESTCOUNT)
do
	echo "Round $((counter + 1)) . Performing necessary pre-processing ..."
	./DataAudit ChallengeGen
	echo "Executing The Main Algo. ..."
	timeTaken=$($executionCommand)
	echo "Execution Complete. Time taken = $timeTaken"
	TotTime=$(awk "BEGIN {print $TotTime + $timeTaken}")
	counter=$((counter + 1))
done
avgTime=$(awk "BEGIN {print $TotTime / $counter}")
echo "Avg Execution time = $avgTime" 



