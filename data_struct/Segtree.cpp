// モノイドの定義 (MaxMonoid, MinMonoid, SumMonoid)
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

// 汎用的なセグメント木クラス
template<typename Monoid>
class segtree {
    using T = typename Monoid::T;
    ll size;
    vector<T> data;

public:
    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        data.assign(2 * size, Monoid::id());
    }

    void update(ll pos, T x) {
        pos += size - 1;
        data[pos] = x;
        while (pos >= 2) {
            pos /= 2;
            data[pos] = Monoid::op(data[pos * 2], data[pos * 2 + 1]);
        }
    }

    T query(ll l, ll r) {
        T vl = Monoid::id(), vr = Monoid::id();
        l += size - 1;
        r += size - 1;
        while (l < r) {
            if (l & 1) vl = Monoid::op(vl, data[l++]);
            if (r & 1) vr = Monoid::op(data[--r], vr);
            l >>= 1;
            r >>= 1;
        }
        return Monoid::op(vl, vr);
    }
};
