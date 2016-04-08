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

int a[1005];
int main(int argc, char *argv[])
{

#ifdef TEST_OJ
	if (!freopen("test.txt", "r", stdin)) {
		printf("Can't open test.txt!\n");
	}
#endif

	int TASKS;
	scanf("%d", &TASKS);
	for (int cs = 0; cs < TASKS; cs++) {
		int N, P, W, H;
		scanf("%d %d %d %d", &N, &P, &W, &H);
		for (int i = 0; i < N; i++) {
			scanf("%d", &a[i]);
		}
			int ans = -1;

			int f = 1;
			for (f = 1; f < 1000000; f++) {
				int L = W / f;
				if (L == 0) {
					break;
				}
				int lines = 0;
				for (int j = 0; j < N; j++) {
					lines += (a[j] + L - 1) / L;
				}
				int HL = H / f;
				if (HL == 0) {
					break;
				}
				int pages = (lines + HL - 1) /HL;
				if (pages > P) {
					break;
				}
			}
			ans = f - 1;
			printf("%d\n", ans);

			//int low = 1, high = 1000000;

			//while (low <= high) {
				//int mid = (low + high) / 2;
				//int L = W / mid;
				//if (L == 0) {
					//high = mid - 1;
					//continue;
				//}

				//int lines = 0;
				//for (int j = 0; j < N; j++) {
					//lines += (a[j] + L - 1) / L;
				//}
				//int HL = H / mid;
				//int pages = (lines + HL - 1) / HL;
				//if ( pages  > P ) {
					//low = mid + 1;
				//} else if (pages < P) {
					//high = mid;
				//} else {
					//high = mid;
					//break;
				//}
			//}

			//ans = high;
			//printf(" %d\n", ans);
	}
	

	return 0;
}

