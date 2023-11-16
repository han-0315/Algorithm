- 문제설명
    
    만약, 극악의 케이스가 들어온다면
    
    `0, 0, [0, 0, 150, 1, 1], [150, 150, 1, 1, 2]`  테스트 케이스에 만족하는 DP 인덱스를 늘리려면, DP의 사이즈는 `150*150 = **22500`을 만족해야 한다.** (물론, 위와 같은 테스트케이스는 기존의 방식으로도 해결할 수 있다. 단순히 코딩력을 149 올린 뒤 1번 문제를 푼것과 cost는 동일하니)
    
    하지만 [0,0,150,2,1] 인 경우에는 기존의 방식으로 해결이 불가능하다.
    
    그러므로 이 문제는 다익스트라로 푸는 것이 옳은 것 같다. 
    

---
DP로 푼다면, (바킹독님 풀이)아래와 같으나 25번 테스트케이스에서 시간초과가 난다.
```cpp
#include <bits/stdc++.h>
using namespace std;

// d[i][j] : 알고력 i, 코딩력 j를 달성하기 위한 시간

int d[505][505];

const int MX = 0x7f7f7f7f;

int solution(int alp, int cop, vector<vector<int>> problems) {
    for(int i = 0; i <= 502; i++) fill(d[i], d[i]+503, MX);
    d[alp][cop] = 0;
    int mxalp = -1, mxcop = -1;
    for(auto& problem : problems){
        mxalp = max(mxalp, problem[0]);
        mxcop = max(mxcop, problem[1]);
    }
    //cout << mxalp << ' ' << mxcop << '\n';
    int ans = MX;
    for(int i = alp; i <= 500; i++){
        for(int j = cop; j <= 500; j++){
            if(i >= mxalp && j >= mxcop) continue;
            // d[i][j]에는 이미 제대로된 값이 들어가있음
            d[i+1][j] = min(d[i+1][j], d[i][j]+1);
            d[i][j+1] = min(d[i][j+1], d[i][j]+1);
            for(auto& problem : problems){
                int alp_req, cop_req, alp_rwd, cop_rwd, cost;
                alp_req = problem[0];
                cop_req = problem[1];
                alp_rwd = problem[2];
                cop_rwd = problem[3];
                cost = problem[4];
                if(alp_req > i || cop_req > j) continue;
                int alp_nxt = i + alp_rwd;
                int cop_nxt = j + cop_rwd;
                if(alp_nxt >= mxalp && cop_nxt >= mxcop){
                    ans = min(ans, d[i][j] + cost);
                    continue;
                }
                if(alp_nxt > 500 || cop_nxt > 500) continue;
                d[alp_nxt][cop_nxt] = min(d[alp_nxt][cop_nxt], cost + d[i][j]);                
            }
        }
    }
    for(int i = mxalp; i <= 500; i++){
        for(int j = mxcop; j <= 500; j++){
            ans = min(ans, d[i][j]);
        }
    }

//     cout << d[80][0] << '\n';
//     cout << d[80][10] << '\n';

    return ans;
}
```

다익스트라 소스코드    
```cpp
#include <string>
#include <vector>
#include <queue>

#define INF 0x7fffffff

struct Entry {
    Entry(int _alp = 0, int _cop = 0, int _time = 0) : alp(_alp), cop(_cop), time(_time) {}
    int alp;
    int cop;
    int time;
};

bool operator>(const Entry &lhs, const Entry &rhs) {
    return lhs.time > rhs.time;
}

inline int max(int a, int b) {
    return a < b ? b : a;
}
inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int relu(int a) {
    return a > 0 ? a : 0;
}

int min_time[151][151];

int solution(int alp, int cop, std::vector<std::vector<int>> problems) {
    int answer;
    int max_alp = 0;
    int max_cop = 0;
        
        // 최댓값으로 DP 배열 초기화
    for (int i = 0; i <= 150; ++i) {
        for (int j = 0; j <= 150; ++j) {
            min_time[i][j] = INF;
        }
    }

    // figure out max alp/cop
    for (const auto &p : problems) {
        max_alp = max(max_alp, p[0]);
        max_cop = max(max_cop, p[1]);
    }

    // Min-Heap w.r.t time
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> PQ;
    PQ.emplace(alp, cop, 0);
    min_time[alp][cop] = 0;

    while (!PQ.empty()) {
        auto curr = PQ.top();
        PQ.pop();

        // Check if minimum time for this status
                // 불필요한 연산 제거(DP에 저장된 시간보다 더 큰 시간일 경우
        if (curr.time > min_time[curr.alp][curr.cop]) {
            continue;
        }
                
        // 문제를 풀었는지 확인
        if (curr.alp >= max_alp && curr.cop >= max_cop) {
            answer = curr.time;
            break;
        }

        // Try to solve problems
        for (const auto &p : problems) {
            // 스킬 1: 상한선을 정해줌(150이하로, why? 배열의 크기 150 & 정답(알고력, 코딩력)의 최댓값도 150이하
            int nalp = min(150, curr.alp + p[2]);
            int ncop = min(150, curr.cop + p[3]);
            int ntime = curr.time + p[4];
            // can solve this problem
            if (curr.alp >= p[0] && curr.cop >= p[1] &&
                ntime < min_time[nalp][ncop]) {
                min_time[nalp][ncop] = ntime;
                PQ.emplace(nalp, ncop, ntime);
                continue;
            }
            // 스킬 2: 만약, 문제를 풀지못할때, 해당 문제를 풀 수 있는 알고, 코딩력을 가지는 시간을 계산하여 
            // 집어넣음 -> 시간줄이기 아래의 코드랑 비교됨
            // d[i+1][j] = min(d[i+1][j], d[i][j]+1);
            // d[i][j+1] = min(d[i][j+1], d[i][j]+1);
            // ======
            nalp = max(p[0], curr.alp);
            ncop = max(p[1], curr.cop);
            ntime = curr.time + relu(p[0] - curr.alp) + relu(p[1] - curr.cop);
            if (ntime < min_time[nalp][ncop]) {
                min_time[nalp][ncop] = ntime;
                PQ.emplace(nalp, ncop, ntime);
            }
        }
    }        

    return answer;
}
```