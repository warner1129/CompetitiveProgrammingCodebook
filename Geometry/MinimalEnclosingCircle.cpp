typedef pair<double, double> pdd;
pdd operator+(const pdd &a, const pdd &b) { return pdd(a.ff + b.ff, a.ss + b.ss); }
pdd operator-(const pdd &a, const pdd &b) { return pdd(a.ff - b.ff, a.ss - b.ss); }
pdd operator/(const pdd &a, double c) { return pdd(a.ff / c, a.ss / c); }
pdd operator*(const pdd &a, double c) { return pdd(a.ff * c, a.ss * c); }
double operator*(const pdd &a, const pdd &b) { return a.ff * b.ff + a.ss * b.ss; }
double abs(const pdd &x) { return sqrt(x.ff * x.ff + x.ss * x.ss); } 
using circle = pair<pdd, double>;
struct Mes {
	Mes() {}		
	bool inside(const circle &c, pdd p) {
		return abs(p - c.ff) <= c.ss;
	};
	circle get_cir(pdd a, pdd b) {
		return circle((a + b) / 2., abs(a - b) / 2.);
	}
	circle get_cir(pdd a, pdd b, pdd c) {
		pdd p = (b - a) / 2.;
		p = pdd(-p.ss, p.ff);
		double t = ((c - a) * (c - b)) / (2 * (p * (c - a)));
		p = ((a + b) / 2.) + (p * t);
		return circle(p, abs(p - a));
	}
	circle get_mes(vector<pdd> P) {
		if (P.empty()) return circle{pdd(0, 0), 0};
		mt19937 rng(random_device{}());
		shuffle(all(P), rng);
		circle C{P[0], 0};
		for (int i = 1; i < P.size(); i++) {
			if (inside(C, P[i])) continue;
			C = get_cir(P[i], P[0]);
			for (int j = 1; j < i; j++) {
				if (inside(C, P[j])) continue;
				C = get_cir(P[i], P[j]);
				for (int k = 0; k < j; k++) {
					if (inside(C, P[k])) continue;
					C = get_cir(P[i], P[j], P[k]);
				}
			}
		}
		return C;
	}
} mes;

