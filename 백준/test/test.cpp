#include <bits/stdc++.h>
#define INF 987654321
using namespace std;
vector<pair<int, int>> edge[20001]; // dst, cost
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
	priority_queue<pair<int, int>> pq; // -cost, start
	pq.push({0, s});
	dst[0] = 0;
	while (!pq.empty())
	{
		auto cur = pq.top();
		int cost = -cur.first;
		int node = cur.second;
		pq.pop();
		if (dst[node] < -cost)
			continue;
		for (pair<int, int> t : edge[cur.second])
		{
			int next = t.first;
			int next_cost = t.second;

			if (dst[next] > next_cost + dst[cur.second])
			{
				dst[next] = next_cost + dst[cur.second];
				pq.push({-(t.second + dst[cur.second]), next});
				pred[next] = pred[cur.second]
			}
		}
	}
	for (int i = 1; i <= v; i++)
	{
		dst[i] >= INF ? cout << "INF" : cout << dst[i];
		cout << '\n';
	}
}

