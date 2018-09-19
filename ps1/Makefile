CPPC = g++
CPPFLAGS = -g -ansi -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = main.o PTree.o

BIN = PTree

all: $(BIN)
	@echo Make complete.
	
$(BIN): $(OBJECTS)
	$(CPPC) $(CPPFLAGS) $(OBJECTS) -o $(BIN) $(LIBS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -c $^

clean:
	rm $(BIN) $(OBJECTS)
