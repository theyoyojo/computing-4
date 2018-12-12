CPPC = g++
CPPFLAGS = -g -ansi -Wall -Werror -pedantic --std=c++11
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

OBJECTS = GuitarHero.o GuitarString.o RingBuffer.o
OBJECTS_TEST = GuitarString.o RingBuffer.o GStest.o

BIN = GuitarHero

BIN_TEST = test

all: $(BIN) $(BIN_TEST)
	@echo Make complete.
	
$(BIN): $(OBJECTS)
	$(CPPC) $(CPPFLAGS) $^ -o $@ $(LIBS)

$(BIN_TEST): $(OBJECTS_TEST)
	$(CPPC) $(CPPFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -c $^

clean:
	rm $(BIN) $(BIN_TEST) $(OBJECTS_TEST) $(OBJECTS)
