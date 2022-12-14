#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

ifstream f("catun.in");
ofstream g("catun.out");

int result[36001];
int minim[36001];
vector<pair<int, int>> graf[36001];
priority_queue<pair<int, int>> q;
int n, m, k;

void dijkstra() {
    while (!q.empty()) {
        int nod = q.top().second;
        q.pop();
        for (auto& v : graf[nod]) {
            if (minim[nod] + v.second < minim[v.first]) {
                minim[v.first] = minim[nod] + v.second;
                q.push(make_pair(-minim[v.first], v.first ));
                result[v.first] = result[nod];
            }
            else if (minim[nod] + v.second == minim[v.first]) {
                result[v.first] = min(result[v.first], result[nod]);
            }
        }
    }
}

int main() {

    f >> n >> m >> k;

    for (int i = 1; i <= n; i++)
        minim[i] = INT_MAX;

    for (int i = 1; i <= k; i++) {
        int x; f >> x;
        result[x] = x;
        q.push({ 0, x });
        minim[x] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        f >> x >> y >> z;
        graf[x].push_back(make_pair(y, z));
        graf[y].push_back(make_pair(x, z));
    }
    dijkstra();
    for (int i = 1; i <= n; i++)
        if (result[i] == i)
            g << 0 << " ";
        else
            g << result[i] << " ";
    return 0;
}
