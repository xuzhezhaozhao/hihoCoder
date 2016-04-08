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

int dp1[105][105];
int dp2[105][105];
bool maze[105][105];
int main(int argc, char *argv[])
{

#ifdef TEST_OJ
	if (!freopen("test.txt", "r", stdin)) {
		printf("Can't open test.txt!\n");
	}
#endif

	int N, M;
	char buf[105];
	// true: 可以通过, 否则不可以通过
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%s\n", buf);
		for (int j = 0; j < M; j++) {
			maze[i][j] = (buf[j] == '.');
		}
	}

	memset(dp1, -1, sizeof(dp1));
	memset(dp2, -1, sizeof(dp2));

	for (int j = 0; j < M; j++) {
		int b = 0;
		for (int k = 0; k <= j; k++) {
			b += maze[0][k] ? 0 : 1;
		}
		if (j + 1 < M) {
			b += maze[0][j+1] ? 1 : 0;
		}
		dp1[0][j] = b;
	}

	for (int i = 0; i < N; i++) {
		int b = 0;
		for (int k = 0; k <= i; k++) {
			b += (maze[k][0] ? 0 : 1);
		}

		if (i + 1 < N) {
			b += maze[i+1][0] ? 1 : 0;
		}
		if (M > 1) {
			b += maze[0][1] ? 1 : 0;
		}

		dp2[i][0] = b;
	}

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < M; j++) {

			dp1[i][j] = 100000;
			dp2[i][j] = 100000;

			int last1 = 0, last2 = 0;
			if (i + 1 < N) {
				last2 = maze[i+1][j] ? 1 : 0;
			}
			if (j + 1 < M) {
				last1 = maze[i][j+1] ? 1 : 0;
			}


			// 上
			// 第 i 行, k = 0 ~ i - 1 行
			for (int k = 0; k <= i - 1; k++) {
				int b = 0;
				// 之间的障碍物
				for (int r = k + 1; r <= i; r++) {
					b += maze[r][j] ? 0 : 1;
				}
				dp2[i][j] = min(dp2[i][j], dp1[k][j] + b + last2);
			}

			// 左
			// 第 k 列, k = 0 ~ j - 1 列
			for (int k = 0; k <= j - 1; k++) {
				int b = 0;
				for (int c = k + 1; c <= j; c++) {
					b += maze[i][c] ? 0 : 1;
				}
				dp1[i][j] = min(dp1[i][j], dp2[i][k] + b + last1);
			}
		}
	}
	if (dp1[N-1][M-1] == -1) {
		dp1[N-1][M-1] = 100000;
	}
	if (dp2[N-1][M-1] == -1) {
		dp2[N-1][M-1] = 100000;
	}

	int ans = min(dp1[N-1][M-1], dp2[N-1][M-1]);
	printf("%d\n", ans);

	return 0;
}

