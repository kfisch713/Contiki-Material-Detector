#include "contiki.h"
#include "net/rime/rime.h"
#include "net/netstack.h"

#include "dev/leds.h"
#include "cc2420.h"
#include "cc2420_const.h"
#include <stdio.h>

#include "lookup.h"

//number of transmissions at each power level
#define NUM_TRANS 20

#define TX_BUF_LEN 6
char tx_buf[TX_BUF_LEN];


//global variables
volatile int recv_rssi;


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
	printf("%s, %d\n", (char *)packetbuf_dataptr(), recv_rssi);
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

  setupMaterial();

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
	printf("blah: %d\n", temp);
  }

  PROCESS_END();
}
