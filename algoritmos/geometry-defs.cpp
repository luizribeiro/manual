typedef struct { int x, y; } point;
typedef struct { point p[MAX_VERTS]; int n; } polygon;
typedef struct { point c; double r; } circle;

int distsqr(point a, point b) {
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

int cross(point a, point b, point c) {
	return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}
