#! /bin/sh
clear
rm -f a.out
g++ -I. \
	-L./leveldb -L./mysql \
	main.cc \
	-lmysqlclient -lleveldb -lpthread
if [ -f "a.out" ]; then
	./a.out
fi