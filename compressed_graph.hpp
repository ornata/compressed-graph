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
        * Does not allow for loops
        */
        int add_edge(const unsigned int u, const unsigned int v)
        {
            if ((u > n) || (v > n) || adjacency_matrix[u][v] == 1 || u == v) {
                return 0;
            }

            adjacency_matrix[u][v] = 1;
            adjacency_matrix[v][u] = 1;
            return 1;
        }

        /* Remove the edge uv from G (and the edge vu).
        * Returns 1 if the edge was removed, and 0 otherwise
        * Does not allow for loops
        */
        int delete_edge(const unsigned int u, const unsigned int v)
        {
            if ((u > n) || (v > n) || adjacency_matrix[u][v] == 0 || u == v) {
                return 0;
            }

            adjacency_matrix[u][v] = 0;
            adjacency_matrix[v][u] = 0;
            return 1;
        }

        /* Checks if uv is an edge. Returns 1 if it is. */
        int is_edge(const unsigned int &u, const unsigned int &v)
        {
            // out of bounds, or a loop
            if ((u > n) || (v > n) || u == v) {
                return 0;
            }

            return adjacency_matrix[u][v];
        }

        /* Returns 1 if v has degree 0, 0 if not, -1 if v out of bounds. */
        int is_isolated(const unsigned int &v)
        {
            if (v > n)  {
                return -1; 
            }

            return !(adjacency_matrix[v].any());
        }

        /* Sets G to its complement. That is, if uv is in G, then uv is not in ~G. If uv not in G,
        * then uv is in ~G. */
        void complement()
        {
            unsigned int i;

            for (i = 0; i < n; i++) {
                adjacency_matrix[i].flip();
                adjacency_matrix[i][i] = 0; // no loops allowed!
            }
        }

        /* Returns the degree of vertex v */
        long degree(const unsigned int &v)
        {
            if (v > n) { // out of bounds, return 0
                return -1;
            }

            return adjacency_matrix[v].count();
        }

        /* Return the number of edges in the graph. */
        unsigned int get_num_edges()
        {
            unsigned int degree_sum = 0;

            for (auto vertex : adjacency_matrix)
            {
                degree_sum += vertex.count();
            }

            if (degree_sum == 0) {
                return 0;
            }

            else {
                return degree_sum >> 1;
            }
        }

        /* Return the number of vertices in G */
        unsigned int get_num_verts()
        {
            return n;
        }
};

#endif