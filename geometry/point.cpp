struct Point {
	ll x, y;

	Point() : x(), y() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}

	Point operator + (const Point &a) const {
		return Point(x + a.x, y + a.y);
	}
	Point operator - (const Point &a) const {
		return Point(x - a.x, y - a.y);
	}
	ll operator * (const Point &a) const {  // cross product
		return x * a.y - y * a.x;
	}
};

int getQ(const Point &a) {
	if (a.y != 0) return (a.y > 0 ? 0 : 1);
	return (a.x >= 0 ? 0 : 1);
}
bool cmp(const Point &v, const Point &u) {
	int q1 = getQ(v), q2 = getQ(u);
	if (q1 != q2) return q1 < q2;
	return v * u > 0;
}