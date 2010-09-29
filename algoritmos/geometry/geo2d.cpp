/* Geometry 2D {{{ */
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
		v = p1 - p0;
	}
	l2d(p2d p, double m) { s = p, v = p2d(cos(m), sin(m)); }

	bool point_on_line(p2d p){ return (v * (p - s)) == 0; } // dat = double?
	double slope() { return v.y/(double)v.x; }
};

struct c2d {
	p2d center;
	double r;

	c2d(){}
	c2d(p2d p0, p2d p1, double _r){
		p2d mid = (p1 + p0)/(double)2, v = (p1 - p0);
		double q = p0.dist(p1), d = sqrt(r * r - q * q / (double) 4);
		v = v / v.mod();
		swap(v.x, v.y);
		v.x = -v.x;
		center = mid + v * d;
		r = _r;
	};
	c2d(p2d p0, p2d p1, p2d p2){

	};

	void tangents(p2d p, l2d &t1, l2d &t2) {
		p2d dir = p - center;
		double dang = atan2(dir.y, dir.x);
		double tang = asin(r/dir.mod());
		t1 = l2d(p, dang + tang);
		t2 = l2d(p, dang - tang);
	}
};

double l2d_p2d_distance(l2d l, p2d p) {
	double u = ((p - l.s) ^ l.v)/l.v.mod2();
	return p.dist(l.s + l.v * u);
}

int c2d_c2d_intersection(c2d c1, c2d c2, p2d &p0, p2d &p1) {
	// TODO
	return 0;
}

int c2d_l2d_intersection(c2d c, l2d l, p2d &p1, p2d &p2) {
	double d = l2d_p2d_distance(l, c.center);
	if(d - c.r > EPS) return 0; // d > c.r => l2d nao corta a c2d
	else if(fabs(d - c.r) < EPS) {
		p1 = l.s + l.v*(((c.center - l.s) ^ l.v)/l.v.mod2());
		return 1; // d == c.r => l2d tangencia a c2d
	} else {
		p2d pc = l.s + l.v*(((c.center - l.s) ^ l.v)/l.v.mod2());
		double u = sqrt(c.r*c.r - d*d)/l.v.mod2();
		p1 = pc + l.v*u;
		p2 = pc - l.v*u;
		return 2; // d < c.r => l2d forma uma corda em c2d
	}
}

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
/* }}} */
