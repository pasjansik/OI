#include<bits/stdc++.h>
using namespace std;
int n, m, post[55000], odw[55000], k, kol[55000], wiel[55000], res[55000];
vector<int> G[55000], G1[55000], G2[55000], ord;
vector<pair<int, int>> v;
stack<int> S;

void dfs(int w)
{
    odw[w] = 1;
    for(auto v : G[w])
    {
        if(odw[v]) continue;
        dfs(v);
    }

    post[w] = ++k;
    v.push_back({k, w});
}

void col(int w, int c)
{
    kol[w] = c;
    wiel[c]++;

    for(auto v : G1[w])
        if(kol[v] == 0) 
            col(v, c);
}

void resetOdw()
{
    for(int i = 1; i <= n; i++) 
        odw[i] = 0;
}

void makeGraph(int w)
{
    odw[w] = 1;
    for(auto v : G[w])
    {
        if(kol[v] != kol[w]) G2[kol[w]].push_back(kol[v]);
        if(odw[v]) continue;
        makeGraph(v);
    }
}

void topoSort(int w)
{
    odw[w] = 1;
    for(auto v : G2[w])
    {
        if(odw[v]) continue;
        topoSort(v);
    }

    S.push(w);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G1[b].push_back(a);
    }

    //kosaraju
    for(int i = 1; i <= n; i++)
        if(!odw[i]) dfs(i);

    sort(v.begin(), v.end());
    k = 1;
    for(int i = v.size() - 1; i >= 0; i--)
        if(kol[v[i].second] == 0) 
            col(v[i].second, k++);

    resetOdw();
    for(int i = 1; i <= n; i++)
        if(!odw[i]) 
            makeGraph(i);

    resetOdw();
    for(int i = 1; i < k; i++)
        if(!odw[i])
            topoSort(i);
    
    while(!S.empty())
    {
        ord.push_back(S.top());
        S.pop();
    }

    for(int i = ord.size() - 1; i >= 0; i--)
    {
        res[ord[i]] = wiel[ord[i]];
        for(auto v : G2[ord[i]]) res[ord[i]] += res[v];
    }

    for(int i = 1; i <= n; i++)
        cout << res[kol[i]] - 1 << "\n";
}

/*
15 19
1 2
3 1
2 4
4 3
4 5
5 6
6 7
7 8
8 6
8 9
9 10
9 12
10 11
11 9
12 11
12 13
13 15
15 14
14 13
*/