#include <bits/stdc++.h>
#define SIZE 100000
#define ll long long
#define pii pair<int, int>
using namespace std;
int n;
pii seg[SIZE * 2]; //(min, max)
//leaf node[i] -> i번째 선반의 DVD
void init(){
    for(int i = 0; i<n;i++){
        seg[i + n].first = seg[i + n].second = i;
    }
    for(int i = n-1; i>0; i--){
        seg[i].first = min(seg[i << 1].first, seg[i << 1 | 1].first);
        seg[i].second = max(seg[i << 1].second, seg[i << 1 | 1].second);
    }
}
bool query(int l, int r){ //[l , r)
    int p_l =l; int p_r = r;
    int low = n, high = 0;
    for(l+=n, r +=n; l!=r; l >>=1, r>>=1){
        if(l & 1){
            low = min(low, seg[l].first);
            high = max(high, seg[l++].second);
        }
        if(r & 1){
            low = min(low, seg[--r].first);
            high = max(high, seg[r].second);
        }
    }
    if(low == p_l && high == p_r - 1) return true;
    else return false;
}
void update(int i, int val){
    i += n;
    seg[i].first = seg[i].second = val;
    while(i >>= 1){
        seg[i].first = min(seg[i << 1].first, seg[i << 1 | 1].first);
        seg[i].second = max(seg[i << 1].second, seg[i << 1 | 1].second);
    }
}
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    //freopen("input.txt", "r", stdin);
    int t;
    cin >> t;
    while(t--){
        int k;
        cin >> n >> k;
        init();
        for(int a, b, c; k > 0; k--){
            cin >> a >> b >> c;
            if(a){
                string ans = query(b, c + 1) ? "YES" : "NO";
                cout << ans << '\n';
            }
            else{
                int temp = seg[n + b].first;
                update(b, seg[n + c].first);
                update(c, temp);
            }
        }

    }
    

    return 0;
}
