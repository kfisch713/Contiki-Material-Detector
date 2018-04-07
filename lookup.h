
#define TX_POW_LEN 5
#define NUM_MATERIALS 5
#define NUM_POWER_LEVELS 5
#define NONE 0
#define WOOD 1
#define CERAMIC 2
#define METAL 3
#define FOAM 4

/*
Prototypes
*/
void setupMaterial(double arr[NUM_POWER_LEVELS][NUM_MATERIALS]);
void print_guess(int guess);
int make_guess(int power_level_index, int recv_rssi, double avg_rssi[NUM_POWER_LEVELS][NUM_MATERIALS]);

