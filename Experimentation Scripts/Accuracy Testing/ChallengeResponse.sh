#!/bin/bash
dataFileName="../Data/15MBData.csv"
attackFileName="../Data/AttackedData.csv"
AttackPercnt=0.01
AttackBlockSize=2000 # DONT FORGET TO MATCH IT WITH THE VALUES IN CONFIG FILE (SECSIZE*)
TESTCOUNT=50
counter=1
echo "Want to Perform Attack? (Press 1 or 0):"
read ATTACK
for i in $(seq 1 $TESTCOUNT)
do
  echo "Executing Testing Script. Iteration No. $counter ..............................................................................."
  	#./DataAudit Setup
	#echo "Setup Done..."
	#./DataAudit TagGen Params.bin alpha.bin $dataFileName
	#echo "Metadata generated for thr data file $dataFileName"
  ./DataAudit ChallengeGen
  echo "Challenge Generated"
  if [ $ATTACK -eq 1 ]; then
  	cp "$dataFileName" "$attackFileName"
  	./Attack $attackFileName $AttackPercnt $AttackBlockSize
  	./DataAudit ProofGen Params.bin $attackFileName ChalStr.txt
  	echo "ProofGen Executed on Corrupted Data File"
  else
  	./DataAudit ProofGen Params.bin $dataFileName ChalStr.txt
  	echo "ProofGen Executed on Original Data File"
  fi
  output=$(./DataAudit VerifyProof Params.bin POP.bin metaData.bin ChalStr.txt)
  if [[ $output -eq 1  &&  $ATTACK -eq 1 ]]; then
    echo "SOUNDNESS VIOLATED: FAILED TO DETECT ATTACK at $counter 'th ITERATION"
    exit 0
  fi
  if [[ $output -eq 0  &&  $ATTACK -eq 0 ]]; then
    echo "COMPLETENESS VIOLATED: WITHOUT ANY ATTACK THE VERIFICATION FAILED at $counter 'th ITERATION ..."
    exit 0
  fi
  counter=$((counter + 1))
  echo "Iteration No. $((counter - 1)) Completed Successfully"
done
if [ $ATTACK -eq 1 ]; then
	echo "TESTING IS SUCCESSFULL. . . ATTACK DETECTED IN ALL $((counter - 1)) ITERATIONS"
else
	echo "TESTING IS SUCCESSFULL. . . CORRECTNESS PRESERVED IN ALL $((counter - 1)) ITERATIONS"
fi





