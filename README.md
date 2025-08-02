<pre> ```markdown ## 📁 Directory Structure ``` FOG-CPS-Data-Auditing/ ├── Aditor/ │ ├── Alice.sh │ ├── Configuration.txt │ ├── DataAudit │ ├── Failure_Msg.ogg │ └── Success_Msg.ogg ├── Auditee/ │ ├── 15MBData.csv │ ├── 15MBData2.csv │ ├── Attack │ ├── Bob.sh │ ├── Configuration.txt │ ├── DataAudit │ └── fileCompare ├── CSP-Admin/ │ ├── Configuration.txt │ ├── DataAudit │ └── SetupTagGen.sh ├── Experimentation Scripts/ │ ├── Accuracy Testing/ │ │ └── ChallengeResponse.sh │ └── Time Measurement/ │ ├── MeasureProofGenTime.sh │ ├── MeasureProofVerifyTime.sh │ ├── MeasureSetupTime.sh │ ├── MeasureTagGenTime.sh │ └── SetupTagGen.sh └── Source Codes/ ├── Attack ├── Attack.cpp ├── DataAudit ├── DataAudit.cpp ├── Makefile ├── dataAuditutils.h ├── dataAuditv2.h ├── fileCompare ├── fileCompare.cpp └── generalUtility.h ``` ``` </pre>

Algebraic Signature Based Demonstration Guidelines

Initial Content of CSP-Admin:-
DataAudit (main s/w)
Configuration.txt   (configuration file)
SetupTagGen.sh (Script to generate key materials and metadata)
Initial Content of Auditor (Alice):-
DataAudit (main s/w)
Configuration.txt   (configuration file)
Success_Msg.ogg (Success message audio file)
Failure_Msg.ogg (Failure message audio file)
Alice.sh (The main Auditor Script)
Initial Content of Auditee / Storage (Bob):-
Data_File
Backup of the Data_file
DataAudit (main s/w)
Configuration.txt   (configuration file)
Attack (attack s/w - specify attack proportion & blocksize)
fileCompare (s/w to compare between two files - mismatching blocks) [optional]
Bob.sh (The main Auditee Script)







Go inside CSP-Admin dir and run:-
chmod +x SetupTagGen.sh DataAudit
Step-1: Make sure that the path and filename of the Data file is properly mentioned in the  ‘SetupTagGen.sh’ script
Step-2: Run the ‘SetupTagGen.sh’ script in Admin
Step-3: copy the params file (‘Params.bin’) from Admin to both Alice and Bob
Step-4: copy only the metadata file (‘metaData.bin’) from Admin to Alice only

Go inside Auditee dir and run:-
chmod +x Bob.sh DataAudit Attack fileCompare
Step-5: correct the Auditor’s IP address inside ‘Bob.sh’ (set 127.0.0.1 for localhost)

Go inside Auditor dir and run:-
chmod +x Alice.sh DataAudit
Step-6: correct the Auditee’s IP address inside ‘Alice.sh’ (set 127.0.0.1 for localhost)

Step-7: Upload Bob Folder in server machine
Step-8: Open three terminals:-
One inside the Auditor (Alice)
Two inside the Auditee (Bob) - may also login remotely using ssh
Step-9: Run ./Bob.sh inside one of the terminals in Bob
Step-10: Run ./Alice.sh inside Alice

Step-11: Observe for some time - verification must be successful in all instances
Step-12: Now Run the Attack program inside the other terminal in Bob 
(./Attack <filename> <attack_proportion> <blocksize>) 
E.g.:
./Attack 15MBData.csv  0.01 2000
blocksize = 2000; 
attack_proportion = 0.01 (may reduce also)
Step-13: Attack should be immediately detected by Alice 

 Step-14: In Each of the folders : Alice, Bob and Admin - ‘Statistics.txt’ file will be generated - check the  execution times from there

To check the correctness of the Attack program we have the ‘filecompare’ program. To compare between two files run  it:-

./fileCompare <filename1> <filename2> <blocksize>

e.g.:-

./fileCompare 15MBData.csv 15MBData2.csv 2000


To Compile the Source Codes:-

make clean
 // removes all the precompiled executables in this directory

make
// compiles all the source codes
