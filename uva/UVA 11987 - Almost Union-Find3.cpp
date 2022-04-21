#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vint;
/*

solution idea:
- extend parents array to double the size needed by the test case.
- assume that size is n, initialize parents from 0 to n with the values n to 2*n
- also initialize parents from n to 2n with the values n to 2*n.
- the second half of parents are the actual parents so we are creating
  artifical parents that don't use the values in the range.
- now, joining two sets works as normal but it is just using the artifical parents instead of the normal ones.
- moving can work fine since the integer being moved will never be a parent(the parents range from n to 2*n).
*/

const int M = 2 * 100000 + 5;

struct DSU
{

    int parent[M], sz[M], sum[M];
    int n;

    void init(int s)
    {
        n = s;
        iota(parent, parent + n, n);
        iota(parent + n, parent + 2 * n, n);
        fill(sz + n, sz + 2 * n, 1);
        iota(sum + n, sum + 2 * n, 0);
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

        sz[y] += sz[x];
        sum[y] += sum[x];
        parent[x] = y;

        return true;
    }

    bool move(int x, int y)
    {
        int par_x = find(x);
        int par_y = find(y);

        if (par_x == par_y)
            return false;

        sz[par_y]++;
        sz[par_x]--;
        sum[par_y] += x;
        sum[par_x] -= x;
        parent[x] = par_y;

        return true;
    }
};

int main(int argc, char const *argv[])
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n, m;
    DSU dsu;
    while (cin >> n >> m)
    {
        dsu.init(n + 1);
        int op, p, q;
        while (m--)
        {
            cin >> op >> p;

            switch (op)
            {
            case 1:
            {

                cin >> q;
                dsu.join(p, q);
                break;
            }
            case 2:
            {

                cin >> q;
                dsu.move(p, q);
                break;
            }
            case 3:
            {
                int parent = dsu.find(p);
                cout << dsu.sz[parent] << " " << dsu.sum[parent] << "\n";
                break;
            }
            default:
                break;
            }
        }
    }

    return 0;
}
