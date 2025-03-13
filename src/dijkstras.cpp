#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;

    vector<int> dist(n,INF);
    previous.assign(n, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    pq.push({0, source});
    dist[source] = 0;

    while(!pq.empty())
    {
        int curr_dist = pq.top().first;
        int curr_vertex = pq.top().second;

        pq.pop();

        if (curr_dist > dist[curr_vertex]) continue;

        for (const Edge& edge : G[curr_vertex])
        {
            int neighbor = edge.dst;
            int new_dist = curr_dist + edge.weight;

            if (new_dist < dist[neighbor])
            {
                dist[neighbor] = new_dist;
                previous[neighbor] = curr_vertex;
                pq.push({new_dist, neighbor});
            }
        }
    }
    return dist;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v])
    {
        path.insert(path.begin(), v);
    }

    return path;
}

void print_path(const vector<int>& v, int total)
{
    if (v.empty())
    {
        cout << "no path found";
        return;
    }

    for (size_t i =0; i < v.size(); ++i)
    {
        cout << v[i] << ' ';
    }
    cout << '\n';

    cout << "Total cost is " << total << endl;
}