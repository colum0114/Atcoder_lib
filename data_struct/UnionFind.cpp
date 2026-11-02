// Union-Find (Disjoint Set Union)
class UnionFind {
private:
    vector<int> parent, siz;
public:
    void init(int n) {
        parent.assign(n + 1, -1);
        siz.assign(n + 1, 1);
    }
    int root(int x) {
        if (parent[x] == -1) return x;
        return parent[x] = root(parent[x]);
    }

    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y);
        parent[y] = x;
        siz[x] += siz[y];
        return true;
    }

    int size(int x) {
        return siz[root(x)];
    }
};