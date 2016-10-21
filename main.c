/*
 * main.c
 *
 *  Created on: Oct 15, 2016
 *      Author: Ugo
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define LIMIT 100000000 //Check numbers up to LIMIT (100M)
#define PRIME 10000000 //Store prime numbers (10M)
#define OUT1 "prime_numbers.txt" //Output file
#define OUT2 "debug.txt" //Debugging info

#define DEBUG 0 //Turn to 1 for debugging purposes

//TODO : Implement segmented sieve

int main(){

	unsigned long long int i, j, count;
	//static int number[LIMIT], prime[PRIME];
	int *number = malloc(LIMIT * sizeof(int));
	int *prime = malloc(PRIME * sizeof(int));
	//Large arrays need to be declared statically or dynamically using malloc
	//(both methods work up to ~100M integers arrays)
	clock_t starttime, endtime;
	double runtime;

	FILE *output, *output2;

	output = fopen(OUT1,"w");
	if(DEBUG>=1) output2 = fopen(OUT2,"w");

	starttime = clock();
	//Fill the number array starting from 2 to LIMIT+1
	for(i=0;i<LIMIT;i++){
		number[i]=i+2;
	}

	for(i=0;i<LIMIT;i++){
		if(number[i]!=-1){ //No need to test if we already flagged a number
			j=number[i]; //The first number in the list is prime
			if(DEBUG>=1) fprintf(output2,"%d should be prime\n",number[i]);
			while(j<LIMIT){
				j+=number[i]; //Multiples are NOT prime..
				if(j<=LIMIT && number[j-2]!=-1 && DEBUG >=1) fprintf(output2,"%I64u\t%d\n",j,number[j-2]);
				if(j<=LIMIT) number[j-2]=-1; //.. so we flag them
				//Conditionnal IF added because number[j-2] can fall out of bounds..
				//..and generate errors because we're dealing with random values in memory
				//NOTE: number[j-2] is the tabulated value that is equal to j
			}

		}
	}

	count=0; //initialize count of primes
	for(i=0;i<LIMIT;i++){
		if(number[i]!=-1 && number[i] <= LIMIT){ //If number isn't flagged (and within the LIMIT)..
			prime[count++]=number[i]; //.. add it to the list of primes and update count
		}
	}

	fprintf(output,"Number of prime numbers up to %d is : %I64u\n\nList:\n\n",LIMIT,count);

	for(i=0;i<count;i++){
		fprintf(output,"%d\n",prime[i]); //Print the primes
	}

	fclose(output);
	if(DEBUG>=1) fclose(output2);
	endtime = clock();
	runtime = ((double) (endtime - starttime)) / CLOCKS_PER_SEC;
	printf("Runtime is %lf\n", runtime);
	getchar();
	return 0;
}
