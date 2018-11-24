CC = g++
CFLAGS = -c -Og -g -std=c++11
OBJ = Airplane.o Airport.o AirportRunways.o AirportServer.o
DEPS = 
LIBS = -pthread
EXE = Airport-Sync

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(EXE)
