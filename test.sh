#! /bin/sh
clear
rm -f a.out
echo '-----------------------------\n\n\n'
g++ -I. \
	-L./leveldb \
	rapidjson.cc \
	-luuid -lmysqlclient -lleveldb -lpthread
if [ -f "a.out" ]; then
	./a.out
fi