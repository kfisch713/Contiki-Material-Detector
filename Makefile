CONTIKI = ../
ifndef TARGET
TARGET=sky
endif

all: <INSERT FILE NAME HERE>


CONTIKI_WITH_IPV4 = 1
CONTIKI_WITH_RIME = 1
include $(CONTIKI)/Makefile.include
