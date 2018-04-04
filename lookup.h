#define TX_POW_LEN 5

/*
Materials
*/
typedef struct material {
	//index of avg_rssi matches index in tx_pow
	double avg_rssi[TX_POW_LEN];
	double length_in_meters;
} material_t;

material_t wood, ceramic, metal, foam;


/*
Prototypes
*/
void setupMaterial();
void setupMaterialHelper(material_t* material, double avg_rssi[TX_POW_LEN], double length);

