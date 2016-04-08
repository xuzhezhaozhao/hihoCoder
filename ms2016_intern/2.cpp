#include <cassert>
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

typedef struct node {
	struct node* bit[2] = {NULL, NULL};
	int allow = -1;
	int seq = -1;
} node;

int main(int argc, char *argv[])
{

#ifdef TEST_OJ
	if (!freopen("test.txt", "r", stdin)) {
		printf("Can't open test.txt!\n");
	}
#endif

	int N, M;
	scanf("%d %d\n", &N, &M);

	char buf[10];
	int ip[4];
	int bits;
	node root;
	root.bit[0] = NULL;
	root.bit[1] = NULL;
	root.allow = -1;
	root.seq = -1;

	int c;
	node *cnode = &root;
	for (int i = 0; i < N; i++) {
		scanf("%s", buf);
		for (int j = 0; j < 4; j++) {
			scanf("%d", &ip[j]);
			c = getchar();
		}
		if (c == '/') {
			scanf("%d\n", &bits);
		} else {
			bits = 8*4;
		}

		int allow = -1;
		if ("allow" == string(buf)) {
			allow = 1;
		} else {
			allow = 0;
		}

		if (bits == 0) {
			if (root.seq == -1) {
				root.allow = allow;
				root.seq = i;
			}
			continue;
		}

		// 开始新的
		cnode = &root;
		for (int b = 0; b < bits; b++) {
			int index = b / 8;
			int n = ip[index];
			int bi = b % 8;
			int cb = (n >> (7-bi)) & 1;

			if (cnode->bit[cb] == NULL) {
				cnode->bit[cb] = new node();
				cnode->bit[cb]->allow = -1;
				cnode->bit[cb]->seq = -1;
				cnode->bit[cb]->bit[0] = NULL;
				cnode->bit[cb]->bit[1] = NULL;
			}
			cnode = cnode->bit[cb];
		}
		if (cnode->seq == -1) {
			cnode->seq = i;
			cnode->allow = allow;
		}
	}


	for (int i = 0; i < M; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%d", &ip[j]);
			getchar();
		}
		node *cnode = &root;
		int cur_seq = cnode->seq;
		int allowed = cnode->allow;
		for (int b = 0; b < 32; b++) {
			int index = b / 8;
			int n = ip[index];
			int bi = b % 8;
			int cb = (n >> (7-bi)) & 1;

			cnode = cnode->bit[cb];

			if (cnode == NULL) {
				break;
			}

			if (cnode->allow != -1) {
				if (cur_seq == -1 || cnode->seq < cur_seq) {
					allowed = cnode->allow;
					cur_seq = cnode->seq;
				}
			}
		}

		if (0 == allowed) {
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	}

	return 0;
}

