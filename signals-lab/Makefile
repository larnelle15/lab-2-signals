# Makefile for Signals Lab
CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2

.PHONY: all clean signals

all: signal1 signal2 timer
signals: all

signal1: signal1.c
	$(CC) $(CFLAGS) -o $@ $<

signal2: signal2.c
	$(CC) $(CFLAGS) -o $@ $<

timer: timer.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f signal1 signal2 timer
