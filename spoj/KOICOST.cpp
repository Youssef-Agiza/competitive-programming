#include <bits/stdc++.h>
using namespace std;

/*
SPOJ
problem: KOICOST


solution idea:
    - sort edges in non-increasing order accoring to their weights and start with an empty graph (no edges).
    - create DSU where each vertex is in a separate component. A path between two vertices will be represented
      by joining their components. That is, if find(x)==find(y), then there is a path between x and y.
    - Now, loop on edges starting with the maximum weight. let the current edge be e,
      and let it be incident with two nodes, u and v. Since this edge connects the two components that
      contain u and v, this edge is the last deleted edge in the cost(u,v). That is, to get cost(u,v),
      we deleted all the edges of weight less than or equal the weight of e.
      Thus, cost(u,v)= prefix_sum of all the weights less than or equal to e.
    - Further more, this edge is the connecting edge for all the vertices in the component of u with all
      the vertices in the component of v. Which mean that
            for any x in component(u) y in component(v)-->cost(x,y)=cost(u,v)=prefix_sum[current_edge].
      Thus,the total cost from the new edge is sz[component(u)]*sz[component(v)]*prefix_sum[current_edge].


    ---- So the algorithm is----
    ans=0
    sort(edges)
    loop on all edges in decreasing order.
    for (i=edges.size()-1; i>=0;i--) do
        e = edges[i]
        if (find(e.u)!=find(e.v))
            ans+= sz[find(e.u)]*sz[find(e.v)]*prefix[i]

*/

typedef long long ll;
typedef pair<int, int> pint;
typedef vector<int> vint;

#define REP(i, st, e) for (ll i = st; i < e; i++)
#define REPI(i, st, e) for (ll i = e; i >= st; i--)

const int N = 100000 + 5, M = 2 * 100000 + 5;
int n, m, ne = 0;

struct DSU
{

    ll parent[N], sz[N], n, num_of_comp;

    void init(ll s)
    {
        num_of_comp = (n = s);

        iota(parent, parent + n, 0);
        fill(sz, sz + n, 1);
    }

    ll find(ll x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }

    bool join(ll a, ll b)
    {
        a = find(a);
        b = find(b);

        if (b == a)
            return false;

        if (sz[a] > sz[b]) // a is smaller
            swap(a, b);

        parent[a] = b;
        sz[b] += sz[a];

        return true;
    }
};

struct Edge
{
    ll u;
    ll v;
    ll w;
};

Edge edges[M];
void addEdge(ll u, ll v, ll w)
{
    edges[ne].u = u;
    edges[ne].v = v;
    edges[ne++].w = w;
}

bool comparator(Edge &e1, Edge &e2)
{
    return e1.w < e2.w;
}

ll prefix_sum[M];
int main(int argc, char const *argv[])
{
    std::ios::sync_with_stdio(false);

    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    ll u, v, w, ans = 0;
    DSU dsu;
    Edge edge;

    cin >> n >> m;
    dsu.init(n + 1);

    REP(i, 0, m)
    {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    sort(edges, edges + m, comparator);

    prefix_sum[0] = (m > 0) ? edges[0].w : 0;
    REP(i, 1, m)
    prefix_sum[i] = prefix_sum[i - 1] + edges[i].w;

    ll u_root, v_root;
    REPI(i, 0, m - 1)
    {
        edge = edges[i];
        u_root = dsu.find(edge.u), v_root = dsu.find(edge.v);
        if (u_root == v_root)
            continue;

        ans += (ll)prefix_sum[i] * (ll)dsu.sz[u_root] * (ll)dsu.sz[v_root];
        dsu.join(edge.u, edge.v);
    }
    cout << ans % ll(1e9) << '\n';
    return 0;
}