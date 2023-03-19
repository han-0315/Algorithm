#include <bits/stdc++.h>
#define SIZE 1000000
#define ll long long
#define pii pair<int, int>
using namespace std;
int n;
int bound=1;
ll segtree[SIZE * 4];
// query: idx에 포함되는 범위에 대한 합을 모두 가져와야함
ll query(int idx){ 
    ll sum = 0;
    for(int i = idx + bound; i>0; i>>=1) 
        sum += segtree[i];
    return sum;
}
//update : 범위에 가장 적합한 위치에 합을 추가.
void update(int cur, int s, int e, int l, int r, int val){
    
    if(l > r || s > e || r < s || l > e) return;
    
    if(l == s && e == r){  
        segtree[cur] += val;
        return;
    }
    int m = (s + e) / 2;
    if(s <= l && r <= e){
        if(m < l) update(cur << 1 | 1, m + 1, e, l, r, val);    
        else if(m > r) update(cur << 1, s, m, l, r, val);
        else{ // l <= m <= r
            update(cur << 1, s, m, l, m, val);
            update(cur << 1 | 1, m + 1, e, m + 1, r, val);    
        }    
    }
}
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    //freopen("input.txt", "r", stdin);
    cin >> n;
    while((bound <<= 1) < n);
    for(int i = 0; i<n;i++) cin >> segtree[bound+i];
    int m;
    cin >> m;
    for(int a,b,c,v; m > 0; m--){
        cin >> a;
        if(a == 1){
            cin >> b >> c >> v;
            update(1, 1, bound,b,c,v );
        }
        else{
            cin >> v;
            cout << query(v - 1) << '\n';
        }
    }

    return 0;
}
