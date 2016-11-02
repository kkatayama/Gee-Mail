# Gee-Mail
A secure asynchronous (same-machine) message platform


#ubuntu (cloud 9)
>###Install Libraries
>sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

>###Compile
>g++ -Wall -I/usr/include/cryptopp -o gee-mail \*.cpp sha256/\*.cpp -lcryptopp

#osx
>###Install Libraries
>brew install boost

>brew install cryptopp

>###Complie
>g++ -std=c++11 -Wall -I/usr/local/include/cryptopp \*.cpp cryptogm/\*.cpp -lcryptopp -lsqlite3 -o gee-mail


#docs
>https://github.com/iwongu/sqlite3pp
>https://cryptopp.com/wiki/Advanced_Encryption_Standard
