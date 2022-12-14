#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double dijkstra(vector<vector<pair<int,double>>> graph, int start, int end)
    {
        vector<double> dist(graph.size(),0);
        priority_queue<pair<int, double>> pq;
        pq.push({ start,1 });
        dist[start] = 1;
        while (pq.size()) {
            double p = pq.top().second;
            int node = pq.top().first;
            pq.pop();
            for (auto x : graph[node])
                if (dist[node] * x.second > dist[x.first])
                {
                    dist[x.first] = dist[node] * x.second;
                    pq.push({ x.first,dist[x.first] });
                }
        }
        return dist[end];
    }

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int endd) {
        vector<vector<pair<int, double>>> graph(n, vector<pair<int,double>>(0));
        for (int i = 0; i < edges.size(); i++)
        {
            pair<int, double> x, y;
            x.first = edges[i][1];
            x.second = succProb[i];
            y.first = edges[i][0];
            y.second = succProb[i];
            graph[edges[i][0]].push_back(x);
            graph[edges[i][1]].push_back(y);
        }
        return dijkstra(graph, start, endd);
    }
};
