mt19937 rng(random_device{}());
i64 rand(i64 l = -lim, i64 r = lim) {
    return uniform_int_distribution<i64>(l, r)(rng); }
double randr(double l, double r) {
    return uniform_real_distribution<double>(l, r)(rng);
}
