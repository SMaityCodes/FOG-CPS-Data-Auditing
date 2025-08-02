#include"dataAuditv2.h"


int main(int argc, char **argv) {

 ///////////////////////////////// GENERAL PROCESSING //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    if(argc < 2){
	printf("Error: Please Enter Correct Execution Command %d !!!\n", argc);
	exit(1);
    }
    
    std::ifstream configFile("Configuration.txt");  
    if (!configFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        exit(1);
    }
    
    statFile.open(statFileName, ios::binary | std::ios::app);
    if (!statFile.is_open()) {
        cerr << "Unable to open input file: " << statFileName << endl;
        exit(1);
    }
    
    // Reading the Protocol Configuration Values from the "Configuration.txt" file
    int configValCount = 8, i= 0;
    vector<string> Values(configValCount);
    string val;
    std::string line;
    while (std::getline(configFile, line)) {  // Read the file line by line
        size_t pos = line.find('=');     // Find the '=' symbol
        if (pos != std::string::npos) {  // If '=' is found
            val = line.substr(pos + 1);  // Extract the value after '='
            // Trim whitespace from the value
            val.erase(0, val.find_first_not_of(" \t"));
            val.erase(val.find_last_not_of(" \t") + 1);
            Values[i++] = val;
        }
    }
    
    // Assigning the retrived configuration values to initialize the global variables
   
    SECSIZE = stoi(Values[0]);
    SECPERBLOCK = stoi(Values[1]);
    k1 = stoi(Values[2]);
    k2 = stoi(Values[3]);
    AUDIT_PERCENT = stod(Values[4]);
    debug =  stoi(Values[5]);
    lastProgramDebug =  stoi(Values[6]);
    timeDebug = stoi(Values[7]);
    BLOCKSIZE = (SECSIZE*SECPERBLOCK);
    ENCODESIZE_1 = (k1/8);
    ENCODESIZE_2 = (k2/8);
    TAGSIZE = ENCODESIZE_2;
    
    /*
    cout << "SECSIZE = " << SECSIZE << " bytes" << endl;
    cout << "SECPERBLOCK = " << SECPERBLOCK << endl;
    cout << "k1 = " << k1 << "-bis" << endl;
    cout << "k2 = " << k2 << "-bis" << endl;
    cout << "debug = " << debug << endl;
    cout << "lastProgramDebug = " << lastProgramDebug << endl;
    cout << "BLOCKSIZE = " << BLOCKSIZE << " bytes" << endl;
    cout << "ENCODESIZE_1 = " << ENCODESIZE_1 << " bytes" << endl;
    cout << "ENCODESIZE_2 = " << ENCODESIZE_2 << " bytes" << endl;
    cout << "TAGSIZE = " << TAGSIZE << " bytes" << endl;
    */
    
    configFile.close(); 
    
/////////////////////////////////////// SETUP ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    if (strcmp(argv[1], "Setup") == 0){
    	if(debug) cout <<endl<< "  ==============================    Setup Executing    =========================================   " << endl;
    
    	Setup();
    	
    	if(debug) cout << "  ==============================    Setup Executed Successfully    =========================================   " << endl;
    }
    
////////////////////////////////////// TAGGEN ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
    else if (strcmp(argv[1], "TagGen") == 0){
    	if(debug) cout <<endl<< "  ==============================    TagGen Executing    =========================================   " << endl;
    	
    	if(argc < 5){
		printf("Error: Please Check the Correct TagGen Command !!!\n");
		exit(1);
    	}
    	
    	ifstream ParamsFile(argv[2], ios::binary);
    	if (!ParamsFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[2] << endl;
        	exit(1);
    	}
    	ifstream alphaFile(argv[3], ios::binary);
    	if (!alphaFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[3] << endl;
        	exit(1);
    	}
    	
    	
    	if(debug) cout<< "Retrieving Param Values from Param-File... " << endl;
    	GlobalParams params;
    	params.LoadValuesFromFile(ParamsFile);
    	 
    	if(debug) params.PrintValues();
	
	if(debug) cout<< "Retrieving Alpha Value from Alpha-File... " << endl;
	Integer alpha = LoadIntegerFromBinaryFile(alphaFile, ENCODESIZE_2);
    	if(debug) cout << "alpha = " << alpha  << endl;
    
	TagGen(argv[4], alpha, params);
	ParamsFile.close();
	alphaFile.close();
	
	if(debug) cout << "  ==============================    TagGen Executed Successfully    =========================================   " << endl;
    }
    
////////////////////////////////////// CHALLENGEGEN /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
    else if (strcmp(argv[1], "ChallengeGen") == 0){
    	if(debug) cout <<endl<< "  ==============================    ChallengeGen Executing    =========================================   " << endl;
    
    	ChallengeGen("ChalStr.txt");
    	
    	if(debug) cout << "  ==============================    ChallengeGen Executed Successfully    =========================================   " << endl;
    }
    
///////////////////////////////////////// PROOFGEN /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
    else if (strcmp(argv[1], "ProofGen") == 0){
    	if(debug) cout <<endl<< "  ==============================    ProofGen Executing    =========================================   " << endl;
    	
    	if(argc < 5){
		printf("Error: Please Check the Correct ProofGen Command !!!\n");
		exit(1);
    	}
    	ifstream paramsFile(argv[2], ios::binary);
    	if (!paramsFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[2] << endl;
        	exit(1);
    	}
    	
    	ifstream dataFile(argv[3], ios::binary);
    	if (!dataFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[3] << endl;
        	exit(1);
    	}
    	
    	ifstream chalFile(argv[4], ios::binary);
    	if (!chalFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[4] << endl;
        	exit(1);
    	}
    	string seed_str;
    	getline(chalFile, seed_str);
    	if(debug) cout << "Seed String is: " << seed_str << endl;
    	
    	GlobalParams params;
    	params.LoadValuesFromFile(paramsFile);
    	if(debug) params.PrintValues();
    	
    	ProofGen(argv[3], seed_str, params);
    	
    	paramsFile.close();
    	dataFile.close();
    	chalFile.close();
    	
    	if(debug) cout << "  ==============================    ProofGen Executed Successfully    =========================================   " << endl;
    }
    
/////////////////////////////////////////// VERIFYPROOF ///////////////////////////////////////////////////////////////////////////////////////////////
     
    else if (strcmp(argv[1], "VerifyProof") == 0){
    	if(lastProgramDebug) cout <<endl<< "  ==============================    VerifyProof Executing    =========================================   " << endl;
    	
    	if(argc < 6){
		printf("Error: Please Check the Correct VerifyProof Command !!!\n");
		exit(1);
    	}
    	
    	ifstream paramsFile(argv[2], ios::binary);
    	if (!paramsFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[2] << endl;
        	exit(1);
    	}
    	
    	ifstream POPFile(argv[3], ios::binary);
    	if (!POPFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[3] << endl;
        	exit(1);
    	}
    	
    	ifstream chalFile(argv[5], ios::binary);
    	if (!chalFile.is_open()) {
        	cerr << "Unable to open input file: " << argv[6] << endl;
        	exit(1);
    	}
    	
    	if(lastProgramDebug) cout<< "Retrieving Param Values from Param-File... " << endl;
    	GlobalParams params;
    	params.LoadValuesFromFile(paramsFile);
    	if(lastProgramDebug) params.PrintValues();
	
	if(lastProgramDebug) cout<< "Retrieving POP Values from POP-File... " << endl;
	PP_PoPData popData; 
	popData.LoadValuesFromFile(POPFile);;
	if(lastProgramDebug) popData.PrintValues();
    	
    	string seed_str;
    	getline(chalFile, seed_str);
    	if(lastProgramDebug) cout << "Seed String is: " << seed_str << endl;
    	
    	VerifyProof(argv[4], popData, seed_str, params);
    	
    	paramsFile.close();
    	POPFile.close();
    	chalFile.close();
    	
    	//if(lastProgramDebug) cout << "  ==============================    VerifyProof Executed Successfully    =========================================   " << endl;
    }
    
////////////////////////////////////////       Error in Execution Command         ////////////////////////////////////////////////////////////////////////
    
    else{
		printf("Incorrect Command\n");
    }
    
//////////////////////////////////////////////// END //////////////////////////////////////////////////////////////////////////////////////////////////////
     
    statFile.close(); 
    return 0;
}

