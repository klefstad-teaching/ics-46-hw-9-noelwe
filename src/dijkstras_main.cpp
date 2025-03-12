#include "dijkstras.h"

int main()
{
    Graph G;
    file_to_graph("small.txt",G);

    int source = 0;
    vector<int> previous;

    vector<int> dist = dijkstra_shortest_path(G, source, previous);

    for(int i = 0; i < G.numVertices; ++i)
    {
        vector<int> path = extract_shortest_path(dist, previous, i);

        print_path(path, dist[i]);
    }
    return 0;
}