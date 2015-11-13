#! /bin/sh
clear
rm -f a.out
g++ -I. -L./leveldb main.cc -lleveldb -lpthread
if [ -f "a.out" ]; then
	./a.out
fi