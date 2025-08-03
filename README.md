# FOG-CPS Data Auditing

## 📁 Project Structure

```
FOG-CPS Data Auditing
├── Aditor/              
│   ├── Alice.sh            # SHELL script for auditor's protocol    
│   ├── Configuration.txt   # Protocol configuration and debug parameters
│   ├── DataAudit           # [executable] the main data-auditing software
│   ├── Failure_Msg.ogg     # supporting audio file 
│   └── Success_Msg.ogg     # supporting audio file
│
├── Auditee/              
│   ├── 15MBData.csv        # A sample data-file 
│   ├── 15MBData2.csv       # Copy of the sample data-file
│   ├── Bob.sh              # SHELL script for auditee's protocol 
│   ├── Configuration.txt   # Protocol configuration and debug parameters
│   ├── DataAudit           # [executable] the main data-auditing software
│   ├── Attack              # [executable] the attack-software
│   └── fileCompare         # [executable] software for comparing the difference between two data-files
│
├── CSP-Admin/              
│   ├── Configuration.txt   # Protocol configuration and debug parameters
│   ├── DataAudit           # [executable] the main data-auditing software
│   └── SetupTagGen.sh      # SHELL script for admin's protocol
│
├── Experimentation Scripts/ # SHELL scripts for accuracy and execution-time measurement
│   ├── Accuracy Testing/
│   │   └── ChallengeResponse.sh
│   └── Time Measurement/
│       ├── MeasureProofGenTime.sh
│       ├── MeasureProofVerifyTime.sh
│       ├── MeasureSetupTime.sh
│       ├── MeasureTagGenTime.sh
│       └── SetupTagGen.sh
│
└── Source Codes/            # All source codes
    ├── DataAudit.cpp
    ├── dataAuditutils.h
    ├── dataAuditv2.h
    ├── generalUtility.h
    ├── Attack.cpp
    ├── fileCompare.cpp    
    └── Makefile

```

## 🚀 How to Use This Repository?
You can test it in three different systems connected by a network - one system working as the cloud (Admin), one acting as the auditor and the other one acting as the auditee. However, you can also test it on a single system (in different terminals). Our files are written assuming the testing to be done on same system. Make the changes accordingly if you test on different systems.

- clone the repository
- copy the "CSP-Admin" directory into the cloud (Admin) system
- copy the "Aditor" directory into the aditor system
- copy the "Auditee" directory into the auditee system
- Go inside "CSP-Admin" dir:-
    - make sure that the path and filename of the data-file (file to be audited) is properly mentioned in the  `SetupTagGen.sh` script
    - run the following command on a terminal opened inside the dir:-
      ```
      chmod +x SetupTagGen.sh DataAudit
      ./SetupTagGen.sh
      ```
    - the above will generate the admin's secret-key *alpha*, the public parameters *params* and the *metadata* of the data-file using *alpha* and *params*
    - copy the params file (`Params.bin`) to both "Aditor" and "Auditee" directories
    - copy only the *metadata* file (`metaData.bin`) to "Aditor" dir only
- Go inside "Auditor" dir:-
    - set the Auditee’s IP address inside `Alice.sh` (set `127.0.0.1` for localhost)
    - run the following command on a terminal opened inside the dir:-
      ```
      chmod +x Alice.sh DataAudit
      ```
- Go inside "Auditee" dir:-
    - set the Auditor’s IP address inside `Bob.sh` (set `127.0.0.1` for localhost)
    - run the following command on a terminal opened inside the dir:-
      ```
      chmod +x Bob.sh DataAudit Attack fileCompare
      ```








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
