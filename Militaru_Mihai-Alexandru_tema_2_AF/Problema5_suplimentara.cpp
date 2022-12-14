#include <fstream>
#include <vector>
#include <iomanip>
#include <queue>
#define inf 100000000

using namespace std;
ifstream fin("ciclu.in");
ofstream fout("ciclu.out");
vector<pair<int, int>> graf[1005];
int n,m;
void citeste()
{
    int u,v,cost;
    fin>>n>>m;
    for(int i=0; i<m; i++)
    {
        fin>>u>>v>>cost;
        graf[u].push_back(make_pair(v,cost));
    }
}
bool bellmanFord(double mij)
{
    vector<double> dist(n+1,0);
    vector<int> noduri(n+1,0);
    queue<int> coada;
    for(int i=1; i<=n; i++)
    {
        // dist.push_back(0);
        //noduri.push_back(0);
        coada.push(i);
    }
    while(!coada.empty()){
        int u = coada.front();
        coada.pop();
        for(auto& v : graf[u]){
            if(dist[u] + v.second - mij < dist[v.first]){
                dist[v.first] = dist[u] + v.second - mij;
                noduri[v.first]++;
                if(noduri[v.first] >= n)
                    return true;
                coada.push(v.first);
            }
        }
    }
    return false;
}
double cautareBinara()
{
    double st=1, dr=inf,mij;
    while(0.01<dr-st)
    {

        mij=(st+dr)/2;
        if(bellmanFord(mij))
            dr=mij;
        else
            st=mij;
    }
    return st;
}
int main()
{
    citeste();
    fout<<fixed<<setprecision(2)<<cautareBinara();
    return 0;
}
