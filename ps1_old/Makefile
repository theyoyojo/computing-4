CPPC = g++
CPPFLAGS = -g -ansi -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ_1 = unoriginal.o sierpinski.o triangle.o
OBJ_2 = original.o spoke_tree.o

BIN_1 = sierpinski
BIN_2 = original


all: $(BIN_1) $(BIN_2)
	@echo Make complete.
	
$(BIN_1): $(OBJ_1)
	$(CPPC) $(CPPFLAGS) $^ -o $@ $(LIBS)

$(BIN_2): $(OBJ_2)
	$(CPPC) $(CPPFLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -c $^

clean:
	rm $(BIN_1) $(BIN_2) $(OBJ_1) $(OBJ_2)
