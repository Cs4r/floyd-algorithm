#include <iostream>
#include <omp.h>
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include <math.h>
#include "../AdjacencyMatrix.h"
using namespace std;

/**
 * Parallel implementation of Floyd-Warshall algorithm using Open MP.
 *
 * Computation of matrix with shortest paths between all pairs of vertices is done distributing
 * rows and columns of the adjacency matrix between threads. That's say it is based on a two-dimensional,
 * blockwise domain decomposition of the adjacency matrix.
 *
 *
 * @author Cs4r
 */
void parallelFloyd(AdjacencyMatrix& adyacencyMatrix);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cerr << "Wrong execution!" << endl;
		cout << "Syntax:\t" << argv[0]
				<< " <adjacency_matrix_file> <number_of_threads>" << endl;
		exit(EXIT_FAILURE);
	}

	try {
		unsigned int numberOfVertices;
		unsigned int numberOfThreads;
		unsigned int sqrtOfnumberOfThreads;
		double t1, t2, elapsedTime;
		AdjacencyMatrix adyacencyMatrix(argv[1]);

		numberOfVertices = adyacencyMatrix.getNumberOfVertices();
		numberOfThreads = atoi(argv[2]);
		sqrtOfnumberOfThreads = sqrt(numberOfThreads);

		if (sqrt(numberOfThreads) != (double) sqrtOfnumberOfThreads
				|| numberOfVertices % sqrtOfnumberOfThreads != 0) {
			throw new runtime_error(
					"Number of vertices must be a multiple of the square root of the number of threads");
		}

		cout << "Number of vertices: " << numberOfVertices << endl;
		cout << "Number of threads: " << numberOfThreads << endl;

		omp_set_num_threads(numberOfThreads);

		t1 = omp_get_wtime();
		parallelFloyd(adyacencyMatrix);
		t2 = omp_get_wtime();

		elapsedTime = t2 - t1;
//		cout << "Matrix with shortest paths between all pairs of vertices is:"
//				<< endl << endl << adyacencyMatrix;
		cout << endl << "Elapsed time = " << elapsedTime << endl;

		exit(EXIT_SUCCESS);
	} catch (exception* error) {
		cerr << "Could not carry out floyd's algorithm execution. Reason: "
				<< error->what() << endl;
		exit(EXIT_FAILURE);
	}
}

void parallelFloyd(AdjacencyMatrix& adyacencyMatrix) {
	unsigned int k, i, j;
	unsigned int lengthFromItoK, lengthFromItoKAndFromKToJ;
	unsigned int numberOfVertices = adyacencyMatrix.getNumberOfVertices();
	unsigned int sqrtOfnumberOfThreads = sqrt(omp_get_max_threads());
	unsigned int blockSize = numberOfVertices / sqrtOfnumberOfThreads;
	unsigned int initialRow, lastRow;
	unsigned int initialColumn, lastColumn;
	unsigned int threadNumber;
	vector<int> kthRow(numberOfVertices);
	vector<int> kthColumn(numberOfVertices);

	#pragma omp parallel shared(adyacencyMatrix, numberOfVertices, sqrtOfnumberOfThreads, blockSize) private(k,i,j, lengthFromItoK, lengthFromItoKAndFromKToJ, threadNumber, initialRow, lastRow, initialColumn, lastColumn) firstprivate(kthRow, kthColumn)
	{
		threadNumber = omp_get_thread_num();

		initialRow = (threadNumber / sqrtOfnumberOfThreads) * blockSize;
		lastRow = initialRow + blockSize;

		initialColumn = (threadNumber % sqrtOfnumberOfThreads) * blockSize;
		lastColumn = initialColumn + blockSize;

		for (k = 0; k < numberOfVertices; k++) {
			#pragma omp barrier
			for (i = 0; i < numberOfVertices; ++i) {
				kthRow[i] = adyacencyMatrix.getEdgeLength(k, i);
				kthColumn[i] = adyacencyMatrix.getEdgeLength(i, k);
			}
			#pragma omp barrier
			for (i = initialRow; i < lastRow; ++i) {
				lengthFromItoK = kthColumn[i];
				for (j = initialColumn; j < lastColumn; ++j) {
					if (i != j && i != k && j != k) {
						lengthFromItoKAndFromKToJ = lengthFromItoK + kthRow[j];
						unsigned int minLength = min(lengthFromItoKAndFromKToJ,
								adyacencyMatrix.getEdgeLength(i, j));
						adyacencyMatrix.setEdge(i, j, minLength);
					}
				}
			}
		}
	}
}
