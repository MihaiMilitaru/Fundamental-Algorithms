#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("online.in");
ofstream fout("online.out");

struct edge {
    int x, y, cost;

    bool operator<(const edge& other) const {
        return cost < other.cost;
    }
};

vector <edge> v;
vector <int> t, h;
int n, m, sum, k;


void init() {
    h = vector <int> (n + 1);
    t = vector <int> (n + 1);
    for(int i = 1; i <= n; ++i)
        t[i] = i;
}

int getRoot(int node) {
    if(node == t[node])
        return node;
    return (t[node] = getRoot(t[node]));
}

bool sameConnectedComponents(int x, int y) {
    return getRoot(x) == getRoot(y);
}

void unite(int x, int y) {
    int rootX = getRoot(x);
    int rootY = getRoot(y);
    if(rootX == rootY)
        return;
    if(h[rootX] < h[rootY])
        t[rootX] = rootY;
    else {
        if(h[rootX] == h[rootY])
            ++h[rootX];
        t[rootY] = rootX;
    }
}

void kruskal() {
    int x, y, c;
    sum = 0;
    vector <edge> apm;
    init();
    for(const auto& p : v) {
        x = p.x;
        y = p.y;
        c = p.cost;
        if(sameConnectedComponents(x, y))
            continue;
        unite(x, y);
        sum += c;
        apm.push_back({x, y, c});
    }
    v = apm;
    apm.clear();
    h.clear();
    t.clear();
    fout << sum << '\n';
}

void read() {
    fin >> n >> m;
    init();
    int x, y, c;
    for(int i = 1; i <= m; ++i) {
        fin >> x >> y >> c;
        v.push_back({x, y, c});
    }
}

void solve() {
    sort(v.begin(), v.end());
    kruskal();
    fin >> k;
    int x, y, c;
    for(int i = 1; i <= k; i ++) {
        fin >> x >> y >> c;
        v.push_back({x, y, c});
        sort(v.begin(), v.end());
        kruskal();
    }
}

int main()
{
    read();
    solve();
}