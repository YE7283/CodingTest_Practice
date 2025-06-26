#include <iostream>

using namespace std;

int N;
int M;
bool visited[9];

// 1~N까지 자연수 중에서 중복 없이 M개를 고른 수열을 모두 구하라
void DFS(string tmp)
{
	if (tmp.length() == M)
	{
		for (int i = 0; i < M; i++)
		{
			cout << tmp[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 1; i <= N; i++)
	{
		if (visited[i]) continue;
		
		visited[i] = true;
		tmp += (i + '0');
		DFS(tmp);
		tmp.pop_back();
		visited[i] = false;
	}
}

int main()
{
	cin >> N >> M;

	DFS("");

	return 0;
}