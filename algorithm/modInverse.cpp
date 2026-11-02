// 巨大な累乗 A^B % P を O(log B) で高速に求める関数
ll mypow(ll a, ll b, ll p) {
    if (p == 1) return 0;
    ll ans = 1;
    a %= p;
    while (b > 0) {
        if (b % 2 == 1) ans = (ans * a) % p;
        a = (a * a) % p;
        b /= 2;
    }
    return ans;
}

const int MAX = 300005;
ll fact[MAX], invFact[MAX];

ll modInverse(ll n) {
    return mypow(n, mod - 2, mod);
}

void init() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[MAX - 1] = modInverse(fact[MAX - 1]);
    for (int i = MAX - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % mod * invFact[n - r] % mod;
}
