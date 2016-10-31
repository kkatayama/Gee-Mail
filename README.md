# Gee-Mail
A secure asynchronous (same-machine) message platform


#ubuntu
>###Install Libraries
>sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

>###Compile
>g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp *.cpp sha256/*.cpp -o gee-mail -lcryptopp -lpthread

#osx
>###Install Libraries
>brew install boost
>brew install cryptopp

>###Complie
>g++ -g3 -ggdb -O0 -DDEBUG -I/usr/local/include/cryptopp *.cpp sha256/*.cpp -o gee-mail -lcryptopp -lpthread

