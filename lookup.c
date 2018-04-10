#include "lookup.h"
#include <stdio.h>

int tx_pow[] = {3, 5, 11, 23, 30};

/*
used to initialize the material structs
*/
void setupMaterial(double arr[NUM_POWER_LEVELS][NUM_MATERIALS]){
	arr[0][NONE]    = -63.0;
	arr[0][WOOD]    = -64.0;
	arr[0][CERAMIC] = -68.0;
	arr[0][METAL]   = -53.0;
	arr[0][FOAM]    = -64.0;

	arr[1][NONE]    = -56.0;
	arr[1][WOOD]    = -54.0;
	arr[1][CERAMIC] = -62.0;
	arr[1][METAL]   = -51.0;
	arr[1][FOAM]    = -58.0;

	arr[2][NONE]    = -47.0;
	arr[2][WOOD]    = -49.0;
	arr[2][CERAMIC] = -56.0;
	arr[2][METAL]   = -42.0;
	arr[2][FOAM]    = -52.0;

	arr[3][NONE]    = -41.0;
	arr[3][WOOD]    = -41.0;
	arr[3][CERAMIC] = -50.0;
	arr[3][METAL]   = -38.0;
	arr[3][FOAM]    = -43.0;

	arr[4][NONE]    = -39.0;
	arr[4][WOOD]    = -37.0;
	arr[4][CERAMIC] = -47.0;
	arr[4][METAL]   = -33.0;
	arr[4][FOAM]    = -41.0;
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

