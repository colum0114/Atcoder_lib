// モノイドの定義 (区間最大値・区間最小値など)
struct MaxMonoid {
    using T = ll;
    static T op(T x, T y) { return max(x, y); }
    static T id() { return -2e18; }
};
struct MinMonoid {
    using T = ll;
    static T op(T x, T y) { return min(x, y); }
    static T id() { return 2e18; }
};
struct SumMonoid {
   using T = ll;
   static T op(T x, T y) { return x + y; }
   static T id() { return 0; }
};

// 0-indexed, 半開区間 [l, r) の区間加算・区間更新・区間演算対応 遅延セグメント木 (再帰版)
template<typename Monoid>
class lazysegtree {
    using T = typename Monoid::T;
    int n;
    vector<T> tree, lazy_update, lazy_add;
    const T LAZY_INIT = 4e18; // 更新がないことを表す値

    // ノード k に更新（代入）を適用
    void apply_update(int k, T x, int l, int r) {
        tree[k] = x;
        lazy_update[k] = x;
        lazy_add[k] = 0; // 代入されたら、それまでの加算分はリセット
    }

    // ノード k に加算を適用
    void apply_add(int k, T x, int l, int r) {
        tree[k] += x;
        if (lazy_update[k] != LAZY_INIT) {
            lazy_update[k] += x; // すでに代入予約があれば、そこに加算を反映
        } else {
            lazy_add[k] += x;
        }
    }

    // 遅延データの伝播（push）
    void eval(int k, int l, int r) {
        if (r - l <= 1) return;
        int mid = (l + r) / 2;
        int lc = k * 2 + 1, rc = k * 2 + 2;

        if (lazy_update[k] != LAZY_INIT) {
            apply_update(lc, lazy_update[k], l, mid);
            apply_update(rc, lazy_update[k], mid, r);
            lazy_update[k] = LAZY_INIT;
        }
        if (lazy_add[k] != 0) {
            apply_add(lc, lazy_add[k], l, mid);
            apply_add(rc, lazy_add[k], mid, r);
            lazy_add[k] = 0;
        }
    }

    void update_sub(int a, int b, T x, int k, int l, int r) {
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            apply_update(k, x, l, r);
            return;
        }
        eval(k, l, r);
        update_sub(a, b, x, k * 2 + 1, l, (l + r) / 2);
        update_sub(a, b, x, k * 2 + 2, (l + r) / 2, r);
        tree[k] = Monoid::op(tree[k * 2 + 1], tree[k * 2 + 2]);
    }

    void add_sub(int a, int b, T x, int k, int l, int r) {
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            apply_add(k, x, l, r);
            return;
        }
        eval(k, l, r);
        add_sub(a, b, x, k * 2 + 1, l, (l + r) / 2);
        add_sub(a, b, x, k * 2 + 2, (l + r) / 2, r);
        tree[k] = Monoid::op(tree[k * 2 + 1], tree[k * 2 + 2]);
    }

    T query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return Monoid::id();
        if (a <= l && r <= b) return tree[k];
        eval(k, l, r);
        T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
        return Monoid::op(vl, vr);
    }

public:
    void init(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        tree.assign(2 * n - 1, 0);
        lazy_update.assign(2 * n - 1, LAZY_INIT);
        lazy_add.assign(2 * n - 1, 0);
    }

    // 区間 [l, r) の値を x に更新（代入）
    void update(int l, int r, T x) {
        update_sub(l, r, x, 0, 0, n);
    }

    // 区間 [l, r) に x を加算
    void add(int l, int r, T x) {
        add_sub(l, r, x, 0, 0, n);
    }

    // 区間 [l, r) の演算結果を取得
    T query(int l, int r) {
        return query_sub(l, r, 0, 0, n);
    }
};
