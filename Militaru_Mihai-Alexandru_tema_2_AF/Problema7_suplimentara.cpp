#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
            vector<pair<int,int>> adj[n];
            for(int i = 0; i < flights.size(); i++){
                int u = flights[i][0];
                int v = flights[i][1];
                int w = flights[i][2];
                adj[u].push_back({v,w});
            }

            vector<int> dist(n+1,INT_MAX);
            dist[src] = 0;

            priority_queue< pair<int,pair<int, int>>, vector<pair<int,pair<int, int>>>,greater<pair<int,pair<int,int>>> > pq;

            pq.push({0,{src,k+1}});

            while(!pq.empty())
            {
                int cost = pq.top().first;
                int node = pq.top().second.first;
                int remStops = pq.top().second.second;
                pq.pop();

                if(node == dst){
                    return dist[dst];
                }
                if(remStops == 0){
                    continue;
                }

                for(auto it: adj[node])
                {
                    int next = it.first;
                    int nextDis =it.second;

                    if((cost + nextDis) < dist[next]){
                        dist[next] = cost + nextDis;
                    }
                    pq.push({cost + nextDis,{next,remStops-1}});

                }
            }

            if(dist[dst] == INT_MAX) return -1;
            return dist[dst];
        }
};
