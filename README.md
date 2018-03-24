# floyd-algorithm
Several parallel implementations of Floyd-Warshall algorithm


About Floyd-Warshall algorithm:

Floyd-Warshall algorithm is a dynamic programming solution to all pairs shortest paths problem. F-W algorithm finds the shortest paths lengths between all pairs of vertices. Unlike Dijkstra's algorithm, F-W algorithm is able to handle negative weight edges. Negative weight cycles are still not allowed. The time complexity of F-W algorithm is O(n^3).


The recurrence of Floyd-Warshall algorithm:
- IF k = 0 and i = j, then Array(k, i, j) = 0,
- If k = 0 and i ≠ j, then Array(k, i, j) = c(i, j),
- IF k > 0, then Array(k, i, j) = min{ Array(k-1, i, j), Array(k-1, i, k) + Array(k-1, k, j) },
- where, k is the intermmeidate vertex between vertices i and j, and c(i, j) is the cost of the edge between vertices i and j.
