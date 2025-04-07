#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 4*4 맵
// 그림은 8종류, 2장씩 있음
// 키 조작 횟수 오르는 기준
// 1. 방향키 중 하나 누름 => 누른 방향으로 1칸 이동
// 2. ctrl + 방향키 => 누른 방향에 있는 가장 가까운 카드로 이동 (없으면 가장 끝으로 이동)
// 3. enter => 카드 뒤집기

// 한번 쫙 돌아서 어느 위치에 어느 그림이 있는지 저장
// 어느 그림을 어떤 순서로 제거하냐에 따라 횟수가 달라짐
// 그렇다면 모든 경우의 수를 돌려봐야 함... => 순열

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

struct Point
{
    int y;
    int x;
};

// 현재 커서 위치에서 목표 카드까지의 최단거리 구하는 bfs 함수
int dist(vector<vector<int>>& board, Point origin, Point dest)
{
    vector<vector<int>> d(4, vector<int>(4, -1));   // 4*4 배열 (-1로 채워짐)
    d[origin.y][origin.x] = 0;
    
    queue<Point> q;
    q.push(origin);
    while(!q.empty())
    {
        Point cur = q.front();
        q.pop();
        
        for(int dir = 0; dir < 4; ++dir)
        {
            int accum = 0;  // dir 방향으로 움직일 때 카드 or 끝까지의 거리
            while(true)
            {
                int ny = cur.y + dy[dir] * accum;
                int nx = cur.x + dx[dir] * accum;
                if(ny + dy[dir] < 0 || ny + dy[dir] > 3 || nx + dx[dir] < 0 || nx + dx[dir] > 3) break;
                if(accum != 0 && board[ny][nx] != 0) break;     // 끝까지 가기 전에 카드에 도달하면 반복문 탈출
                accum++;
            }
            
            for(int i: {1, accum})
            {
                int ny = cur.y + dy[dir] * i;
                int nx = cur.x + dx[dir] * i;
                if(ny < 0 || ny > 3 || nx < 0 || nx > 3) continue;
                if(d[ny][nx] == -1)
                {
                    d[ny][nx] = d[cur.y][cur.x] + 1;
                    q.push({ny, nx});
                }
            }
        }
    }
    
    
    return d[dest.y][dest.x];
}


// 커서의 처음 위치 (r, c)
int solution(vector<vector<int>> board, int r, int c) 
{
    int answer = 21e8;
    vector<Point> card_pos[7];
    
    // 각 그림의 위치 저장
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(board[i][j] == 0) continue;
            card_pos[board[i][j]].push_back({i, j});
        }
    }
    
    // 존재하는 카드의 종류 (순열 만들기 위한 배열)
    vector<int> cards;
    for(int i = 1; i <= 6; ++i)
        if(!card_pos[i].empty()) cards.push_back(i);
    
    int n = cards.size();   // 카드 종류 수
    
    // 카드 제거할 순서에 대한 순열에 따라 최소 조작수 구하기
    do{
        vector<vector<int>> myboard = board;
        int cnts[6][2];     // 각 카드 쌍을 제거하는 데 드는 최소 횟수
        cnts[0][0] = dist(myboard, {r, c}, card_pos[cards[0]][0]) 
                    + dist(myboard, card_pos[cards[0]][0], card_pos[cards[0]][1]);
        cnts[0][1] = dist(myboard, {r, c}, card_pos[cards[0]][1]) 
                    + dist(myboard, card_pos[cards[0]][1], card_pos[cards[0]][0]);
        myboard[card_pos[cards[0]][0].y][card_pos[cards[0]][0].x] = 0;
        myboard[card_pos[cards[0]][1].y][card_pos[cards[0]][1].x] = 0;
        
        // i번째 카드쌍을 제거할 때 0->1 순서로 고르는 경우와 1->0 순서로 고르는 경우 중 더 작은 값 구하기
        // 이전 카드쌍까지 제거한 최소 거리 + i번째 카드쌍의 0or1번 먼저 선택 후 짝 카드까지 이동하는 횟수
        for(int i = 1; i < n; ++i)
        {
            cnts[i][0] = min(cnts[i-1][0] + dist(myboard, card_pos[cards[i-1]][1], card_pos[cards[i]][0]), 
                             cnts[i-1][1] + dist(myboard, card_pos[cards[i-1]][0], card_pos[cards[i]][0])) 
                        + dist(myboard, card_pos[cards[i]][0], card_pos[cards[i]][1]);
            cnts[i][1] = min(cnts[i-1][0] + dist(myboard, card_pos[cards[i-1]][1], card_pos[cards[i]][1]), 
                             cnts[i-1][1] + dist(myboard, card_pos[cards[i-1]][0], card_pos[cards[i]][1])) 
                        + dist(myboard, card_pos[cards[i]][1], card_pos[cards[i]][0]);
            
            myboard[card_pos[cards[i]][0].y][card_pos[cards[i]][0].x] = 0;
            myboard[card_pos[cards[i]][1].y][card_pos[cards[i]][1].x] = 0;
        }
        answer = min({answer, cnts[n-1][0], cnts[n-1][1]});
    }while(next_permutation(cards.begin(), cards.end()));
    
    
    // 모든 카드를 제거하기 위한 키 조작 횟수의 최솟값 반환
    answer += (n * 2);  // 카드 뒤집는 횟수 더해주기
    return answer;
}