
# 
# compile tool
# compile param
# link    param
# exe file
# *.o file
# compile command 
# link command
#

PROTOC_DIR=./proto-bufc/
CC = gcc
CFLAGS = -Wall -O2 -I${PROTOC_DIR}include/
LDFLAGS = ${PROTOC_DIR}lib/libprotobuf-c.a
TARGET = client server
COBJS = test.pb-c.o example-client.o
SOBJS = test.pb-c.o example-server.o
COMPILE  = $(CC) $(CFLAGS) -MD -c -o $@ $<
LINK = $(CC) $^ $(LDFLAGS) -o $@

ALL:$(TARGET)

client:$(COBJS)
	$(LINK)

server:$(SOBJS)
	$(LINK)

%.o:%.c
	$(COMPILE)
%.pb-c.c:%.proto
	${PROTOC_DIR}bin/protoc-c test.proto --c_out=./

.SECONDARY:
-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) *~ *.d *.o $(TARGET) *pb-c.[ch]
