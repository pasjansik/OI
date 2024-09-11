#include<bits/stdc++.h>
using namespace std;
struct edge
{
    int des, in;
    void read(int _des, int _in)
    {
        des = _des;
        in = _in;
    }
};

vector<edge> G[1000005];
vector<pair<int, int>> edges;
char res[1000005];
int n, m, low[1000005], odw[1000005], pre[1000005], par[1000005], bl[1000005], ans, edgePar[1000005];

void czytaj()
{
    cin >> n >> m;
    int x = 0;
    for(int i = 0; i < m; i++)
    {
        int a, b; cin >> a >> b;
        edge e; e.read(a, x);
        G[b].push_back(e);
        e.read(b, x++);
        G[a].push_back(e);
        edges.push_back({a, b});
    }
}

int k = 0;
void calc_low(int w)
{
    odw[w] = 1;
    pre[w] = ++k;
    low[w] = pre[w];
    for(auto v : G[w])
    {
        if(odw[v.des] && edgePar[w] != v.in) 
        {
            low[w] = min(low[w], pre[v.des]);
            continue;
        }
        else if(odw[v.des]) 
            continue;
        par[v.des] = w;
        edgePar[v.des] = v.in;
        calc_low(v.des);
        low[w] = min(low[w], low[v.des]);
    }
}

void del_bridges(int w)
{
    odw[w] = 1;
    for(auto v : G[w])
    {
        if(low[w] == pre[w] && v.des == par[w]) bl[v.in] = 1;
        if(odw[v.des]) continue;
        del_bridges(v.des);
    }
}

void calc_res(int w)
{
    odw[w] = 1;
    for(auto v : G[w])
    {
        if(edges[v.in].first == w) res[v.in] = '>';
        else res[v.in] = '<';
        if(bl[v.in] || odw[v.des]) continue;
        calc_res(v.des);
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    czytaj();
    for(int i = 1; i <= n; i++) 
        pre[i] = n + 1;
    for(int i = 1; i <= n; i++)
        if(!odw[i])
            calc_low(i);

    for(int i = 1; i <= n; i++) odw[i] = 0;

    for(int i = 1; i <= n; i++)
        if(!odw[i])
            del_bridges(i);

    for(int i = 1; i <= n; i++) odw[i] = 0;
    for(int i = 1; i <= n; i++)
    {
        if(!odw[i])
        {
            ans++;
            calc_res(i);
        }
    }

    cout << ans << "\n";
    for(int i = 0; i < m; i++) cout << res[i];
}