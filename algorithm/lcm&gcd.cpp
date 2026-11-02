// ユークリッドの互除法による高速な最大公約数(GCD)計算
ll mygcd(ll a, ll b) {
    if (b == 0) return a;
    return mygcd(b, a % b);
}

ll mylcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return (a / mygcd(a, b)) * b;
}