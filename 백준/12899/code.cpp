#include <bits/stdc++.h>
#define SIZE 2000000
#define ll long long
#define pii pair<int, int>
using namespace std;
int seg[SIZE * 2];
int query(int l, int r){ //[l, r)
    int res = 0;
    for(l +=SIZE, r+=SIZE; l!=r; l>>=1, r>>=1){
        if(l & 1) res += seg[l++];
        if(r & 1) res += seg[--r];
    }
    return res;
}
void update(int i, int val){//leaf 0 ~ n-1 -> 해당 원소에 ++
    seg[i += SIZE]+=val;
    while(i >>= 1){
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }
}
int find_xnum(int x){
    int l = 0; int r = SIZE-1;
    while(l < r){
        int m = (l + r)/2;
        query(0, m + 1) >= x ? r = m: l = m + 1;
    }
    return l;
}
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    //디버깅용
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    while(n--){
        int a,b;
        cin >> a >> b;
        if(a == 1){
            update(b-1, 1);
        }
        else{
            int rt = find_xnum(b) + 1;
            update(rt - 1, -1);
            cout << rt << '\n';
        }
    }
    return 0;
}
