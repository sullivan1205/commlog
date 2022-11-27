SRC         := example.cpp
OBJS        := example.o
LIBS        := -lcommlog
TARGET      := example
CC          := g++
CXXFLAGS    := -std=c++11
LDFLAGS     := -L../lib

$(TARGET): $(OBJS)
	$(CC) $(LIBS) $(LDFLAGS) $(CXXFLAGS) -o $@ $^

$(OBJS): $(SRC)
	$(CC) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -fr *.o $(TARGET)