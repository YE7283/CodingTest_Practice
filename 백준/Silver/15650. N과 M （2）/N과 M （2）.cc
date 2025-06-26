#include <iostream>

using namespace std;

int N;
int M;
bool visited[9];

void DFS(int num, string tmp)
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

	for (int i = num; i <= N; i++)
	{
		if (visited[i]) continue;
		
		visited[i] = true;
		tmp += (i + '0');

		DFS(i + 1, tmp);

		tmp.pop_back();
		visited[i] = false;
	}
}

int main()
{
	cin >> N >> M;

	DFS(1, "");

	return 0;
}