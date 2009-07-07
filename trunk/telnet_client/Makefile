# Makefile for my telnet client
# by liuw
# liuw@liuw.name

RM 	= rm -f
TAGPROG	= cscope -Rb
CC	= gcc

all:
	$(CC) -Iinclude telnet_parse.c main.c -o telnet

debug:
	$(CC) -g -Iinlcude telnet_parse.c main.c -o telnet

tags:
	$(TAGPROG)

clean:
	$(RM) telnet cscope.out