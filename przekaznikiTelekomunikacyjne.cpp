#include<bits/stdc++.h>
using namespace std;
#define int long long
struct lNode
{
    int beg, ent;
};
struct maszt
{
    int s, a;
    void read(int _s, int _a)
    {
        s = _s;
        a = _a;
    }
};

int n, q, base = 1, tr[1000005];
lNode lazy[1000005], lazy2[1000005];
maszt m[1000005];

inline void push(int w, int lw, int pw)
{
    int l = w * 2, p = w * 2 + 1;
    if(lazy[w].ent != 0 || lazy[w].beg != 0)
    {
        int dl = pw - lw + 1;
        int wspol = (lazy[w].ent - lazy[w].beg) / (dl - 1);
        
        int wartP = lazy[w].beg;
        lazy[l].beg += wartP;
        int wartK = (dl / 2 - 1) * wspol + lazy[w].beg;
        lazy[l].ent += wartK;
        tr[l] += wartP * (dl / 2) + ((dl / 2) * ((dl / 2) - 1) / 2) * wspol;
        
        wartP = (dl / 2) * wspol + lazy[w].beg;
        lazy[p].beg += wartP;
        wartK = lazy[w].ent;
        lazy[p].ent += wartK;
        tr[p] += wartP * (dl / 2) + ((dl / 2) * ((dl / 2) - 1) / 2) * wspol;

        lazy[w].beg = lazy[w].ent = 0;
    }

    if(lazy2[w].ent == 0 && lazy2[w].beg == 0) return;
    int dl = pw - lw + 1;
    int wspol = (lazy2[w].beg - lazy2[w].ent) / (dl - 1);

    int wartP = lazy2[w].beg;
    lazy2[l].beg += wartP;
    int wartK = lazy2[w].ent + wspol * (dl / 2);
    lazy2[l].ent += wartK;
    tr[l] += wartK * (dl / 2) + ((dl / 2) * ((dl / 2) - 1) / 2) * wspol;
     
    wartK = lazy2[w].ent;
    lazy2[p].ent += wartK;
    wartP = lazy2[w].ent + wspol * (dl / 2 - 1);
    lazy2[p].beg += wartP;
    tr[p] += wartK * (dl / 2) + ((dl / 2) * ((dl / 2) - 1) / 2) * wspol;

    lazy2[w].beg = lazy2[w].ent = 0;
}

inline void merge(int w)
{
    int l = w * 2, p = w * 2 + 1;
    tr[w] = tr[l] + tr[p];
}

void update(int w, int lw, int pw, int lz, int pz, int val, int wspo, int flag)
{
    if(lw >= lz && pw <= pz)
    {
        int dl = pw - lw + 1;
        int last = val + wspo * (dl - 1);
        tr[w] += (val + last) * dl / 2;
        if(flag == 0)
        {
            lazy[w].beg += val;
            lazy[w].ent += last;
        }
        else
        {
            lazy2[w].beg += last;
            lazy2[w].ent += val;
        }
        return;
    }
    if(pw < lz || lw > pz)
        return;

    push(w, lw, pw);
    int mid = (lw + pw) / 2;
    int iloscWLewym = max(0LL, mid - max(lz, lw) + 1);
    int iloscWPrawym = max(0LL, max(0LL, min(pz, pw) - (mid + 1) + 1));

    if(flag == 0)
    {
        update(w * 2, lw, mid, lz, pz, val, wspo, flag);
        update(w * 2 + 1, mid + 1, pw, lz, pz, val + (wspo * iloscWLewym), wspo, flag);
    }
    else
    {
        update(w * 2, lw, mid, lz, pz, val + iloscWPrawym * wspo, wspo, flag);
        update(w * 2 + 1, mid + 1, pw, lz, pz, val, wspo, flag);
    }
    merge(w);
}

int query(int w, int lw, int pw, int lz, int pz)
{
    if(lw >= lz && pw <= pz)
        return tr[w];
    if(pw < lz || lw > pz)
        return 0;
    push(w, lw, pw);
    int mid = (lw + pw) / 2;
    return query(w * 2, lw, mid, lz, pz) + query(w * 2 + 1, mid + 1, pw, lz, pz);
}

int32_t main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    while(base < n) base *= 2;

    for(int i = 0; i < q; i++)
    {
        char in; cin >> in;
        if(in == 'P')
        {
            int x, s, a; cin >> x >> s >> a;

            int lz = x - s / a;
            if(s % a == 0) lz++;
            if(lz < 1)
                lz = 1;
            
            int pz = x + s / a;
            if(s % a == 0) pz--;
            if(pz > n) pz = n;

            update(1, 0, base - 1, lz - 1, x - 1, s - (x - lz) * a, a, 0);
            if(a < s)
                update(1, 0, base - 1, x, pz - 1, s - (pz - x) * a, a, 1);

            m[x].read(s, a);
        }
        else if(in == 'Z')
        {
            int a, b; cin >> a >> b;
            cout << query(1, 0, base - 1, a - 1, b - 1) / (b - a + 1) << "\n";
        }
        else
        {
            int x; cin >> x;
            int s = m[x].s; int a = m[x].a;
            m[x].read(0, 0);

            int lz = x - s / a;
            if(s % a == 0) lz++;
            if(lz < 1) lz = 1;

            int pz = x + s / a;
            if(s % a == 0) pz--;
            if(pz > n) pz = n;

            update(1, 0, base - 1, lz - 1, x - 1, -s, a, 1);
            if(a < s)
                update(1, 0, base - 1, x, pz - 1, -(s - a), a, 0);
        }
    }
}
