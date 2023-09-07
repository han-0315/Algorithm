#include <bits/stdc++.h>
#define SIZE 500000
#define ll long long 
#define pii pair<int, int>
using namespace std;


int seg[SIZE * 2];
vector<pii> vec;
int n;
int query(int l, int r){ //[l, r)
    int res = 0;
    for(l +=n, r += n; l != r; l >>= 1, r >>=1){
        if(l & 1) res += seg[l++];
        if(r & 1) res += seg[--r];
    }
    return res;
}
void update(int i, int val){
    seg[i += n] = val;
    while(i >>= 1){
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }
}
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    freopen("input.txt", "r", stdin);
    cin >> n;
    vec.resize(n);
    for(int i = 0; i<n;i++){
        cin >> vec[i].first;
        vec[i].second = i;
    }
    sort(vec.begin(), vec.end());
    ll res = 0;
    for(int i = 0; i<n;i++){
        int idx = vec[i].second;
        res += query(idx, n);
        update(idx, 1);
    }
    cout << res;
    return 0;
}
