protobuf-c-examples
===================

protocol buffers; C language; examples

1. What is protocol buffer
    https://developers.google.com/protocol-buffers/docs/overview

2. What is protocol buffer c
    Dave Benson
    http://code.google.com/p/protobuf-c/

3. How to install
    /mnt/share_disk/program-source/protobuf-c-0.14/configure\
    --prefix=/mnt/share_disk/program-files/proto-buffc/\
    CXXFLAGS=-I/mnt/share_disk/program-files/proto-buff/include\
    LDFLAGS=-L/mnt/share_disk/program-files/proto-buff/lib/\
    PROTOC=/mnt/share_disk/program-files/proto-buff/bin/protoc

4. The compare to other serialize tools
    http://code.google.com/p/thrift-protobuf-compare/wiki/Benchmarking

5. How to exec client and server example
    1)
    ./server --unix=/tmp/a --database=database
    ./client --unix=/tmp/a
    2)
    ./server --port=3333 --database=database
    ./client --tcp=127.0.0.1:3333
