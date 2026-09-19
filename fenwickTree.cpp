long long sumfen(long long fen[], int i) {
    long long ans = 0;
    while (i >= 0) {
        ans += fen[i];
        i = (i & (i + 1)) - 1;
    }
    return ans;
}

void updfen(long long fen[], int i, long long v, int n) {
    while (i < n) {
        fen[i] += v;
        i = (i | (i + 1));
    }
}
