#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point
{
	int y;
	int x;
};

int N;	// 행 개수
int M;	// 열 개수

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

vector<vector<int>> maze(101, vector<int>(101, -1));
vector<vector<int>> visited(101, vector<int>(101, -1));

// 최대 100*100
// 1: 이동가능, 0: 이동 불가

void BFS()
{
	queue<Point> q;
	q.push({ 1, 1 });
	visited[1][1] = 1;
	
	while (!q.empty())
	{
		Point curPoint = q.front();
		int curCnt = visited[curPoint.y][curPoint.x];
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = curPoint.y + dy[i];
			int nx = curPoint.x + dx[i];

			if (ny <= 0 || ny > N || nx <= 0 || nx > M) continue;	// 미로 범위 밖
			if (maze[ny][nx] == 0) continue;	// 이동 못하는 곳이면 가지 않음
			if (visited[ny][nx] != -1 && visited[ny][nx] <= curCnt + 1) continue;

			visited[ny][nx] = curCnt + 1;
			q.push({ ny, nx });
		}
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		string tmp;
		cin >> tmp;

		for (int j = 0; j < M; ++j)
		{
			maze[i][j + 1] = (tmp[j] - '0');
		}
	}

	BFS();

	// 1,1 에서 출발 N,M 도착할때 지나야하는 최소 칸 수 출력
	cout << visited[N][M];

	return 0;
}