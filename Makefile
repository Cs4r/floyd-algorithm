CC = g++ 
ONEDIMENSIONAL_MP = OneDimensionalFloyd
BIN = bin
OBJ = obj
SRC = src
SRC_ONEDIMENSIONAL_MP = $(SRC)/multiprocessor
CFLAGS = -fopenmp -O2

all: $(ONEDIMENSIONAL_MP)

$(ONEDIMENSIONAL_MP) : $(OBJ)/OneDimensionalFloyd.o $(OBJ)/AdjacencyMatrix.o
	$(CC) $(CFLAGS) $(OBJ)/OneDimensionalFloyd.o $(OBJ)/AdjacencyMatrix.o -o $(BIN)/$(ONEDIMENSIONAL_MP)
	
$(OBJ)/AdjacencyMatrix.o : $(SRC)/AdjacencyMatrix.cpp $(SRC)/AdjacencyMatrix.h
	$(CC) $(CFLAGS) -c $(SRC)/AdjacencyMatrix.cpp -o $(OBJ)/AdjacencyMatrix.o
	
$(OBJ)/OneDimensionalFloyd.o : $(SRC_ONEDIMENSIONAL_MP)/OneDimensionalFloyd.cpp
	$(CC) $(CFLAGS) -c $(SRC_ONEDIMENSIONAL_MP)/OneDimensionalFloyd.cpp -o $(OBJ)/OneDimensionalFloyd.o
	

clean:
	rm -f $(BIN)/*
	rm -rf $(OBJ)/*.o