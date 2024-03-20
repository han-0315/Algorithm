/*
    시뮬레이션 문제
    각 단계마다, 정해진 규칙에 맞게 보드의 기사를 움직여야 함
    규칙은 연쇄적으로 작용하며, 한 명의 기사가 다른 기사를 밀어내면, 밀려난 위치에 있는 또 다른 기사도 밀려남
    여기서 모든 기사가 밀려나는 것이 가능해야, 즉 A->B->C라면, A,B,C 모두 밀려난 위치에 벽 혹은 보드 밖이 아니어야
    움직임이 가능함.
    -- 처음 틀린 이유 --
    여기서 나는 DFS 구조로 C가 가능하면 당연히 B,A도 가능할 거라 생각했으나



*/

#include <bits/stdc++.h>
#define ll long long
#define INF 987654321
#define SIZE 50
#define pii pair<int, int>
using namespace std;
int L, N, Q;
int board[SIZE][SIZE]; // 빈칸, 함정, 벽
int sboard[SIZE][SIZE];
int dx[4] = {0, 1, 0, -1}; // 상, 우, 하, 좌
int dy[4] = {-1, 0, 1, 0};
bool moved[SIZE];
queue<int> move_list;
struct sol
{
    int r;
    int c;
    int h;
    int w;
    int k;      // 현재 체력
    int demage; // 현재 받은 피해량
};

vector<struct sol> weapon;
void prt()
{
    for (int i = 1; i <= L; i++)
    {
        for (int j = 1; j <= L; j++)
        {
            cout << sboard[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void move(int idx, int dir)
{
    int cr = weapon[idx].r;
    int cc = weapon[idx].c;
    int ch = weapon[idx].h;
    int cw = weapon[idx].w;
    for (int i = 1; i <= L; i++)
        for (int j = 1; j <= L; j++)
        {
            if (sboard[i][j] == idx)
                sboard[i][j] = 0;
        }
    for (int r = cr; r < cr + ch; r++)
    {
        for (int c = cc; c < cc + cw; c++)
        {
            int nr = r + dy[dir];
            int nc = c + dx[dir];
            sboard[nr][nc] = idx;
        }
    }
    weapon[idx].r += dy[dir];
    weapon[idx].c += dx[dir];
}
void remove(int idx)
{
    for (int i = 1; i <= L; i++)
    {
        for (int j = 1; j <= L; j++)
        {
            if (sboard[i][j] == idx)
                sboard[i][j] = 0;
        }
    }
}
void demage(int idx)
{
    int cnt = 0;
    for (int i = 1; i <= L; i++)
    {
        for (int j = 1; j <= L; j++)
        {
            if (board[i][j] == 1 && sboard[i][j] == idx)
                cnt++;
        }
    }
    if (cnt >= weapon[idx].k)
    {
        weapon[idx].k = 0;
        remove(idx);
    }
    else
    {
        weapon[idx].k -= cnt;
        weapon[idx].demage += cnt;
    }
}

bool move_change(int idx, int dir)
{
    moved[idx] = true;
    bool flag = true;
    int cr = weapon[idx].r;
    int cc = weapon[idx].c;
    int ch = weapon[idx].h;
    int cw = weapon[idx].w;
    for (int r = cr; r < cr + ch; r++)
    {
        for (int c = cc; c < cc + cw; c++)
        {
            int nr = r + dy[dir];
            int nc = c + dx[dir];
            if (nr < 1 || nr > L || nc < 1 || nc > L || board[nr][nc] == 2)
            {
                return false;
            }
            else if (sboard[nr][nc] != idx && sboard[nr][nc] != 0)
            {
                if (moved[sboard[nr][nc]])
                    continue;
                flag = move_change(sboard[nr][nc], dir);
                if (!flag)
                    return false;
            }
        }
    }
    if (flag) // move
    {
        move_list.push(idx);
    }
    return true;
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    cin >> L >> N >> Q;
    weapon.resize(N + 1);

    for (int i = 1; i <= L; i++)
        for (int j = 1; j <= L; j++)
            cin >> board[i][j];

    // 기사 정보
    // (r,c) (h,w), k초기체력
    for (int i = 1, r, c, h, w, k; i <= N; i++)
    {
        cin >> r >> c >> h >> w >> k;
        struct sol cur = {r, c, h, w, k, 0};
        weapon[i] = cur;
        for (int a = r; a < r + h; a++)
        {
            for (int b = c; b < c + w; b++)
            {
                sboard[a][b] = i;
            }
        }
    }
    // 명령
    for (int i = 1; i <= Q; i++)
    {
        memset(moved, 0, sizeof(moved));
        while (!move_list.empty())
            move_list.pop();
        int num, dir;
        cin >> num >> dir; // num 번 기사에게 방향 d로 이동하라는 한칸 이동
        if (weapon[num].k <= 0)
            continue;

        if (move_change(num, dir))
        {
            while (!move_list.empty())
            {
                move(move_list.front(), dir);
                if (move_list.front() != num)
                    demage(move_list.front());
                move_list.pop();
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= N; i++)
    {
        if (weapon[i].k > 0)
            ans += weapon[i].demage;
    }
    cout << ans;
}
