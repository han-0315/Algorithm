#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
int n, m, k;
priority_queue<int> board[21][21];
struct user
{
	int x, y;
	int dir;
	int s;
	int weapon;
	int point;
};
user users[31];

int user_map[21][21];
int lose_next_dir(int id)
{
	int next;
	for (int i = 0; i < 4; i++)
	{
		next = (users[id].dir + i) % 4;
		int nx = dx[next] + users[id].x;
		int ny = dy[next] + users[id].y;
		if (user_map[nx][ny] == 0 && nx > 0 && nx <= n && ny > 0 && ny <= n)
			break;
	}
	return next;
}
pair<bool, int> fight(int a_id, int b_id) // return <이긴사람(오른쪽이면 true), 포인트>
{
	if (users[a_id].weapon + users[a_id].s != users[b_id].weapon + users[b_id].s)
	{
		return make_pair(users[a_id].weapon + users[a_id].s < users[b_id].weapon + users[b_id].s, abs(users[a_id].weapon - users[b_id].weapon));
	}
	return make_pair(users[a_id].s < users[b_id].s, 0);
}
int next_dir(int id)
{
	int
}
void move(int id, bool lose)
{
	int dir = next_dir(id);
	int nx = dx[dir], ny = dy[dir];

	// 플레이어가 있을 때
	if (user_map[nx][ny] != 0)
	{
		int win_id, lose_id;
		pair<int, int> result = fight(user_map[nx][ny], id);
		if (result.first)
		{
			win_id = id;
			lose_id = user_map[nx][ny];
		}
		else
		{
			win_id = user_map[nx][ny];
			lose_id = id;
		}
		// ## 진 유저
		// ### 총 내려놓기
		if (users[lose_id].weapon != 0)
			board[nx][ny].push(users[lose_id].weapon);
		users[lose_id].weapon = 0;
		// ### 이동(move 함수 호출)
		move(lose_id, 1);
		// ## 이긴 유저
		// ### 포인트 획득
		users[win_id].point += result.second;
		// ### 총 획득
		if (!board[nx][ny].empty())
		{
			if (board[nx][ny].top() > users[win_id].weapon)
			{
				users[win_id].weapon = board[nx][ny].top();
				board[nx][ny].pop();
			}
		}
	}
	// 플레이어가 없을 때
	else
	{
		int gun = 0;
		if (!board[nx][ny].empty())
		{
			if (board[nx][ny].top() > users[id].weapon)
			{
				users[id].weapon = board[nx][ny].top();
				board[nx][ny].pop();
			}
		}
	}
}
int main()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0, t; j < n; j++)
		{
			cin >> t;
			board[i][i].emplace(t);
		}
	for (int i = 1; i <= m; i++)
	{
		cin >> users[i].x >> users[i].y >> users[i].dir >> users[i].s;
	}

	return 0;
}

// 다른 유저를 만났을 때
//