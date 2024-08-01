// ∠AOB * r^2 / 2
double SectorArea(Pt a, Pt b, double r) {
    double theta = atan2(a.ss, a.ff) - atan2(b.ss, b.ff);
    while (theta <= 0) theta += 2 * pi;
    while (theta >= 2 * pi) theta -= 2 * pi;
    theta = min(theta, 2 * pi - theta);
    return r * r * theta / 2;
}