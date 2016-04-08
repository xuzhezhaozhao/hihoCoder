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

static int sptype[105][105][105];
// 上, 下, 左, 右, 前, 后
const int dx[] = {0, 0, 1, 0, 0, -1};
const int dy[] = {0, 1, 0, 0, -1, 0};
const int dz[] = {1, 0, 0, -1, 0, 0};

static bool visited[105][105][105];
static bool touched[105][105][105];

// 0 ~ 101 都是合法的, 外扩1, 算法需要
static inline bool validPoint(int x, int y, int z) {
	if (x < 0 || x > 101 || y < 0 || y > 101 || z < 0 || z > 101) {
		return false;
	}
	return true;
}

struct Point {
	int x, y, z;
	Point(int _x, int _y, int _z): x(_x), y(_y), z(_z) {}
};

static void bfs(int _x, int _y, int _z) {
	queue <Point> Q;
	Q.push(Point(_x, _y, _z));
	visited[_x][_y][_z] = true;
	while (!Q.empty()) {
		auto point = Q.front();
		Q.pop();
		for (int dir = 0; dir < 6; dir++) {
			int nx = point.x + dx[dir];
			int ny = point.y + dy[dir];
			int nz = point.z + dz[dir];
			if (!validPoint(nx, ny, nz) || visited[nx][ny][nz]) {
				continue;
			}
			if (1 != sptype[nx][ny][nz]) {
				Q.push(Point(nx, ny, nz));
				visited[nx][ny][nz] = true;
			} else {
				touched[nx][ny][nz] = true;
			}
		}
	}
}

static void dfs(int _x, int _y, int _z) {
	stack <Point> S;
	S.push(Point(_x, _y, _z));
	visited[_x][_y][_z] = true;
	while (!S.empty()) {
		auto point = S.top();
		S.pop();
		for (int dir = 0; dir < 6; dir++) {
			int nx = point.x + dx[dir];
			int ny = point.y + dy[dir];
			int nz = point.z + dz[dir];
			if (!validPoint(nx, ny, nz) || visited[nx][ny][nz]) {
				continue;
			}

			if (1 != sptype[nx][ny][nz]) {
				// 没有被点占据
				S.push(Point(nx, ny, nz));
				visited[nx][ny][nz] = true;
			} else {
				touched[nx][ny][nz] = true;
			}
		}
	}
}

int main(int argc, char *argv[])
{

#ifdef TEST_OJ
	if (!freopen("test.txt", "r", stdin)) {
		printf("Can't open test.txt!\n");
	}
#endif

	int T;
	if (scanf("%d", &T)) {};
	for (int case_num = 0; case_num < T; case_num++) {
		int N;
		if (scanf("%d", &N)) {};
		// 初始化 sptype 数组
		// -1: 没有任何访问
		// 1: 点被占据了
		// 2: 被占据点的相邻未被占据点
		memset(sptype, -1, sizeof(sptype));
		for (int x = 0; x <= 101; x++) {
			for (int y = 0; y <= 101; y++) {
				// z = 0 的点为 ground
				// z = 1 的点为相邻点
				sptype[x][y][0] = 1;
				sptype[x][y][1] = 2;
			}
		}

		bool ok = true;
		// 判断相邻性
		for (int coord_num = 0; coord_num < N; coord_num++) {
			int x, y, z;
			if (scanf("%d %d %d", &x, &y, &z)) {}
			if (-1 == sptype[x][y][z]) {
				// No 相邻条件不满足
				ok = false;
				goto end;
			} else if (1 == sptype[x][y][z]) {
				// No 点重复了
				ok = false;
				goto end;
			} else {
				// sptype[x][y][z] == 2
				sptype[x][y][z] = 1;		// 占据该点
				// 更新6个方向的相邻点
				for (int dir = 0; dir < 6; dir++) {
					int nx = x + dx[dir];
					int ny = y + dy[dir];
					int nz = z + dz[dir];
					// 检查点是否越界
					if ( !validPoint(nx, ny, nz) ) {
						continue;
					}
					if (-1 == sptype[nx][ny][nz]) {
						sptype[nx][ny][nz] = 2;
					}
				} // dir 6 个方向
			}
		} // coord_num

		// dfs 判断可到达性
		memset(visited, 0, sizeof(visited));
		memset(touched, 0, sizeof(touched));
		bfs(101, 101, 101);

		for (int x = 1; x <= 100; x++) {
			for (int y = 1; y <= 100; y++) {
				for (int z = 1; z <= 100; z++) {
					if (1 == sptype[x][y][z]) {
						// 被点占据, 合法的话一定可以访问到
						if (!touched[x][y][z]) {
							// 不合法
							ok = false;
							goto end;
						}
					}
				}
			}
		}

	end:
		if (ok) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	} // case_num

	return 0;
}

