CONTIKI = ..
ifndef TARGET
TARGET=sky
endif

all: sender receiver

PROJECT_SOURCEFILES += lookup.c
CONTIKI_WITH_RIME = 1
include $(CONTIKI)/Makefile.include
