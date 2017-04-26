#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <math.h>
#include <fcntl.h>

#include "431project.h"




/*
 * Returns 1 if valid, else 0
 */
int validateConfiguration(std::string configuration){
	// FIXME - YOUR CODE HERE
	// flag assumes valid until proven otherwise
	int fieldArray[18]; 
	int blockSize = 0; 
	if(!isan18dimconfiguration(configuration)){
		return 0; 	
	} 
	for(int fieldnum =0; fieldnum <18; ++fieldnum){
    		int j = 2*fieldnum;
    		std::string fieldString = configuration.substr(j,1);
		int field = atoi(fieldString.c_str());
		fieldArray[fieldnum] = field; 
		// checks the details of constraint 5 (simple implementation items) 
		if(fieldArray[fieldnum] >= GLOB_dimensioncardinality[fieldnum]){
			return 0; 
		}		
	}
// constraint 1
	// is set by the width and is always true by construction
	// no need to validate constraint 1 
	// il1 block size = width*8
	blockSize = fieldArray[0] + 3; 
// constraint 2 
	// check to make sure ul2 is double il1 block size 
	if(fieldArray[11] < fieldArray[0]){
		return 0; 	
	}
	//max size 128 Bytes 
	if(fieldArray[11] > 3) {
		return 0; 
	} 
// constraint 3 
	// make sure that the latency is correct
	// total block size = width * 8 * sets (8 = 2^3.... +3) (sets starts at (32 = 2^5).... +5) 
	// latency = total block size * assoc - baseline (baseline = 8KB = 2^13) 
	// ilblocksize = dl1blocksize However, assoc may be different so they may have different latencies
	//il1 
	if(fieldArray[15] != fieldArray[0] + 3 + fieldArray[8] + 5 + fieldArray[9] - 13){
		return 0; 	
	}
	//dl1
	if(fieldArray[14] != fieldArray[0] + 3 + fieldArray[6] + 5 + fieldArray[7] - 13){
		return 0; 	
	}
// constraint 3 
	// total block size = ul2 block * ul2 sets (16 = 2^4 ... + 4) (256 = 2^8 ... + 8 
	// latency + 5 = total block size * assoc - baseline (baseline = 8KB = 2^13)	
	if(fieldArray[16] + 4 != fieldArray[11] + 4 + fieldArray[10] + 8 + fieldArray[12] - 13){
		return 0; 	
	}
/*
0 = width=( "1" "2" "4" "8" ) 
1 = fetchspeed=( "1" "2" ) 
2 = scheduling=( "-issue:inorder true -issue:wrongpath false" "-issue:inorder false -issue:wrongpath true" ) 
3 = ruusize=( "4" "8" "16" "32" "64" "128" ) 
4 = lsqsize=( "4" "8" "16" "32" )
5 = memport=( "1" "2" )
6 = dl1sets=( "32" "64" "128" "256" "512" "1024" "2048" "4096" "8192" )
7 = dl1assoc=( "1" "2" "4" )
8 = il1sets=( "32" "64" "128" "256" "512" "1024" "2048" "4096" "8192" )
9 = il1assoc=( "1" "2" "4" )
10 = ul2sets=( "256" "512" "1024" "2048" "4096" "8192" "16384" "32768" "65536" "131072" )
11 = ul2block=( "16" "32" "64" "128" )
12 = ul2assoc=( "1" "2" "4" "8" "16" ) 
13 = tlbsets=( "4" "8" "16" "32" "64" )
14 = dl1lat=( "1" "2" "3" "4" "5" "6" "7" )
15 = il1lat=( "1" "2" "3" "4" "5" "6" "7" )
16 = ul2lat=( "5" "6" "7" "8" "9" "10" "11" "12" "13" )
17 = branchsettings=( "-bpred perfect" "-bpred nottaken" "-bpred bimod -bpred:bimod 2048" "-bpred 2lev -bpred:2lev 1 1024 8 0" "-bpred 2lev -bpred:2lev 4 256 8 0" "-bpred comb -bpred:comb 1024" )
*/

  // The below is a necessary, but insufficient condition for validating a configuration
  //return isan18dimconfiguration(configuration); 
	return 1;
}



/*
 * Given the current best known configuration, the current configuration, and the globally visible map of all previously investigated configurations, suggest a previously unexplored design point. You will only be allowed to investigate 1000 design points in a particular run, so choose wisely.
 */
std::string generateNextConfigurationProposal(std::string currentconfiguration, std::string bestEXECconfiguration, std::string bestEDPconfiguration, int optimizeforEXEC, int optimizeforEDP){
  std::string nextconfiguration=GLOB_baseline;
  while(GLOB_seen_configurations[nextconfiguration]){ // check if proposed configuration has been seen before
    
    /*
     * REPLACE THE BODY OF THIS WHILE LOOP WITH YOUR PROPOSAL FUNCTION
     *
     * The proposal function below is extremely unintelligent and
     * will produce configurations that, while properly formatted, violate specified project constraints
     */    

    //
    //YOUR CODE BEGINS HERE
    //
	unsigned int design[18];
	std::stringstream ss;
do{
//0 = width=( "1" "2" "4" "8" ) 
	design[0] = rand()%4;
//1 = fetchspeed=( "1" "2" ) 
	design[1] = 1;
//2 = scheduling=( "-issue:inorder true -issue:wrongpath false" "-issue:inorder false -issue:wrongpath true" ) 
	design[2] = 0;	
//3 = ruusize=( "4" "8" "16" "32" "64" "128" ) 
	design[3] = rand()%6;
//4 = lsqsize=( "4" "8" "16" "32" )
	design[4] = rand()%4;
//5 = memport=( "1" "2" )
	design[5] = 0;
//6 = dl1sets=( "32" "64" "128" "256" "512" "1024" "2048" "4096" "8192" )
	design[6] = 6;
//7 = dl1assoc=( "1" "2" "4" )
	design[7] = rand()%3;
//8 = il1sets=( "32" "64" "128" "256" "512" "1024" "2048" "4096" "8192" )
	design[8] = 6;
//9 = il1assoc=( "1" "2" "4" )
	design[9] = rand()%3;
//10 = ul2sets=( "256" "512" "1024" "2048" "4096" "8192" "16384" "32768" "65536" "131072" )
	design[10] = 6;
//11 = ul2block=( "16" "32" "64" "128" )
	design[11] = rand()%4;
//12 = ul2assoc=( "1" "2" "4" "8" "16" ) 
	design[12] = 3;
//13 = tlbsets=( "4" "8" "16" "32" "64" )
	design[13] = 2;
//14 = dl1lat=( "1" "2" "3" "4" "5" "6" "7" )
	design[14] = design[0] + 3 + design[6] + 5 + design[7] - 13;
//15 = il1lat=( "1" "2" "3" "4" "5" "6" "7" )
	design[15] = design[0] + 3 + design[8] + 5 + design[9] - 13;
//16 = ul2lat=( "5" "6" "7" "8" "9" "10" "11" "12" "13" )
	design[16] = design[11] + 4 + design[10] + 8 + design[12] - 13 - 4;
//17 = branchsettings=("-bpred perfect" "-bpred nottaken" "-bpred bimod -bpred:bimod 2048" "-bpred 2lev -bpred:2lev 1 1024 8 0" "-bpred 2lev -bpred:2lev 4 256 8 0" "-bpred comb -bpred:comb 1024")
	design[17] = 0;
for(int dim = 0; dim<17; ++dim){
      ss << design[dim] << " ";
    } 
	ss << design[17];
    nextconfiguration=ss.str();
    ss.str("");
}while((GLOB_seen_configurations[nextconfiguration])||(!validateConfiguration(nextconfiguration)));

    //
    //YOUR CODE ENDS HERE
    //
    /*
     * keep the following code in this function as-is.
     */
    if(!validateConfiguration(nextconfiguration)){
      fprintf(stderr,"Exiting with error; Configuration Proposal invalid:\n%s\n", nextconfiguration.c_str());
      exit(-1);
    }
  }
  return nextconfiguration;
}

