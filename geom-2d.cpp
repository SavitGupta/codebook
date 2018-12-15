ld INF = 1e100;
ld EPS = 1e-12;
ld pi = acos(-1);

struct point { 
    ld x, y; 
    point() {}
    point(ld x, ld y) : x(x), y(y) {}
    point(const point &p) : x(p.x), y(p.y) {}
    point operator + (const point &p) const { return point(x+p.x, y+p.y); }
    point operator - (const point &p) const { return point(x-p.x, y-p.y); }
    point operator * (ld c) const { return point(x*c, y*c); }
    point operator / (ld c) const { return point(x/c, y/c); }
    bool operator == (const point &p) { return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS; }
    bool operator != (const point &p) { return fabs(x - p.x) > EPS || fabs(y - p.y) > EPS; }
};

ld dot(point p, point q) { return p.x*q.x+p.y*q.y; }
ld dist2(point p, point q) { return dot(p-q,p-q); }
ld dist(point p, point q) { return sqrtl(dist2(p, q)); }
ld cross(point p, point q) { return p.x*q.y-p.y*q.x; }
ld magnitude(point p) { return sqrtl(dot(p, p)); }
ld to_degree(ld angle) { return angle * 180.0 / pi; }
ld angle_in_radian(point p, point q) { return acos(dot(p, q) / (magnitude(p) * magnitude(q))); }
ld angle_in_degree(point p, point q) { return to_degree(angle_in_radian(p, q)); }
ostream &operator<<(ostream &os, const point &p) { 
    return os << "(" << p.x << "," << p.y << ")"; 
}

// rotate a point CCW or CW around the origin
point RotateCCW90(point p) { return point(-p.y,p.x); }
point RotateCW90(point p) { return point(p.y,-p.x); }
point RotateCCW(point p, ld t) { 
    return point(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}

// project point c onto line through a and b
// assuming a != b
point ProjectPointLine(point a, point b, point c) {
    return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

// project point c onto line segment through a and b
point ProjectPointSegment(point a, point b, point c) {
    ld r = dot(b-a,b-a);
    if (fabs(r) < EPS) return a;
    r = dot(c-a, b-a)/r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b-a)*r;
}

// compute distance from c to segment between a and b
ld DistancePointSegment(point a, point b, point c) {
    return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
ld DistancePointPlane(ld x, ld y, ld z, ld a, ld b, ld c, ld d) {
    return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(point a, point b, point c, point d) { 
    return fabs(cross(b-a, c-d)) < EPS; 
}

bool LinesCollinear(point a, point b, point c, point d) { 
    return LinesParallel(a, b, c, d) && fabs(cross(a-b, a-c)) < EPS && fabs(cross(c-d, c-a)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(point a, point b, point c, point d) {
    if (LinesCollinear(a, b, c, d)) {
        if (dist2(a, c) < EPS || dist2(a, d) < EPS || dist2(b, c) < EPS || dist2(b, d) < EPS) 
            return true;
        if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0) 
            return false;
        return true;
    }
    if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
    if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
    return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
point ComputeLineIntersection(point a, point b, point c, point d) {
    b=b-a; d=c-d; c=c-a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
point ComputeCircleCenter(point a, point b, point c) {
    b=(a+b)/2;
    c=(a+c)/2;
    return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<point> &p, point q) {
    bool c = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i+1)%p.size();
        if ((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) && q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<point> &p, point q) {
    for (int i = 0; i < p.size(); i++)
        if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
        return true;
    return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<point> CircleLineIntersection(point a, point b, point c, ld r) {
    vector<point> ret;
    b = b-a;
    a = a-c;
    ld A = dot(b, b);
    ld B = dot(a, b);
    ld C = dot(a, a) - r*r;
    ld D = B*B - A*C;
    if (D < -EPS) return ret;
    ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
    if (D > EPS)
        ret.push_back(c+a+b*(-B-sqrt(D))/A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<point> CircleCircleIntersection(point a, point b, ld r, ld R) {
    vector<point> ret;
    ld d = sqrt(dist2(a, b));
    if (d > r+R || d+min(r, R) < max(r, R)) return ret;
    ld x = (d*d-R*R+r*r)/(2*d);
    ld y = sqrt(r*r-x*x);
    point v = (b-a)/d;
    ret.push_back(a+v*x + RotateCCW90(v)*y);
    if (y > 0)
        ret.push_back(a+v*x - RotateCCW90(v)*y);
    return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
ld ComputeSignedArea(const vector<point> &p) {
    ld area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}

ld ComputeArea(const vector<point> &p) {
    return fabs(ComputeSignedArea(p));
}

point ComputeCentroid(const vector<point> &p) {
    point c(0,0);
    ld scale = 6.0 * ComputeSignedArea(p);
    for (int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
    }
    return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<point> &p) {
    for (int i = 0; i < p.size(); i++) {
        for (int k = i+1; k < p.size(); k++) {
            int j = (i+1) % p.size();
            int l = (k+1) % p.size();
            if (i == l || j == k) continue;
            if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
                return false;
        }
    }
    return true;
}
