double polygon_area(polygon q) {
	double r = 0.0;
	int i;
	for(i = 1; i < q.n-1; i++){
		int x1 = p.p[i].x - p.p[0].x;
		int y1 = p.p[i].y - p.p[0].y;
		int x2 = p.p[i+1].x - p.p[0].x;
		int y2 = p.p[i+1].y - p.p[0].y;
		r += x1*y2 - x2*y1;
	}
	return fabs(r/2.0);
}
