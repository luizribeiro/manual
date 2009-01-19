/* c = circulo que passa por a, b e tem raio r (ordem a, b importa) */
bool circle2ptsRad(point a, point b, double r, circle &c) {
	double det = r*r/distsqr(a, b) - 0.25;
	if(det < 0) return false;
	double h = sqrt(det);
	c.r = r;
	c.c.x = (a.x + b.x)*0.5 + (a.y - b.y)*h;
	c.c.y = (a.y + b.y)*0.5 + (b.x - a.x)*h;
	return true;
}
