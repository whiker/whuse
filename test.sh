#! /bin/sh
clear
rm -f a.out
echo '-----------------------\n'

proto_dir='./protodir'
proto_obj="$proto_dir/user.o"
protoc -I=$proto_dir --cpp_out=$proto_dir $proto_dir/user.proto
rm -f $proto_obj
g++ -c -I$proto_dir $proto_dir/user.pb.cc -o $proto_obj

g++ -I. \
	-L./leveldb \
	protot.cc  $proto_obj \
	-lprotobuf -luuid -lmysqlclient -lleveldb -lpthread

if [ -f "a.out" ]; then
	./a.out
fi