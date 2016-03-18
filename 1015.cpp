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

char src[1000001];
char pattern[10001];
int next[10001];

inline void getNext(const char *pattern, int len, int next[]) {
	next[0] = 0;
	int mat = 0;
	for (int i = 1; i < len;) {
		if (pattern[i] == pattern[mat]) {
			next[i] = ++mat;
			++i;
		} else {
			if (mat > 0) {
				mat = next[mat - 1];
			} else {
				next[i] = 0;
				++i;
			}
		}
	}
}

void kmpProcess(string t) {
    int n = t.length();
    //vector<int> lps(n, 0);
    for (int i = 1, len = 0; i < n; ) {
        if (t[i] == t[len])
            ::next[i++] = ++len;
        else if (len) len = ::next[len - 1];
		else ::next[i++] = 0;
    }
}

inline int match(const char *pattern, int len1, const char *src, int len2) {
	int res = 0;
	//getNext(pattern, len1, ::next);
	kmpProcess(string(pattern));

	int src_i = 0, pat_j = 0;
	while (src_i < len2) {
		int matched = pat_j;
		while (pat_j < len1 && src_i < len2 && pattern[pat_j] == src[src_i]) {
			++matched;
			++pat_j;
			++src_i;
		}

		if (pat_j == len1) {
			// match once
			++res;
		}
		if (matched == 0) {
			++src_i;
		} else {
			pat_j = ::next[ matched-1 ];
		}
	}

	return res;
}

int main(int argc, char *argv[])
{

#ifdef TEST_OJ
	if (!freopen("test.txt", "r", stdin)) {
		printf("Can't open test.txt!\n");
	}
#endif

	int N;
	while (scanf("%d", &N) != EOF) {
		for (int i = 0; i < N; i++) {
			scanf("%s", pattern);
			scanf("%s", src);

			printf("%d\n", match(pattern, strlen(pattern), src, strlen(src)));
		}
	}

	return 0;
}

