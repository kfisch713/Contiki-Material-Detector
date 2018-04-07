#include "lookup.h"
#include <stdio.h>

int tx_pow[] = {3, 5, 11, 23, 30};

/*
used to initialize the material structs
*/
void setupMaterial(double arr[NUM_POWER_LEVELS][NUM_MATERIALS]){
	arr[0][NONE]    = -70.0;
	arr[0][WOOD]    = 0.0;
	arr[0][CERAMIC] = 0.0;
	arr[0][METAL]   = 0.0;
	arr[0][FOAM]    = 0.0;

	arr[1][NONE]    = 0.0;
	arr[1][WOOD]    = -70.0;
	arr[1][CERAMIC] = 0.0;
	arr[1][METAL]   = 0.0;
	arr[1][FOAM]    = 0.0;

	arr[2][NONE]    = 0.0;
	arr[2][WOOD]    = 0.0;
	arr[2][CERAMIC] = -70.0;
	arr[2][METAL]   = 0.0;
	arr[2][FOAM]    = 0.0;

	arr[3][NONE]    = 0.0;
	arr[3][WOOD]    = 0.0;
	arr[3][CERAMIC] = 0.0;
	arr[3][METAL]   = -70.0;
	arr[3][FOAM]    = 0.0;

	arr[4][NONE]    = 0.0;
	arr[4][WOOD]    = 0.0;
	arr[4][CERAMIC] = 0.0;
	arr[4][METAL]   = 0.0;
	arr[4][FOAM]    = -70.0;
}

int make_guess(int power_level_index, int recv_rssi, double avg_rssi[NUM_POWER_LEVELS][NUM_MATERIALS]){

	int guess = NONE;
	/* use dist^2 instead of dist so we only have to worry about magnitude */
	double dist2 = recv_rssi - avg_rssi[power_level_index][NONE];
	dist2 = dist2*dist2;
	double temp2;


	/* I really want to do this in a loop but I'm watching tv while coding this
	   and I can't think of a robust way to loop without knowing the order of 
	   avg_rssi */
	temp2 = recv_rssi - avg_rssi[power_level_index][WOOD];
	temp2 = temp2*temp2;
	if(temp2 < dist2){
		dist2 = temp2;
		guess = WOOD;
	}

	temp2 = recv_rssi - avg_rssi[power_level_index][CERAMIC];
	temp2 = temp2*temp2;
	if(temp2 < dist2){
		dist2 = temp2;
		guess = CERAMIC;
	}

	temp2 = recv_rssi - avg_rssi[power_level_index][METAL];
	temp2 = temp2*temp2;
	if(temp2 < dist2){
		dist2 = temp2;
		guess = METAL;
	}

	temp2 = recv_rssi - avg_rssi[power_level_index][FOAM];
	temp2 = temp2*temp2;
	if(temp2 < dist2){
		dist2 = temp2;
		guess = FOAM;
	}
	
	return guess;
}

void print_guess(int guess){
	printf("Best guess is ");
	switch(guess){
		case NONE: printf("no material"); break;
		case WOOD: printf("wood"); break;
		case CERAMIC: printf("ceramic tile"); break;
		case METAL: printf("metal sheet"); break;
		case FOAM: printf("styrofoam"); break;
	}

	printf("\n");
}

