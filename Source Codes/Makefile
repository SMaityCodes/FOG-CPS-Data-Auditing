all: mainprog attack filecompare

mainprog:
	@echo "Compiling the main program..."
	g++ DataAudit.cpp -o DataAudit -lcrypto++
	
attack:
	@echo "Compiling the attacker program..."
	g++ Attack.cpp -o Attack -lcrypto++

filecompare:
	@echo "Compiling the filecompare program..."
	g++ fileCompare.cpp -o fileCompare -lcrypto++
	
clean:
	@echo "Remove all binary files..."
	rm Attack DataAudit fileCompare
	

		
	

