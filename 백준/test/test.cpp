#include <bits/stdc++.h>
#define INF 987654321
using namespace std;
vector<pair<int, int>> edge[20001];
int dst[20001];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	freopen("input.txt", "r", stdin);
	// ex) input 1 3 5 == 1 -> 3 으로 가는 간선이 5정도
	int v, e, s;
	cin >> v >> e >> s;
	for (int i = 0; i < e; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		edge[a].push_back({b, c});
	}
	fill(dst, dst + 20000, INF);
}