#include<bits/stdc++.h>
using namespace std;
struct node
{
    int val, kr;
    void read(int _val, int _kr)
    {
        val = _val; kr = _kr;
    }
};
struct prz
{
    int kand, ilKandPref, wyn, len;
    void read(int _kand, int _ilKandPref, int _wyn, int _len)
    {
        kand = _kand; ilKandPref = _ilKandPref; wyn = _wyn; len = _len;
    }
};
struct event //poczKon --> 0 - pocz, 1 - num, 2 - kon
{
    int val, poczKon, indx, aVal;
    void read(int _val, int _poczKon, int _indx, int _aVal)
    {
        val = _val; poczKon = _poczKon; indx = _indx; aVal = _aVal;
    }
};

int n, q, t[1000005], base = 1, zlicz[1000005];
node tr[1700005];
prz prze[1000005];
vector<event> eve;

node uni(node a, node b) 
{
    node res;
    if(a.val == b.val)
        res.read(a.val, a.kr + b.kr);
    else if(a.kr > b.kr)
        res.read(a.val, a.kr - b.kr);
    else if(a.kr < b.kr)
        res.read(b.val, b.kr - a.kr);
    else
        res.read(0, 0);
    
    return res;
}

int query(int a, int b)
{
    a += base - 1;
    b += base + 1;
    node res; res.kr = 0; res.val = 0;
    while(a / 2 != b / 2)
    {
        if(a % 2 == 0) res = uni(res, tr[a + 1]);
        if(b % 2 == 1) res = uni(res, tr[b - 1]);
        a /= 2;
        b /= 2;
    }
    return res.val;
}

bool cmp(event a, event b)
{
    if(a.val == b.val)
        return a.poczKon < b.poczKon;
    return a.val < b.val;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    while(base < n) base *= 2;
    for(int i = 1; i <= n; i++) 
    {
        cin >> t[i];
        event e; e.read(i, 1, 0, t[i]);
        eve.push_back(e);
        tr[base + i - 1].read(t[i], 1);
    }

    for(int i = base - 1; i > 0; i--)
        tr[i] = uni(tr[i * 2], tr[i * 2 + 1]);

    for(int i = 0; i < q; i++)
    {
        int a, b; cin >> a >> b;
        prze[i + 1].read(query(a - 1, b - 1), 0, 0, b - a + 1);
        event e; e.read(a, 0, i + 1, 0);
        eve.push_back(e);
        e.poczKon = 2;
        e.val = b;
        eve.push_back(e);
    }

    sort(eve.begin(), eve.end(), cmp);

    for(int i = 0; i < eve.size(); i++)
    {
        if(eve[i].poczKon == 0) //poczatek
        {
            int nr = eve[i].indx;
            prze[nr].ilKandPref = zlicz[prze[nr].kand];
        }
        else if(eve[i].poczKon == 2) //koniec
        {
            int nr = eve[i].indx;
            int ilosc = zlicz[prze[nr].kand] - prze[nr].ilKandPref;
            if(ilosc > prze[nr].len / 2)
                prze[nr].wyn = prze[nr].kand;
            else
                prze[nr].wyn = 0;
        }
        else //liczba
            zlicz[eve[i].aVal]++;
    }

    for(int i = 1; i <= q; i++)
        cout << prze[i].wyn << "\n"; 
}