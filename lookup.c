#include "lookup.h"

extern material_t wood, ceramic, metal, foam;

/*
used to initialize the material structs
*/
void setupMaterial(){
	double wood_init[] = {0, 0, 0, 0, 0};
	double ceramic_init[] = {0, 0, 0, 0, 0};
	double metal_init[] = {0, 0, 0, 0, 0};
	double foam_init[] = {0, 0, 0, 0, 0};

	double wood_length = 0.0;
	double ceramic_length = 0.0;
	double metal_length = 0.0;
	double foam_length = 0.0;
	
	setupMaterialHelper(&wood, wood_init, wood_length);
	setupMaterialHelper(&ceramic, ceramic_init, ceramic_length);
	setupMaterialHelper(&metal, metal_init, metal_length);
	setupMaterialHelper(&foam, foam_init, foam_length);

}

/*
helper method to initialize the material structs
*/
void setupMaterialHelper(material_t* material, double avg_rssi[TX_POW_LEN], double length){
	int i;
	for(i=0; i<TX_POW_LEN; i++){
		material->avg_rssi[i] = avg_rssi[i];
	}

	material->length_in_meters = length;
}

