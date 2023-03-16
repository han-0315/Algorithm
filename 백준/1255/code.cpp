#include <bits/stdc++.h>
using namespace std;
#define MAX 1 << 20
stack<int> s;//위치
int seg[MAX];
int n_size = 1;
void update(int i, int val){
    seg[i += n_size] = val;
    while(i >>= 1){
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }
}
int query(size_t l, size_t r) //[l, r]
{
	int result = 0;
	for (l += n_size, r += n_size; l != r; l >>= 1, r >>= 1) {
		if (l & 1) result += seg[l++];
		if (r & 1) result += seg[--r];
	}
	return result;
}
//k가 현재위치
string solution(int n, int k, vector<string> cmd) {
    for(;n_size < n;n_size <<= 1);
    n_size >>= 1;
    //segment 세팅 끝
    //[0, n)
    int cur = k;
    for(string i : cmd){
        if(i[0] == 'D'){
            int plus = query(i[2] - '0', cur);
            cur -= (plus + i[2]);
        }
        else if(i[0] == 'U'){
            int plus = query(cur, i[2] - '0');
            cur += (plus + i[2]);
        }
        else if(i[0] == 'C'){ //삭제
            s.push(cur);
            update(cur, 1);
            //마지막이 아니면 ++
            for(;seg[n_size + (++cur)] != 0 && cur < n;);
            cur = cur == n-1 && seg[n_size + n-1] == 1 ? cur - 1 : cur;
        }
        else{
            update(s.top(), 0);
            s.pop();
        }
    }


    string answer = "";
    return answer;
}

int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    //freopen("input.txt", "r", stdin);
    cout << "123";
    return 0;
}
