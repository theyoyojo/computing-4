CPPC = g++
CPPFLAGS = -g -ansi -Wall -Werror -pedantic --std=c++11
LIBS = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = PhotoMagic.o LFSR.o

BIN = PhotoMagic

all: $(BIN)
	@echo Make complete.
	
$(BIN): $(OBJECTS)
	$(CPPC) $(CPPFLAGS) $^ -o $@  $(LIBS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -c $^

clean:
	rm $(BIN) $(OBJECTS)
