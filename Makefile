CC = g++ 
ONEDIMENSIONAL_MP = OneDimensionalFloyd
TWODIMENSIONAL_MP = TwoDimensionalFloyd
BIN = bin
OBJ = obj
SRC = src
SRC_MP = $(SRC)/multiprocessor
CFLAGS = -fopenmp -O2 -fexceptions

all: $(ONEDIMENSIONAL_MP) $(TWODIMENSIONAL_MP)

$(ONEDIMENSIONAL_MP) : $(OBJ)/OneDimensionalFloyd.o $(OBJ)/AdjacencyMatrix.o
	$(CC) $(CFLAGS) $(OBJ)/OneDimensionalFloyd.o $(OBJ)/AdjacencyMatrix.o -o $(BIN)/$(ONEDIMENSIONAL_MP)
	
$(TWODIMENSIONAL_MP) : $(OBJ)/TwoDimensionalFloyd.o $(OBJ)/AdjacencyMatrix.o
	$(CC) $(CFLAGS) $(OBJ)/TwoDimensionalFloyd.o $(OBJ)/AdjacencyMatrix.o -o $(BIN)/$(TWODIMENSIONAL_MP)
	
$(OBJ)/AdjacencyMatrix.o : $(SRC)/AdjacencyMatrix.cpp $(SRC)/AdjacencyMatrix.h
	$(CC) $(CFLAGS) -c $(SRC)/AdjacencyMatrix.cpp -o $(OBJ)/AdjacencyMatrix.o
	
$(OBJ)/OneDimensionalFloyd.o : $(SRC_MP)/OneDimensionalFloyd.cpp
	$(CC) $(CFLAGS) -c $(SRC_MP)/OneDimensionalFloyd.cpp -o $(OBJ)/OneDimensionalFloyd.o
	
$(OBJ)/TwoDimensionalFloyd.o : $(SRC_MP)/TwoDimensionalFloyd.cpp
	$(CC) $(CFLAGS) -c $(SRC_MP)/TwoDimensionalFloyd.cpp -o $(OBJ)/TwoDimensionalFloyd.o
	

clean:
	rm -f $(BIN)/*
	rm -rf $(OBJ)/*.o