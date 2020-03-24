#include <bits/stdc++.h>
#include <sys/time.h>
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define sz(x) (int)((x).size())
#define debug(x) cout << #x << ":" << x << ' ';
#define debugg(x) cout << #x << ":" << x << ' ' << "\n";
#define endl "\n"
#define L(X) ((X)<<1)
#define R(X) (((X)<<1)|1)
#define M(X,Y) (((X)+(Y))>>1)

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const long long int LLINF = 0x3f3f3f3f3f3f3f3f;
const double EPS = 1e-9;
const double PI = acos(-1);

template<typename T>   T max_self(T& a, T b) { if (a < b) a = b; return a; }
template<typename T>   T min_self(T& a, T b) { if (a > b) a = b; return a; }
template<typename T>   T add(T x, T y) { return ((x % MOD)  + (y % MOD)) % MOD;}
template<typename T>   T mul(T x, T y) { return ((x % MOD) * (long long)(y % MOD)) % MOD;}
template<typename T>   T sub(T x, T y) { return add(x, -y + MOD);}
template<typename T>   T gcd(T a, T b) { return b ? gcd(b, a % b) : a;}
template<typename T>   T lcm(T a, T b) { return a / gcd(a, b) * b;}
template<typename T>   vector<T> read(vector<T>& v, int n) {v.resize(n); for (auto &x : v)cin >> x;}
template<typename T>   void trav(vector<T> &v) {for (int i = 0 ; i < (int)v.size() ; ++i) {cout << v[i]; if (i != (int)v.size() - 1) cout << ' ';}}
int lg2(long long x)   {   return 64 - __builtin_clzll(x) - 1;    }
int lg2(int x)   {   return 32 - __builtin_clz(x) - 1;    }



//do stuff
//Variables Declaration

// def maxSubArraySum_kadane(a):
//     size = len(a)
//     max_so_far = -float("inf")
//     max_ending_here = 0
//     first_i = -1
//     for i in range(0, size):
//         max_ending_here = max_ending_here + a[i]
//         if (max_so_far < max_ending_here):
//             max_so_far = max_ending_here
//             first_i = i

//         if max_ending_here < 0:
//             max_ending_here = 0

//     mySum = 0
//     res  = []
//     while mySum != max_so_far :
//         mySum+= a[first_i]
//         res.append(a[first_i])
//         first_i-=1

//     Res = [max_so_far ]
//     # print(max_so_far)
//     for x in reversed(res):
//         # print(x , end = " ")
//         Res.append(x)
//     return Res


void maxSubArraySum(vector<ll> vect, bool show = true)
{
	size_t size = vect.size();
	ll max_so_far = LONG_LONG_MIN, max_ending_here = 0;
	size_t first_i = -1;

	for (size_t i = 0; i < size; i++)
	{
		max_ending_here = max_ending_here + vect[i];
		if (max_so_far < max_ending_here) {
			max_so_far = max_ending_here;
			first_i = i ;
		}

		if (max_ending_here < 0)
			max_ending_here = 0;
	}

	ll mySum = 0;
	vector<ll> res;
	while (mySum != max_so_far) {
		mySum += vect[first_i];
		res.push_back(vect[first_i]);
		first_i--;
	}
	if (show) {
		cout << mySum ;
		for (auto it = res.rbegin() ; it != res.rend() ; ++it) {
			cout << " " << *it ;
		}
	}
}

bool first = true ; 
ll random(ll min, ll max, std::mt19937 gen ) //range : [min, max]
{
	max++;
	if (first)
	{
		srand( time(NULL) ); //seeding for the first time only!
		first = false;
	}
	return min + gen() % (( max + 1 ) - min);
}

void generateList(vector<ll> & vect, ll size,std::mt19937 gen, ll minval = -10000, ll maxval = 10000 ) {
	vect.resize(size);
	std::uniform_int_distribution<> dis(minval, maxval);
	for (auto& x : vect) {
		x = dis(gen);
	}
}


template<class T>
T read_urandom()
{
	union {
		T value;
		char cs[sizeof(T)];
	} u;

	std::ifstream rfin("/dev/urandom");
	rfin.read(u.cs, sizeof(u.cs));
	rfin.close();

	return u.value;
}

int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	// cin.tie(0);
	// cout.tie(0);
    std::random_device rd;

	struct timeval begin, end;
	double elapsed = 0;

	gettimeofday(&begin, NULL);
	int seed = read_urandom<int>();
	std::mt19937 g2 (seed);

	srand(seed);
	cerr << "SEED:" << seed << endl;

	ll size = ll( 1ll << stoi(argv[1]));
	cerr << "Size: " << size << endl;
	vector<ll> vect;

	// ll x = 0 ;
	// while(cin >> x ){
	// 	vect.push_back(x);
	// }

	generateList(vect, size,g2);
	string test = "data/test" + string(argv[1]);
	freopen(test.c_str(), "w+", stdout);
	//generate input
	for (auto c : vect) {
		cout << c << " ";
	}
	cerr << "Vector size will be : " << vect.size() << endl;

	//generate output
	string result = "data/result" + string(argv[1]);

	freopen(result.c_str(), "w+", stdout);

	maxSubArraySum(vect, 1);
	// //End Timed stuff
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec) / 1000000.0);
	cerr << "~ Genaration took " << elapsed << " seconds using GetTimeOfDay" << endl;;


	return 0;
}
