#include <bits/stdc++.h>
using namespace std;

#define TRAV_SET(j, st, dsu) for (int j = dsu.roots[st]; ~j; j = dsu.nxt[j])

typedef long long ll;
typedef vector<int> vint;

const int M = 1000 + 5;
struct DSU
{

    int parent[M], sz[M];
    int roots[M], root_inv[M];
    int tail[M], nxt[M];
    int n, num_comp;

    void init(int s)
    {
        n = s;
        num_comp = s;
        fill(sz, sz + n, 1);
        iota(parent, parent + n, 0);

        iota(roots, roots + n, 0);
        iota(root_inv, root_inv + n, 0);

        fill(nxt, nxt + n, -1);
        iota(tail, tail + n, 0);
    }

    int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }
    bool join(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;

        if (sz[x] > sz[y])
            swap(x, y);

        parent[x] = y;
        sz[y] += sz[x];

        int posX = root_inv[x];
        roots[posX] = roots[--num_comp];
        root_inv[roots[num_comp]] = posX;

        nxt[tail[y]] = x;
        tail[y] = tail[x];
        return true;
    }
};

int convert(char l)
{
    return l - 'A';
}

int main(int argc, char const *argv[])
{
    // freopen("out.txt", "w", stdout);
    int t;
    cin >> t;
    while (t--)
    {
        char l;
        string edge;
        cin >> l;
        // cout << "L: " << l;
        int s = convert(l) + 1;
        DSU dsu;
        dsu.init(s);
        // cout << "here\n";
        cin.ignore(256, '\n');
        while (getline(cin, edge))
        {
            if (edge.empty())
            {
                // cout << "FOUND EMPTY LINE\n";
                break;
            }
            // cout << edge;
            int u = convert(edge[0]), v = convert(edge[1]);
            dsu.join(u, v);
            // cout << dsu.num_comp << "\n";
        }
        // for (int i = 0; i < dsu.num_comp; i++)
        // {
        //     TRAV_ROOT(j, i, dsu)
        //     cout << j << " ";

        //     cout << "\n";
        // }

        cout << dsu.num_comp << (t == 0 ? "\n" : "\n\n");
    }
    return 0;
}