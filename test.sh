#! /bin/sh
clear
rm -f a.out
g++ -I. \
	-L./leveldb \
	mysql.cc \
	-lmysqlclient -lleveldb -lpthread
if [ -f "a.out" ]; then
	./a.out
fi