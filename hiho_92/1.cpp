#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <bitset>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <set>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>
#include <ctime>
#include <climits>

using namespace std;

typedef pair<int, int> pii;
#define mkp make_pair

long long powerMod(long long a, long long b, long long n) {
	// a^b mod n
	long long r = 1, base = a;
	while (b != 0) {
		if (b & 1) {
			std::cout << "b: " << r << std::endl;
			std::cout << "base: " << base << std::endl;
			r *= base;
			std::cout << "a: " << r << std::endl;
			r %= n;
		}
		base *= base;
		base %= n;
		b >>= 1;
	}
	return r;
}

bool isPrime(long long n) {
	if (2 == n) {
		return true;
	}
	if (n % 2 == 0) {
		return false;
	}

	// 将 n-1 表示成 d*2^r, 其中 d 为奇数, r尽可能大
	long long d = -1, r = -1;
	for (int i = 0; i < 63; i++) {
		if ( (n-1)%(1LL<<i) == 0 && ((n-1)/(1LL<<i))%2 == 1 ) {
			r = i;
			d = (n-1)/(1LL<<r);
		}
	}

	std::cout << d << std::endl;
	std::cout << r << std::endl;
	// a^(d*2^i) mod n
	long long test[] = {2, 3, 7, 11, 13, 17, 61, 24251};
	for (auto a : test) {
		if (a >= n) {
			continue;
		}
		for (long long i = r; i >= 0; i--) {
			long long rem = powerMod(a, d*(1LL<<i), n);
			if (rem == 1) {
				// continue
			} else if (rem == n - 1) {
				break;
			} else {
				return false;
			}
		}
	}

	return true;
}

int main(int argc, char *argv[])
{

#ifdef TEST_OJ
	if (!freopen("test.txt", "r", stdin)) {
		printf("Can't open test.txt!\n");
	}
#endif

	int T;
	scanf("%d", &T);

	for (int case_num = 0; case_num < T; case_num++) {
		long long a;
		scanf("%lld", &a);

		if (isPrime(a)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	

	return 0;
}

