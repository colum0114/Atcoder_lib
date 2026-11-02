vll minp(10000001);

void eratos() {
    for (int i = 2; i <= 10000000; i++) {
        if (minp[i] == 0) {
            // iは素数。iの倍数に最小素因数iを記録していく
            for (int j = i; j <= 10000000; j += i) {
                if (minp[j] == 0) {
                    minp[j] = i;
                }
            }
        }
    }
}
