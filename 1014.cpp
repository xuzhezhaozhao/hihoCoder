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

typedef struct Node {
	struct Node *ch[26] = {NULL};
	int cnt = 0;
} Node;

int main(int argc, char *argv[])
{

#ifdef TEST_OJ
	if (!freopen("test.txt", "r", stdin)) {
		printf("Can't open test.txt!\n");
	}
#endif

	int n, m;
	char word[11];
	while (scanf("%d", &n) != EOF) {
		Node root;

		for (int i = 0; i < n; i++) {
			scanf("%s", word);
			int len = strlen(word);

			Node *cur = &root;
			for (int k = 0; k < len; k++) {

				if (cur->ch[ word[k]-'a' ] == NULL) {
					cur->ch[ word[k]-'a' ] = new Node();
				}

				cur = cur->ch[ word[k]-'a' ];
				++(cur->cnt);
			}
		}


		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s", word);
			int len = strlen(word);
			Node *cur = &root;
			for (int k = 0; k < len; k++) {
				cur = cur->ch[ word[k]-'a' ];

				if (!cur) {
					break;
				}
			}
			if (!cur) {
				printf("0\n");
			} else {
				printf("%d\n", cur->cnt);
			}
		}
	}

	return 0;
}

