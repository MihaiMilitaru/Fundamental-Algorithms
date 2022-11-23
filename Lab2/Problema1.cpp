#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
ifstream f("retea2.in");
struct punct{
    double x, y;
};
const int NMAX = 2000;
const int MMAX = 2000;

int n, m;
punct poz[NMAX + MMAX + 5];
bool vizitat[NMAX + MMAX + 5];
long long dmin[NMAX + MMAX + 5];

int update(int idx) {
    int d_dmin = -1;
    for(int i = n+1; i <= n + m; i++) {

        if(vizitat[i])
            continue;

        long long d = 1LL * (poz[idx].x - poz[i].x) * (poz[idx].x- poz[i].x) +
                      1LL * (poz[idx].y - poz[i].y) * (poz[idx].y - poz[i].y);

        if(dmin[i] == -1 || d < dmin[i])
            dmin[i] = d;

        if(d_dmin == -1 || dmin[i] < dmin[d_dmin])
            d_dmin = i;
    }

    return d_dmin;
}

int main() {
    freopen("retea2.out", "w", stdout);
    f>>n>>m;
    for(int i=1; i<=n+m; i++) {
        double x, y;
        f >> x >> y;
        poz[i] = {x, y};
        dmin[i] = -1;
    }

    int nod = -1;
    for(int i = 1; i <= n; i++) {
        vizitat[i] = true;
        nod = update(i);
    }

    double dtotal = 0;
    for(int j = 1; j <= m; j++) {
        vizitat[nod] = true;
        dtotal += sqrt(dmin[nod]);
        nod = update(nod);
    }

    printf("%.6lf", dtotal);

    return 0;
}
