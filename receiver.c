#include "contiki.h"
#include "net/rime/rime.h"
#include "net/netstack.h"

#include "dev/leds.h"
#include "cc2420.h"
#include "cc2420_const.h"
#include <stdio.h>
#include <stdlib.h>

#include "lookup.h"
#define DEBUG 1


//global variables
volatile int recv_rssi;
volatile int tx_pow_index;
double avg_rssi[NUM_POWER_LEVELS][NUM_MATERIALS];
extern int tx_pow[NUM_POWER_LEVELS];


/*---------------------------------------------------------------------------*/
PROCESS(receiver, "Receiver");
AUTOSTART_PROCESSES(&receiver);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
	//read rssi
	recv_rssi = packetbuf_attr(PACKETBUF_ATTR_RSSI);
  
	//print power level and rssi
	tx_pow_index = atoi((char *)packetbuf_dataptr());
	if(DEBUG){
		printf("%d, %d\n", tx_pow[tx_pow_index], recv_rssi);
		printf("index: %d\n", tx_pow_index);
	}

	print_guess( make_guess(tx_pow_index, recv_rssi, avg_rssi));
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*
*---------------------------------------------------------------------------
*/

PROCESS_THREAD(receiver, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  setupMaterial(avg_rssi);

  PROCESS_BEGIN();

  cc2420_on();

  leds_off(LEDS_ALL);

  broadcast_open(&broadcast, 129, &broadcast_call);

  int temp = 0;

  while(1){
    	/* Delay 2 seconds */
    	etimer_set(&et, CLOCK_SECOND * 5);
    	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
	
	temp++;
	//printf("blah: %d\n", temp);
  }

  PROCESS_END();
}
