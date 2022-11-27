SRC         := commlog.cpp
OBJS        := commlog.o
TARGET      := libcommlog.a
CC          := g++
CXXFLAGS    := -std=c++11

AR          := ar

$(TARGET): $(OBJS)
	$(AR) rcv $@ $^
	cp -f $@ ../lib/

$(OBJS): $(SRC)
	$(CC) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -fr *.o *.a