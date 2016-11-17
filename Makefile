CC = g++

OS := $(shell uname)
ifeq ($(OS),Darwin)
	CCFLAGS = -I/usr/local/include/cryptopp -std=c++11 -Wall -lcryptopp -lsqlite3
else
	CCFLAGS = -I/usr/include/cryptopp -std=c++11 -Wall -lcryptopp -lsqlite3
endif

all: gee-mail.cpp
	$(CC) $(CCFLAGS) *.cpp cryptogm/*.cpp GeeMail/*.cpp GraphicEngine/*.cpp  -o gee-mail
clean:
	$(RM) gee-mail
