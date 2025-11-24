



CXX   := g++
BIN   := crypt
UNITS := crypto.o io.o LA.o
RM    := rm -f
FLAGS := 
LIBS  := 

all: $(UNITS)
	$(GXX) -o $(BIN) main.cpp $^ $(FLAGS) $(LIBS)

%.o: %.c
	$(GXX) -c -o $@ $< $^ $(FLAGS)

clean:
	$(RM) $(UNITS) $(BIN)