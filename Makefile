CC = g++

OS := $(shell uname)
ifeq ($(OS),Darwin)
	CCFLAGS = -std=c++11 -Wall -I/usr/local/include/cryptopp -lcryptopp -lsqlite3
else
	CCFLAGS = -std=c++11 -Wall -I/usr/include/cryptopp -lcryptopp -lsqlite3
endif

all: gee-mail.cpp
	$(CC) $(CCFLAGS) *.cpp cryptogm/*.cpp GeeMail/*.cpp GraphicEngine/*.cpp  -o gee-mail
clean:
	$(RM) gee-mail
