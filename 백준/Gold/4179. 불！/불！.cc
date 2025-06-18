#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point
{
	int y;
	int x;
};

int R;	// 미로 행의 개수
int C;	// 미로 열의 개수

char maze[1001][1001];
vector<vector<int>> distF(1001, vector<int>(1001, -1));	// 불이 각 칸까지 도달하는 시간
vector<vector<int>> distJ(1001, vector<int>(1001, -1));	// 지훈이가 각 칸까지 도달하는 시간

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

queue<Point> fireQ;
queue<Point> jihoonQ;

int main()
{
	cin >> R >> C;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> maze[i][j];

			if (maze[i][j] == 'F')
			{
				fireQ.push({ i, j });
				distF[i][j] = 0;
			}
			else if (maze[i][j] == 'J')
			{
				jihoonQ.push({ i, j });
				distJ[i][j] = 0;
			}
		}
	}

	// 불 BFS
	while (!fireQ.empty())
	{
		Point curPos = fireQ.front();
		fireQ.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = curPos.y + dy[i];
			int nx = curPos.x + dx[i];

			if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
			if (maze[ny][nx] == '#' || distF[ny][nx] >= 0) continue;

			fireQ.push({ ny, nx });
			distF[ny][nx] = distF[curPos.y][curPos.x] + 1;
		}
	}

	// 지훈 BFS
	while (!jihoonQ.empty())
	{
		Point curPos = jihoonQ.front();
		jihoonQ.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = curPos.y + dy[i];
			int nx = curPos.x + dx[i];
			int nextDist = distJ[curPos.y][curPos.x] + 1;

			// 미로 범위를 벗어났다 => 탈출했다
			if (ny < 0 || ny >= R || nx < 0 || nx >= C)
			{
				cout << nextDist << "\n";
				return 0;
			}

			if (maze[ny][nx] == '#' || distJ[ny][nx] >= 0) continue;
			if (distF[ny][nx] >= 0 && distF[ny][nx] <= nextDist) continue;

			jihoonQ.push({ ny, nx });
			distJ[ny][nx] = nextDist;
		}
	}

	// 지훈이가 불이 도달하기 전에 미로를 탈출할 수 없는 경우 IMPOSSIBLE 출력
	cout << "IMPOSSIBLE\n";

	return 0;
}