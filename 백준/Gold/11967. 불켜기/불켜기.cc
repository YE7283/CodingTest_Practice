#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct Point
{
	int y;
	int x;
};

int N;
int M;
int maxCnt = 0;

int map[101][101];			// 0: 불 꺼짐, 1: 불 켜짐
bool visited[101][101];		// 방문 여부
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

vector<Point> room_light[101][101];	// 방 - 불을 켤 수 있는 방 목록
queue<Point> Q;

int main()
{
	cin >> N >> M;
	int y, x, b, a;
	for (int i = 0; i < M; i++)
	{
		cin >> y >> x >> b >> a;
		room_light[y][x].push_back({b, a});
	}

	// 1,1 에서 출발 (불 켜져 있음)
	map[1][1] = 1;
	visited[1][1] = true;
	maxCnt++;
	Q.push({ 1, 1 });

	while (!Q.empty())
	{
		Point curPos = Q.front();
		Q.pop();
		
		// 스위치로 불 켜기
		for (int i = 0; i < room_light[curPos.y][curPos.x].size(); i++)
		{
			Point turnOn = room_light[curPos.y][curPos.x][i];
			if (map[turnOn.y][turnOn.x] == 1) continue;

			map[turnOn.y][turnOn.x] = 1;
			maxCnt++;

			// 불을 새로 켠 방과 인접한 곳 중에 이미 방문한 곳이 있다면, 새로 켠 방도 갈 수 있음
			for (int j = 0; j < 4; j++)
			{
				int ny = turnOn.y + dy[j];
				int nx = turnOn.x + dx[j];

				if (ny > 0 && ny <= N && nx > 0 && nx <= N && visited[ny][nx])
				{
					visited[turnOn.y][turnOn.x] = true;
					Q.push({ turnOn.y, turnOn.x });
					break;
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			int ny = curPos.y + dy[i];
			int nx = curPos.x + dx[i];

			if (ny <= 0 || ny > N || nx <= 0 || nx > N) continue;
			if (map[ny][nx] == 0 || visited[ny][nx]) continue;

			visited[ny][nx] = true;
			Q.push({ ny, nx });
		}
	}

	// 불을 켤 수 있는 방의 최대 개수 출력
	cout << maxCnt;

	return 0;
}