#include <bits/stdc++.h>
 
using namespace std;
 
/*
    VERIFICAR:
    - Corner cases
    - Estouro de variavel
    - Acesso indevido de memoria
    
    MODULO NEGATIVO
    int modulo(int x,int N){
        return (x % N + N) %N;
    }
 
*/
 
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define f first
#define s second
#define pb push_back
 
typedef long long ll;
typedef pair<int, int> ii;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
 
typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;
 
#define sq(x) ((x)*(x))
 
bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}
 
struct pt { // ponto
	ld x, y;
	pt() {}
	pt(ld x_, ld y_) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		if (!eq(y, p.y)) return y < p.y;
		return 0;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y);
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ld c) const { return pt(x*c  , y*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  ); }
	ld operator * (const pt p) const { return x*p.x + y*p.y; }
	ld operator ^ (const pt p) const { return x*p.y - y*p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};
 
struct line { // reta
	pt p, q;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
	friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};
 
// PONTO & VETOR
 
ld dist(pt p, pt q) { // distancia
	return hypot(p.y - q.y, p.x - q.x);
}
 
ld dist2(pt p, pt q) { // quadrado da distancia
	return sq(p.x - q.x) + sq(p.y - q.y);
}
 
ld norm(pt v) { // norma do vetor
	return dist(pt(0, 0), v);
}
 
ld angle(pt v) { // angulo do vetor com o eixo x
	ld ang = atan2(v.y, v.x);
	if (ang < 0) ang += 2*pi;
	return ang;
}
 
ld sarea(pt p, pt q, pt r) { // area com sinal
	return ((q-p)^(r-q))/2;
}
 
bool col(pt p, pt q, pt r) { // se p, q e r sao colin.
	return eq(sarea(p, q, r), 0);
}
 
int paral(pt u, pt v) { // se u e v sao paralelos
	if (!eq(u^v, 0)) return 0;
	if ((u.x > eps) == (v.x > eps) and (u.y > eps) == (v.y > eps))
		return 1;
	return -1;
}
 
bool cw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea(p, q, r) < eps;
}
 
bool ccw(pt p, pt q, pt r) { // se p, q, r sao ccw
	return sarea(p, q, r) > eps;
}
 
pt rotate(pt p, ld th) { // rotaciona o ponto th radianos
	return pt(p.x * cos(th) - p.y * sin(th),
			p.x * sin(th) + p.y * cos(th));
}
 
pt rotate90(pt p) { // rotaciona 90 graus
	return pt(-p.y, p.x);
}
 
// RETA
 
bool isvert(line r) { // se r eh vertical
	return eq(r.p.x, r.q.x);
}
 
ld getm(line r) { // coef. ang. de r
	if (isvert(r)) return DINF;
	return (r.p.y - r.q.y) / (r.p.x - r.q.x);
}
 
ld getn(line r) { // coef. lin. de r
	if (isvert(r)) return DINF;
	return r.p.y - getm(r) * r.p.x;
}
 
bool paraline(line r, line s) { // se r e s sao paralelas
	return paral(r.p - r.q, s.p - s.q);
}
 
bool isinseg(pt p, line r) { // se p pertence ao seg de r
	if (p == r.p or p == r.q) return 1;
	return paral(p - r.p, p - r.q) == -1;
}
 
ld get_t(pt v, line r) { // retorna t tal que t*v pertence a reta r
    return (r.p^r.q) / ((r.p-r.q)^v);
}
 
pt proj(pt p, line r) { // projecao do ponto p na reta r
	if (r.p == r.q) return r.p;
	r.q = r.q - r.p; p = p - r.p;
	pt proj = r.q * ((p*r.q) / (r.q*r.q));
	return proj + r.p;
}
 
pt inter(line r, line s) { // r inter s
	if (paraline(r, s)) return pt(DINF, DINF);
 
	if (isvert(r)) return pt(r.p.x, getm(s) * r.p.x + getn(s));
	if (isvert(s)) return pt(s.p.x, getm(r) * s.p.x + getn(r));
 
	ld x = (getn(s) - getn(r)) / (getm(r) - getm(s));
	return pt(x, getm(r) * x + getn(r));
}
 
bool interseg(line r, line s) { // se o seg de r intersecta o seg de s
	if (isinseg(r.p, s) or isinseg(r.q, s)
		or isinseg(s.p, r) or isinseg(s.q, r)) return 1;
 
	return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and
			ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}
 
ld disttoline(pt p, line r) { // distancia do ponto a reta
	return dist(p, proj(p, r));
}
 
ld disttoseg(pt p, line r) { // distancia do ponto ao seg
	if (isinseg(proj(p, r), r))
		return disttoline(p, r);
	return min(dist(p, r.p), dist(p, r.q));
}
 
ld distseg(line a, line b) { // distancia entre seg
	if (interseg(a, b)) return 0;
 
	ld ret = DINF;
	ret = min(ret, disttoseg(a.p, b));
	ret = min(ret, disttoseg(a.q, b));
	ret = min(ret, disttoseg(b.p, a));
	ret = min(ret, disttoseg(b.q, a));
 
	return ret;
}
 
// POLIGONO
 
ld polarea(vector<pt> v) { // area do poligono
	ld ret = 0;
	for (int i = 0; i < v.size(); i++)
		ret += sarea(pt(0, 0), v[i], v[(i + 1) % v.size()]);
	return abs(ret);
}
 
bool inpol(pt p, vector<pt> v) { // se um ponto pertence ao poligono
	//if (onpol(p, v)) return 1;
	int c = 0;
	line r = line(p, pt(DINF, pi * DINF));
	for (int i = 0; i < v.size(); i++) {
		line s = line(v[i], v[(i + 1) % v.size()]);
		if (interseg(r, s)) c++;
	}
	return c % 2;
}
 
bool interpol(vector<pt> v1, vector<pt> v2) { // se dois poligonos se intersectam
	for (int i = 0; i < v1.size(); i++) if (inpol(v1[i], v2)) return 1;
	for (int i = 0; i < v2.size(); i++) if (inpol(v2[i], v1)) return 1;
	return 0;
}
 
ld distpol(vector<pt> v1, vector<pt> v2) { // distancia entre poligonos
	if (interpol(v1, v2)) return 0;
 
	ld ret = DINF;
 
	for (int i = 0; i < v1.size(); i++) for (int j = 0; j < v2.size(); j++)
		ret = min(ret, distseg(line(v1[i], v1[(i + 1) % v1.size()]),
					line(v2[j], v2[(j + 1) % v2.size()])));
	return ret;
}
 
//LEMBRAR QUE PONTOS COLINEARES SÃO REMOVIDOS AO REPRESENTAR O HULL
//NAO FUNCIONOU, OLHAR GEOMETRIA INT
vector<pt> convex_hull(vector<pt> v) { // convex hull - O(n log(n))
	vector<pt> l, u;
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		while (l.size() > 1 and !ccw(l[l.size()-2], l.back(), v[i]))
			l.pop_back();
		l.pb(v[i]);
	}
	for (int i = v.size() - 1; i >= 0; i--) {
		while (u.size() > 1 and !ccw(u[u.size()-2], u.back(), v[i]))
			u.pop_back();
		u.pb(v[i]);
	}
	l.pop_back(); u.pop_back();
	for (pt i : u) l.pb(i);
	return l;
}
 
pt getCentroid(vector<pt> pol) {//Calcula centroide
    ld accumulatedArea = 0.0;
    ld centerX = 0.0;
    ld centerY = 0.0;
    for (int i = 0, j = pol.size() - 1; i < pol.size(); j = i++) {
       ld temp = pol[i].x * pol[j].y - pol[j].x * pol[i].y;
       accumulatedArea += temp;
       centerX += (pol[i].x + pol[j].x) * temp;
       centerY += (pol[i].y + pol[j].y) * temp;
    }
 
    if(eq(accumulatedArea, 0)) {
        return pt();
    }
    accumulatedArea *= 3.0;
    return pt(centerX / accumulatedArea, centerY / accumulatedArea);
  }
 
struct convex_pol {
	vector<pt> pol;
 
	convex_pol(vector<pt> v) : pol(convex_hull(v)) {}
	bool is_inside(pt p) { // se o ponto ta dentro do hull - O(log(n))
		if (pol.size() == 1) return p == pol[0];
		int l = 1, r = pol.size();
		while (l < r) {
			int m = (l+r)/2;
			if (ccw(p, pol[0], pol[m])) l = m+1;
			else r = m;
		}
		if (l == 1) return isinseg(p, line(pol[0], pol[1]));
		if (l == pol.size()) return false;
		return !ccw(p, pol[l], pol[l-1]);
	}
};
 
bool operator < (const line& a, const line& b) { // comparador pro sweepline
	if (a.p == b.p) return ccw(a.p, a.q, b.q);
	if (!eq(a.p.x, a.q.x) and (eq(b.p.x, b.q.x) or a.p.x+eps < b.p.x))
		return ccw(a.p, a.q, b.p);
	return ccw(a.p, b.q, b.p);
}
 
bool simple(vector<pt> v) { // se um poligono eh simples - O(n log(n))
	auto intersects = [&](pair<line, int> a, pair<line, int> b) {
		if ((a.s+1)%v.size() == b.s or (b.s+1)%v.size() == a.s) return false;
		return interseg(a.f, b.f);
	};
	vector<line> seg;
	vector<pair<pt, pair<int, int>>> w;
	for (int i = 0; i < v.size(); i++) {
		pt at = v[i], nxt = v[(i+1)%v.size()];
		// pontos do segmento devem estar ordenados
		if (nxt < at) swap(at, nxt);
		seg.push_back(line(at, nxt));
		w.push_back({at, {0, i}});
		w.push_back({nxt, {1, i}});
		// casos degenerados estranhos
		if (isinseg(v[(i+2)%v.size()], line(at, nxt))) return 0;
		if (isinseg(v[(i+v.size()-1)%v.size()], line(at, nxt))) return 0;
 
	}
	sort(w.begin(), w.end());
	set<pair<line, int>> se;
	for (auto i : w) {
		line at = seg[i.s.s];
		if (i.s.f == 0) {
			auto nxt = se.lower_bound({at, i.s.s});
			if (nxt != se.end() and intersects(*nxt, {at, i.s.s})) return 0;
			if (nxt != se.begin() and intersects(*(--nxt), {at, i.s.s})) return 0;
			se.insert({at, i.s.s});
		} else {
			auto nxt = se.upper_bound({at, i.s.s}), cur = nxt, prev = --cur;
			if (nxt != se.end() and prev != se.begin()
				and intersects(*nxt, *(--prev))) return 0;
			se.erase(cur);
		}
	}
	return 1;
}
 
// CIRCUNFERENCIA
 
pt getcenter(pt a, pt b, pt c) { // centro da circunf dado 3 pontos
	b = (a + b) / 2;
	c = (a + c) / 2;
	return inter(line(b, b + rotate90(a - b)),
			line(c, c + rotate90(a - c)));
}
 
vector<pt> circ_line_inter(pt a, pt b, pt c, ld r) { // intersecao da circunf (c, r) e reta ab
	vector<pt> ret;
	b = b-a, a = a-c;
	ld A = b*b;
	ld B = a*b;
	ld C = a*a - r*r;
	ld D = B*B - A*C;
	if (D < -eps) return ret;
	ret.push_back(c+a+b*(-B+sqrt(D+eps))/A);
	if (D > eps) ret.push_back(c+a+b*(-B-sqrt(D))/A);
	return ret;
}
 
vector<pt> circ_inter(pt a, pt b, ld r, ld R) { // intersecao da circunf (a, r) e (b, R)
	vector<pt> ret;
	ld d = dist(a, b);
	if (d > r+R or d+min(r, R) < max(r, R)) return ret;
	ld x = (d*d-R*R+r*r)/(2*d);
	ld y = sqrt(r*r-x*x);
	pt v = (b-a)/d;
	ret.push_back(a+v*x + rotate90(v)*y);
	if (y > 0) ret.push_back(a+v*x - rotate90(v)*y);
	return ret;
}
 
pair<pt, pt> getTangentes(pt p, pt c, ld r) {
    ld angulo = asin(r/dist(p, c));
    ld angulo2 = angle(p-c);
    if(angulo2 > pi) {
        angulo2-=pi;
    }
    angulo += angulo2;
    ld coef = tan(angulo);
    ld y = coef*(c.x-p.x)+p.y;
    line l(p, pt(c.x, y));
    vector<pt> inters1 = circ_line_inter(l.p, l.q, c, r);
    coef = tan(-angulo);
    y = coef*(c.x-p.x)+p.y;
    l = line(p, pt(c.x, y));
    vector<pt> inters2 = circ_line_inter(l.p, l.q, c, r);
    return {inters1[0], inters2[0]};
}
 
int main() { _
    pt c, d;
    cin >> c >> d;
    pair<pt, ld> b, r;
    cin >> b.f >> b.s;
    cin >> r.f >> r.s;
    vector<pt> intersecaoLinhaB = circ_line_inter(c, d, r.f, r.s);
    cout << fixed << setprecision(10);
    if(intersecaoLinhaB.size() == 2) {
        //Arco
        pair<pt, pt> r1 = getTangentes(c, r.f, r.s);
        pair<pt, pt> r2 = getTangentes(d, r.f, r.s);
        vector<pt> v1(2);
        vector<pt> v2(2);
        v1[0] = r1.f;
        v1[1] = r1.s;
        v2[0] = r2.f;
        v2[1] = r2.s;
        ld resp = DINF;
        for(int I=0; I<2; I++) {
            for(int J=0; J<2; J++) {
                ld ang1 = angle(v1[I]-r.f);
                ld ang2 = angle(v2[J]-r.f);
                if(ang1 > ang2) {
                    swap(ang1, ang2);
                }
                ld ang = ang2-ang1;
                if(ang > pi) {
                    ang-=pi;
                }
                ld distArc = ang*r.s;
                ld dis = dist(c, v1[I]) + distArc + dist(v2[J], d);
                if(resp == DINF) {
                    resp = dis;
                }
                resp = max(resp, dis);
            }
        }
        cout << resp << endl;
    } else {
        cout << dist(c, d) << endl;
    }
	return 0;
}
