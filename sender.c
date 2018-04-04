#include "contiki.h"
#include "net/rime/rime.h"
#include "net/netstack.h"

#include "dev/leds.h"
#include "cc2420.h"
#include "cc2420_const.h"
#include <stdio.h>

#include "lookup.h"

volatile int current_rssi;

//number of transmissions at each power level
#define NUM_TRANS 20

#define TX_BUF_LEN 6
char tx_buf[TX_BUF_LEN];


//variables to control tx power
int tx_pow[] = {3, 5, 11, 23, 30};

volatile int power_level_index = 0;
volatile int transmission_counter = 0;

/*---------------------------------------------------------------------------*/
PROCESS(sender, "Sender");
AUTOSTART_PROCESSES(&sender);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
	//do nothing on receive
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*
*---------------------------------------------------------------------------
*/
void updateLEDs(int index){
	leds_off(LEDS_ALL);	

	switch(index){
		case 0:
			leds_off(LEDS_ALL);
			break;
		case 1:
			leds_on(LEDS_RED);
			break;
		case 2:
			leds_on(LEDS_GREEN);
			break;
		case 3:
			leds_on(LEDS_GREEN | LEDS_RED);
			break;
		case 4:
			leds_on(LEDS_BLUE);
			break;
		case 5: 
			leds_on(LEDS_BLUE | LEDS_RED);
			break;
		default:
			//something weird happened so turn on all leds
			leds_on(LEDS_ALL);
			break;
	}
}
/*
*---------------------------------------------------------------------------
*/
PROCESS_THREAD(sender, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  cc2420_on();

  leds_off(LEDS_ALL);

  broadcast_open(&broadcast, 129, &broadcast_call);

  //print labels
  printf("Power level\n");

  while(1){
    //change power level
    if(transmission_counter > NUM_TRANS-1){
	power_level_index++;
	transmission_counter = 0;
    }
    
    //check if we are at the last power level in the list and loop back around
    if(power_level_index >= TX_POW_LEN){
	power_level_index = 0;
    }

    updateLEDs(power_level_index);

    //update tx_buf
    sprintf(tx_buf, "%d", tx_pow[power_level_index]);

    /* Delay 2 seconds */
    etimer_set(&et, CLOCK_SECOND * 2);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    /* Set the power level */
    cc2420_set_txpower(tx_pow[power_level_index]);
    transmission_counter++;

    //send message so we can get an RSSI
    packetbuf_copyfrom(tx_buf, TX_BUF_LEN);
    broadcast_send(&broadcast);

    printf("%s\n", tx_buf);
  }

  PROCESS_END();
}
