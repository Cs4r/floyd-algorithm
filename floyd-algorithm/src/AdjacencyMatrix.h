#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include <vector>
#include <iostream>
/**
 * A Matrix that represents which vertices (or nodes) of a graph are adjacent to which other vertices
 *
 * @author Cs4r
 */
class AdjacencyMatrix {
public:
	AdjacencyMatrix(const std::string& fileName);
	AdjacencyMatrix(const AdjacencyMatrix& other);

	void setEdge(const int unsigned& vertexA, const unsigned int& vertexB,
			const unsigned int& edgeLength);

	unsigned int getEdgeLength(const unsigned int& vertexA,
			const unsigned int& vertexB) const;

	inline unsigned int getNumberOfVertices() const {
		return this->numberOfVertices;
	}

	~AdjacencyMatrix();

private:
	std::vector<unsigned int> adjacencyMatrix;
	unsigned int numberOfVertices;

	void readNumberOfVerticesFromFile(std::ifstream& infile);
	void initializeAdjacencyMatrix(std::ifstream& infile);
	void readVerticesFromFile(std::ifstream& infile);
};

std::ostream & operator<<(std::ostream & stream,
		const AdjacencyMatrix& adjacencyMatrix);

#endif
