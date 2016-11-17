CC = g++

OS := $(shell uname)
ifeq ($(OS),Darwin)
	CCFLAGS = -std=c++11 -Wall -I/usr/local/include/cryptopp
else
	CCFLAGS = -std=c++11 -Wall -I/usr/include/cryptopp
endif

LFLAGS = -lcryptopp -lsqlite3

all: gee-mail.cpp
	$(CC) $(CCFLAGS) *.cpp cryptogm/*.cpp GeeMail/*.cpp GraphicEngine/*.cpp $(LFLAGS) -o gee-mail
clean:
	$(RM) gee-mail
