#include <cmath>
#include <algorithm>
using namespace std;
#define EPS 1e-9

typedef double dat;
dat sqr(dat x) { return (x * x); }

struct p2d {
	dat x, y;
	
	p2d(dat _x = 0, dat _y = 0): x(_x), y(_y) {};

	p2d operator+(p2d p) { return p2d(x + p.x, y + p.y); }
	p2d operator-(p2d p) { return p2d(x - p.x, y - p.y); }
	p2d operator*(dat k) { return p2d(k * x, k * y); }
	p2d operator/(dat k){ return p2d(x / k, y / k); }
	dat operator*(p2d p){ return (x * p.y - y * p.x); } // cross product
	dat operator^(p2d p){ return (x * p.x + y * p.y); } // dot product

	// dat = double?
	bool operator==(p2d p){ return (x == p.x && y == p.y); }
	bool operator<(p2d p) const { return (x < p.x || (x == p.x && y < p.y)); }
	bool operator>(p2d p) const { return (x > p.x || (x == p.x && y > p.y)); }

	double dist(p2d p){ return hypot(x - p.x, y - p.y); }
	double dist2(p2d p){ return sqr(x - p.x) + sqr(y - p.y);}
	double mod(){ return sqrt(x * x + y * y); }
	double mod2(){ return (x * x + y * y); }
	double ang(p2d p){ return atan2(*this * p, *this ^ p); } // [-pi,pi]
	double point_line_segment_distance(p2d p0, p2d p1){
		p2d v1 = *this - p0, v2 = p1 - p0;
		double u = (v1 ^ v2)/v2.mod2();
		if(u < -EPS) return (*this).dist(p0);
		if(u - 1 > EPS) return (*this).dist(p1);
		return (*this).dist(p0 + v2 * u);
	}
};

struct l2d {
	p2d s, v;

	l2d(){}
	l2d(p2d p0, p2d p1){
		s = p2d(p0.x, p0.y);
		v = p1 - p0, v = v/v.mod();
	}
	l2d(p2d p, double m) { s = p, v = p2d(cos(m), sin(m)); }
	l2d(double a, double b, double c) { // ax + by = c
		if(fabs(a) < EPS) v = p2d(1, -a/b), s = p2d(0, c/b);
		else v = p2d(-b/a, 1), s = p2d(c/a, 0);
	}

	bool point_on_line(p2d p){ return (v * (p - s)) == 0; } // dat = double?
	double slope() { return v.y/(double)v.x; }
};

struct c2d {
	p2d c;
	double r;

	c2d(){}
	c2d(p2d p0, p2d p1, double _r) { // cuidado: supoe que r >= p0.dist(p1)/2
		p2d mid = (p1 + p0)/2.0, v = (p1 - p0);
		double q = p0.dist(p1), d = sqrt(r*r - q*q/4.0);
		v = v / v.mod();
		swap(v.x, v.y);
		v.x = -v.x;
		c = mid + v * d;
		r = _r;
	};
	c2d(p2d p0, p2d p1, p2d p2){

	};

	bool p2d_inside(p2d p) { return c.dist(p) - r < EPS; } // d - r <= 0
	void tangents(p2d p, l2d &t1, l2d &t2) {
		p2d dir = p - c;
		double dang = atan2(dir.y, dir.x);
		double tang = asin(r/dir.mod());
		t1 = l2d(p, dang + tang);
		t2 = l2d(p, dang - tang);
	}
};

double l2d_p2d_distance(l2d l, p2d p) {
	double u = (p - l.s) ^ l.v;
	return p.dist(l.s + l.v * u);
}

int c2d_l2d_intersection(c2d c, l2d l, p2d &p1, p2d &p2) {
	double d = l2d_p2d_distance(l, c.c);
	if(d - c.r > EPS) return 0; // d > c.r => l2d nao corta a c2d
	else if(fabs(d - c.r) < EPS) {
		p1 = l.s + l.v*((c.c - l.s) ^ l.v);
		return 1; // d == c.r => l2d tangencia a c2d
	} else {
		p2d pc = l.s + l.v*((c.c - l.s) ^ l.v);
		double u = sqrt(c.r*c.r - d*d);
		p1 = pc + l.v*u;
		p2 = pc - l.v*u;
		return 2; // d < c.r => l2d forma uma corda em c2d
	}
}

l2d l2d_perpendicular(l2d l, p2d p) { // reta perpendicular a l, passando por p
	return l2d(p, p + p2d(-l.v.y, l.v.x));
}

// cuidado se c1 e c2 forem coincidentes
int c2d_c2d_intersection(c2d c1, c2d c2, p2d &p1, p2d &p2) {
	double d = c1.c.dist(c2.c);
	double x = (d*d - c2.r*c2.r + c1.r*c1.r)/(2*d); // distancia de c1.c ao eixo radical
	l2d l = l2d(c1.c, c2.c);
	l2d r = l2d_perpendicular(l, l.s + l.v*x); // eixo radical
	return c2d_l2d_intersection(c1, r, p1, p2);
}

// cuidado se l1 e l2 forem coincidentes
int l2d_l2d_intersection(l2d l1, l2d l2, p2d &pi){
	p2d p1 = p2d(l1.s.x, l1.s.y), p2 = l1.s + l1.v;
	p2d p3 = p2d(l2.s.x, l2.s.y), p4 = l2.s + l2.v;
	dat den = (p1.x - p2.x) * (p3.y - p4.y) - (p3.x - p4.x) * (p1.y - p2.y);
	if(fabs(den) < EPS) return 0; // linhas paralelas
	dat x = ((p1 * p2) * (p3.x - p4.x) - (p3 * p4) * (p1.x - p2.x));
	dat y = ((p1 * p2) * (p3.y - p4.y) - (p3 * p4) * (p1.y - p2.y));
	pi = p2d(x, y)/den;
	return 1; // pi = ponto de intersecao
}
