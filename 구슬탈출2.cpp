/*
	-오답 이유
	 1) 구슬 R의 위치가 변동이 없으면 리턴해주었던 조건
	 2) 구슬 R과 구슬 B가 동시에 구멍으로 떨어진 경우 미처리
	 3) 문제 마지막의 '10번 이하로 움직여야 하는' 조건 빼먹음
	    => 따라서, 종료조건을 1)로 설정했다가 삽질
	-결론: 문제를 꼼꼼히 읽자
*/
#include <iostream>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
int ans = 99999999, N, M, rx, ry, bx, by;
char map[10][10];
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
void input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'R')
			{
				rx = i; ry = j; map[i][j] = '.';
			}
			else if (map[i][j] == 'B')
			{
				bx = i; by = j; map[i][j] = '.';
			}
		}
}
void go(int dir,int x1, int y1, int x2, int y2, bool r_first)
{
	while (1)
	{
		x1 += dx[dir]; y1 += dy[dir];
		if (map[x1][y1] == '#') 
		{
			x1 -= dx[dir]; y1 -= dy[dir]; break;
		}
		else if (map[x1][y1] == 'O') break;
	}
	while (1)
	{
		x2 += dx[dir]; y2 += dy[dir];
		if (map[x2][y2] == 'O') break;
		if (map[x2][y2] == '#' || (x1==x2 && y1==y2))
		{
			x2 -= dx[dir]; y2 -= dy[dir]; break;
		}
	}
	if (r_first)
	{
		rx = x1; ry = y1; bx = x2; by = y2;
	}
	else
	{
		rx = x2; ry = y2; bx = x1; by = y1;
	}
}
void move(int dir)
{
	int x1 = rx, y1 = ry, x2 = bx, y2 = by; bool r_first = true;
	if ((dir == 0 && y1 == y2 && x1>x2) || (dir == 1 && y1 == y2 && x1< x2) 
		|| (dir == 2 && x1 == x2 && y1> y2) || (dir == 3 && x1 == x2 && y1 < y2))
	{
		x2 = rx, y2 = ry, x1 = bx, y1 = by; r_first = false;
	} // 먼저 이동할 구슬 정해주기
	go(dir, x1, y1, x2, y2, r_first); // 이동
}
void solve(int cnt, int before_dir)
{
	// 종료조건
	if (cnt >= ans || cnt>10) return;
	if (map[bx][by] == 'O') return;
	else if (map[rx][ry] == 'O')
	{
		ans = min(ans, cnt); return;
	}
	int save_rx = rx, save_ry = ry, save_bx = bx, save_by = by;
	for (int dir = 0; dir < 4; dir++)
	{
		if ((before_dir == 0 && dir == 1) || (before_dir == 1 && dir == 0) 
			|| (before_dir == 2 && dir == 3) || (before_dir == 3 && dir == 2)) continue;
		move(dir);
		solve(cnt + 1, dir); // 유망하면 진행
		rx = save_rx; ry = save_ry; bx = save_bx; by = save_by; // 다음 갈래 수행 전 구슬 위치 되돌려주기
	}
}
int main()
{
	freopen("input.txt", "r", stdin);
	input();
	solve(0, -1);
	if (ans == 99999999) ans = -1;
	cout << ans << '\n';
	return 0;
}