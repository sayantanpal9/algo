vector<ll> sieve(1e6+1, 1);
for (ll i = 2; i <= 1e3; i++) {
  if (sieve[i]) {
    for (ll j = i * i; j <= 1e6; j += i) {
      sieve[j] = 0;
    }
  }
}
