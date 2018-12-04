CPPC = g++
CPPFLAGS = -g -ansi -Wall -Werror -pedantic --std=c++11
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

OBJECTS = ps5a-test.o RingBuffer.o test.o

BIN = ps5a

all: $(BIN)
	@echo Make complete.
	
$(BIN): $(OBJECTS)
	$(CPPC) $(CPPFLAGS) $(OBJECTS) -o $(BIN) $(LIBS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -c $^

clean:
	rm $(BIN) $(OBJECTS)
