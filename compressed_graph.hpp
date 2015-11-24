#ifndef __COMPRESSEDGRAPH__
#define __COMPRESSEDGRAPH__

#include <iostream>
#include <bitset>
#include <vector>

template <unsigned int n>
class CompressedGraph {
    private:
        unsigned int num_verts = n;
        std::vector<std::bitset<n>> adjacency_matrix; // vector stores bitsets of length n

    public:
        CompressedGraph()
        {
            unsigned int i;
            for (i = 0; i < n; i++) {
                std::bitset<n> b;
                adjacency_matrix.push_back(b);
            }
        }

        /* Print out the adjacency matrix of the graph */
        void print()
        {
            unsigned int i;

            for (i = 0; i < n; i++) {
                std::cout << "(" << i << "): " << adjacency_matrix[i] << "\n";
            }
        }

        /* Add the edge uv to G (and the edge vu).
        * Returns 1 if the edge was added, and 0 otherwise.
        */
        int add_edge(const unsigned int u, const unsigned int v)
        {
            if ((u > n) || (v > n) || adjacency_matrix[u][v] == 1) {
                return 0;
            }

            adjacency_matrix[u][v] = 1;
            adjacency_matrix[v][u] = 1;
            return 1;
        }

        /* Remove the edge uv from G (and the edge vu).
        * Returns 1 if the edge was removed, and 0 otherwise
        */
        int delete_edge(const unsigned int u, const unsigned int v)
        {
            if ((u > n) || (v > n) || adjacency_matrix[u][v] == 0) {
                return 0;
            }

            adjacency_matrix[u][v] = 0;
            adjacency_matrix[v][u] = 0;
            return 1;
        }

        /* Checks if uv is an edge. Returns 1 if it is. */
        int is_edge(const unsigned int &u, const unsigned int &v)
        {
            if ((u > n) || (v > n)) {
                return 0;
            }

            return adjacency_matrix[u][v];
        }
};

#endif