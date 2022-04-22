#include <bits/stdc++.h>
using namespace std;

#define REP(i, st, e) for (int i = st; i < e; i++)
#define REPI(i, st, e) for (int i = e; i >= st; i--)
typedef long long ll;
typedef pair<int, int> pint;
typedef vector<int> vint;

#define adj(u, e, v, w) for (int e = head[u], v, w; ~e && ((v = to[e], w = wt[e]), 1); e = nxt[e])
const int N = 10000 + 5, M = 2 * 100000 + 5;
int head[N], to[M], nxt[M], wt[M], ne, n;
int vid = 0, dis[N], vis[N];
void init()
{
    memset(head, -1, n * sizeof(head[0]));
    ne = 0;
}

void addEdge(int f, int t, int w)
{
    to[ne] = t;
    nxt[ne] = head[f];
    wt[ne] = w;
    head[f] = ne++;
}
void addBiEdge(int f, int t, int w)
{
    addEdge(f, t, w);
    addEdge(t, f, w);
}

ll prim()
{
    vid++;
    memset(dis, 63, n * sizeof(dis[0]));
    dis[0] = 0;

    priority_queue<pair<int, int>> q;
    q.emplace(0, 0);

    ll result = 0;
    while (q.size())
    {
        int d, u;
        tie(d, u) = q.top();
        q.pop();
        d *= -1;
        if (vis[u] == vid)
            continue;
        vis[u] = vid;
        result += d;
        adj(u, e, v, w)
        {
            if (vis[v] == vid)
                continue;
            if (dis[v] > w)
            {
                dis[v] = w;
                q.emplace(-w, v);
            }
        }
    }
    return result;
}

int main(int argc, char const *argv[])
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    int m;
    cin >> n >> m;
    n++;
    init();
    int u, v, w;
    while (m--)
    {
        cin >> u >> v >> w;
        addBiEdge(--u, --v, w);
    }
    cout << prim() << "\n";
    return 0;
}
