CPPC = g++
CPPFLAGS = -g -ansi -Wall -Werror -pedantic --std=c++11
LIBS = -lboost_unit_test_framework

OBJECTS = main.o LFSR.o
OBJECTS_TEST = test.o LFSR.o

BIN = app
BIN_TEST = ps2a

all: $(BIN) $(BIN_TEST)
	@echo Make complete.
	
$(BIN): $(OBJECTS)
	$(CPPC) $(CPPFLAGS) $^ -o $@  $(LIBS)

$(BIN_TEST): $(OBJECTS_TEST)
	$(CPPC) $(CPPFLAGS) $^ -o $@  $(LIBS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -c $^

clean:
	rm $(BIN) $(OBJECTS) $(BIN_TEST) $(OBJECTS_TEST)
