// This is a collection of useful code for solving problems that
// involve modular linear equations.  Note that all of the
// algorithms described here work on nonnegative integers.

typedef vector<int> vll;
typedef pair<int,int> pii;
const int mod = 1e9 + 7;

// return a % b (positive value)
int takemod(int a, int b = mod) {
  return ((a%b)+b)%b;
}

// computes gcd(a,b)
int gcd(int a, int b) {
    int tmp;
    while(b) { 
        a%=b; 
        swap(a, b); 
    }
    return a;
}

// computes lcm(a,b)
int lcm(int a, int b) {
    return (a / gcd(a,b)) * b;
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {  
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a/b;
        int t = b; b = a%b; a = t;
        t = xx; xx = x-q*xx; x = t;
        t = yy; yy = y-q*yy; y = t;
    }
    return a;
}

// finds all solutions to ax = b (mod n)
vll modular_linear_equation_solver(int a, int b, int n) {
    pii x, y;
    vll solutions;
    pii d = extended_euclid(a, n, x, y);
    if (!(b%d)) {
        x = takemod (x*(b/d), n);
        for (int i = 0; i < d; i++)
          solutions.push_back(takemod(x + i*(n/d), n));
    }
    return solutions;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
    int x, y;
    int d = extended_euclid(a, n, x, y);
    if (d > 1) return -1;
    return takemod(x,n);
}

// Chinese remainder theorem (special case): find z such that
// z % x = a, z % y = b.  Here, z is unique modulo M = lcm(x,y).
// Return (z,M).  On failure, M = -1.
pii chinese_remainder_theorem(int x, int a, int y, int b) {
    int s, t;
    int d = extended_euclid(x, y, s, t);
    if (a%d != b%d) return make_pair(0, -1);
    return make_pair(takemod(s*b*x+t*a*y,x*y)/d, x*y/d);
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (x[i]).  Return (z,M).  On 
// failure, M = -1.  Note that we do not require the a[i]'s
// to be relatively prime.
pii chinese_remainder_theorem(const vll &x, const vll &a) {
    pii ret = make_pair(a[0], x[0]);pii
    for (int i = 1; i < x.size(); i++) {
        ret = chinese_remainder_theorem(ret.first, ret.second, x[i], a[i]);
        if (ret.second == -1) break;
    }
    return ret;
}

// computes x and y such that ax + by = c; on failure, x = y =-1
bool linear_diophantine(int a, int b, int c, int &x, int &y, int &g) {
    g = gcd(a,b);
    if (c%g) {
        return false;
    } else {
        x = c/g * mod_inverse(a/g, b/g);
        y = (c-a*x)/b;
    }
    return true;
}

int main() {
    // To find solution of ax + by = c, call find_any_solution(a, b, c, x, y, g);
    // x, y, g are just random integers initially, g is gcd(a, b);
    int x, y, g, a, b, c;
    cin >> a >> b >> c;
    if(!linear_diophantine(a, b, c, x, y, g)); // No solution
    assert(c == a * x + b * y);
    int qa = b / g, qb = b / g;
    // X = x + k * qa, Y = y - k * qb are also solutions of the equation where k is any integer.
}
