# Gee-Mail
A secure asynchronous (same-machine) message platform


#ubuntu
>###Install Libraries
>sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

>###Compile
>g++ -Wall -I/usr/include/cryptopp -o gee-mail \*.cpp sha256/\*.cpp -lcryptopp

#osx
>###Install Libraries
>brew install boost
>brew install cryptopp

>###Complie
>g++ -Wall -I/usr/local/include/cryptopp -o gee-mail \*.cpp sha256/\*.cpp -lcryptopp

