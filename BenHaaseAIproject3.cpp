// AIp3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
using namespace std;

//prototypes
void runGA(string *, int, int, double);
void fillPop(string *, int, int);
void displayPop(string *, int);
int fitnessSingle(string);
double fitStats(string *, int);
string * crossOver(string, string);
int main()
{
	srand(time(NULL)); //seed random
	int popSize = 0; //hold population size
	int strSize = 0; //hold string size
	//get these values
	cout << "Enter population size: ";
	cin >> popSize;
	cout << "Enter string size: ";
	cin >> strSize;
	cout << endl;
	string * population = new string[popSize]; //create string* to hold population
	fillPop(population, popSize, strSize); //fill population with random strings
	double avg = fitStats(population, popSize); //get starting average
	runGA(population, popSize, strSize, avg); //run the GA

	return 0;
}

//perferm the main operations and calls of the GA
void runGA(string * pop, int ps, int ss, double avg){
	string * nPop = new string[ps]; //hold new population
	//hold string values when doing operations to add to new population
	string a;
	string b;
	string c;
	string * d;
	double navg = 0;
	for(int i=0; i<=((ps/2)-1); i++){
		//tournament selections
		a = pop[rand()%ps];
		c = pop[rand()%ps];
		if(fitnessSingle(a) < fitnessSingle(c)) a = c;
		b = pop[rand()%ps];
		c = pop[rand()%ps];
		if(fitnessSingle(b) < fitnessSingle(c)) b = c;
		//take crossover 60% of time
		int co = rand()%202; //formatted this way for better number spread
		//crossover and add to new population
		if(co%5!=0){
			d = crossOver(a,b);
			nPop[2*i] = d[0];
			nPop[(2*i)+1] = d[1];
			delete [] d;
		}
		//if did not cross over, copy to new population
		else{
			nPop[2*i] = a;
			nPop[(2*i)+1] = b;
		}
	}
	//find the best 2 strings in population
	a = pop[0];
	for(int i=0; i<ps; i++){
		if(fitnessSingle(pop[i])>fitnessSingle(a)){
			b = a;
			a = pop[i];
		}
		else if(fitnessSingle(pop[i])>fitnessSingle(b)) b = pop[i];
	}
	//add these strings to new population
	nPop[ps-2] = a;
	nPop[ps-1] = b;
	//calculate new average and output stats
	navg = fitStats(nPop, ps);
	delete [] pop; //cleanup
	//recursive call, or terminate if average goes down or global optimum reached
	if(navg > avg && navg!=ss){
		runGA(nPop, ps, ss, navg);
	}
	else{
		delete [] nPop; //cleanup
	}
}

//random gen each string
void fillPop(string * pop, int ps, int ss){
	for(int i=0; i<ps; i++){
		for(int k=0; k<ss; k++){
			if((rand()%100)%2!=0) pop[i] += '1'; //formatted for better spread
			else pop[i] += '0';
		}
	}
}

//show the population at a given time (not used except in my testing)
void displayPop(string * pop, int ps){
	for(int i=0; i<ps; i++) cout << pop[i] << " f: " << fitnessSingle(pop[i]) << endl;
}

//get the fitness of a single string
int fitnessSingle(string s){
	int f = 0;
	for(int i=0; i<s.length(); i++) if(s[i] == '1') f++;
	return f;
}

//calculate the averge fitness and find the highest and lowest fitness
double fitStats(string * pop, int s){
	int low = fitnessSingle(pop[0]);
	int high = fitnessSingle(pop[0]);
	double avg = 0;
	int temp = 0;

	for(int i=0; i<s; i++){
		temp = fitnessSingle(pop[i]);
		if(temp<low) low = temp;
		if(temp>high) high = temp;
		avg += temp;
	}
	avg = (avg/s);
	//output stats
	cout << "Average fitness: " << avg << endl;
	cout << "Best: " << high << endl;
	cout << "Worst: " << low << endl;
	return avg;
}

//perform the crossover operation and return a pointer with the two created strings
string * crossOver(string a, string b){
	string c;
	string d;
	string * e = new string[2];
	for(int i=0; i<a.length(); i++){
		if((rand()%100)%2!=0){ //formatted for better spread
			c += a[i];
			d += b[i];
		}
		else{
			c += b[i];
			d += a[i];
		}
	}
	e[0] = c;
	e[1] = d;
	return e;
}