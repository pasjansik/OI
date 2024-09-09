#include<bits/stdc++.h>
using namespace std;
int n, m, odw[1000005], col[1000005], ileZlych, czyDoc[1000005], wyw[1000005];
vector<int> G[1000005], G1[1000005], G2[1000005], G3[1000005];
stack<int> S;
vector<int> ord;

void dfs(int w)
{
    odw[w] = 1;
    for(auto v : G[w])
        if(!odw[v])
            dfs(v);
    S.push(w);
}

void color(int w, int c)
{
    col[w] = c;
    for(auto v : G1[w])
        if(!col[v]) 
            color(v, c);
}

void toposort(int w)
{
    odw[w] = 1;
    for(auto v : G2[w])
        if(!odw[v])
            toposort(v);
    ord.push_back(w);
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G1[b].push_back(a);
    }

    for(int i = 1; i <= n; i++)
        if(!odw[i]) 
            dfs(i);

    int c = 0;
    while(!S.empty())
    {
        int w = S.top(); S.pop();
        if(col[w]) continue;
        color(w, ++c);
    }

    for(int i = 1; i <= n; i++)
    {
        for(auto v : G[i])
        {
            if(col[v] != col[i])
            {
                G2[col[i]].push_back(col[v]);
                G3[col[v]].push_back(col[i]);
            }
        }
    }

    for(int i = 1; i <= n; i++) odw[i] = 0;

    for(int i = 1; i <= c; i++)
        if(!odw[i])
            toposort(i);

    for(int i = 0; i < ord.size(); i++)
    {
        for(auto v : G2[ord[i]])
        {
            if(!czyDoc[v]) 
            {
                ileZlych--;
                czyDoc[v] = 1;
            }
        }

        if(ileZlych > 0) wyw[ord[i]] = 1;
        ileZlych++;
        
    }

    for(int i = 1; i <= c; i++) czyDoc[i] = 0;
    ileZlych = 0; 
    for(int i = ord.size() - 1; i >= 0; i--)
    {
        for(auto v : G3[ord[i]])
        {
            if(!czyDoc[v])
            {
                ileZlych--;
                czyDoc[v] = 1;
            }
        }
        
        if(ileZlych > 0) wyw[ord[i]] = 1;
        ileZlych++;
    }


    int res = 0;
    for(int i = 1; i <= n; i++)
        if(!wyw[col[i]]) res++;
    cout << res << "\n";

    for(int i = 1; i <= n; i++)
        if(!wyw[col[i]]) cout << i << " ";
}