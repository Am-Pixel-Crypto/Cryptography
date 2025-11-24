



CXX   := g++
BIN   := crypt
UNITS := crypto.o io.o LA.o
RM    := rm -f
FLAGS := 
LIBS  := 

all: $(UNITS)
	$(CXX) -o $(BIN) main.cpp $^ $(FLAGS) $(LIBS)

%.o: %.c
	$(CXX) -c -o $@ $< $^ $(FLAGS)

clean:
	$(RM) $(UNITS) $(BIN)