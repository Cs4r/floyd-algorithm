#include "AdjacencyMatrix.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>

static const int INFINITY = 100000;
static const int BUFFER_SIZE = 100;
static const char* VERTEX_SEPARATOR = " \t";

AdjacencyMatrix::AdjacencyMatrix(const std::string& filename) {
	try {
		std::ifstream infile(filename.c_str());
		if (infile) {
			initializeAdjacencyMatrix(infile);
			return;
		}
	} catch (std::exception& e) {
	}
	throw new std::runtime_error(
			"Unable to read the file with definition of vertices");
}

void AdjacencyMatrix::initializeAdjacencyMatrix(std::ifstream& infile) {
	readNumberOfVerticesFromFile(infile);

	adjacencyMatrix.resize(numberOfVertices * numberOfVertices);

	for (unsigned i = 0; i < numberOfVertices; ++i) {
		unsigned int currentRowShift = i * numberOfVertices;
		for (unsigned j = 0; j < numberOfVertices; ++j) {
			if (i == j) {
				adjacencyMatrix[currentRowShift + j] = 0;
			} else {
				adjacencyMatrix[currentRowShift + j] = INFINITY;
			}
		}
	}

	readVerticesFromFile(infile);
}

void AdjacencyMatrix::readNumberOfVerticesFromFile(std::ifstream& infile) {
	char buffer[BUFFER_SIZE];
	infile.getline(buffer, BUFFER_SIZE, '\n');
	numberOfVertices = (unsigned int) atoi(buffer);
}

void AdjacencyMatrix::readVerticesFromFile(std::ifstream& infile) {
	char buffer[BUFFER_SIZE];

	while (infile.getline(buffer, BUFFER_SIZE) && infile.good() && !infile.eof()) {
		char * vertexAString = buffer;
		char* vertexBString = strpbrk(vertexAString, VERTEX_SEPARATOR);
		*vertexBString++ = '\0';
		char* edgeLengthString = strpbrk(vertexBString, VERTEX_SEPARATOR);
		*edgeLengthString++ = '\0';
		int edgeLength = atoi(edgeLengthString);
		unsigned int vertexA = atoi(vertexAString);
		unsigned int vertexB = atoi(vertexBString);
		adjacencyMatrix[vertexA * numberOfVertices + vertexB] = edgeLength;
	}

}

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& other) {
	this->numberOfVertices = other.numberOfVertices;
	this->adjacencyMatrix = other.adjacencyMatrix;
}

AdjacencyMatrix::~AdjacencyMatrix() {
	/* Nothing to do here */
}

void AdjacencyMatrix::setEdge(const unsigned int& vertexA,
		const unsigned int& vertexB, const unsigned int& edgeLength) {
	adjacencyMatrix[vertexA * numberOfVertices + vertexB] = edgeLength;
}

unsigned int AdjacencyMatrix::getEdgeLength(const unsigned int& vertexA,
		const unsigned int& vertexB) const {
	return adjacencyMatrix[vertexA * numberOfVertices + vertexB];
}

std::ostream & operator<<(std::ostream & stream,
		const AdjacencyMatrix& adjacencyMatrix) {
	int numberOfVertices = adjacencyMatrix.getNumberOfVertices();

	for (int i = 0; i < numberOfVertices; ++i) {
		stream << "[" << i << ",*]= ";

		for (int j = 0; j < numberOfVertices; ++j) {
			if (adjacencyMatrix.getEdgeLength(i, j) == INFINITY) {
				stream << "INF";
			} else {
				stream << adjacencyMatrix.getEdgeLength(i, j);
			}
			if (j < numberOfVertices - 1) {
				stream << ",";
			} else {
				stream << std::endl;
			}
		}
	}

	return stream;
}

