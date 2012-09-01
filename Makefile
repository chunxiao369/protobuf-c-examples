
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
TARGET = pack_unpack
OBJS = amessage.pb-c.o test4.o 
COMPILE  = $(CC) $(CFLAGS) -MD -c -o $@ $<
LINK = $(CC) $(OBJS) $(LDFLAGS) -o $@

ALL:$(TARGET)

$(TARGET):$(OBJS)
	$(LINK)

%.o:%.c
	$(COMPILE)
%.pb-c.c:%.proto
	${PROTOC_DIR}bin/protoc-c amessage.proto --c_out=./

-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) *~ *.d *.o $(TARGET) *pb-c.[ch]
