#include <bits/stdc++.h>
using namespace std;
const int MAXN=22;
 
long long f[MAXN][4];
 
void prework(){
    f[0][0]=1;
    for(int i=1;i<=20;i++){
        f[i][3]=f[i-1][2]+10*f[i-1][3];
        f[i][2]=f[i-1][1];
        f[i][1]=f[i-1][0];
        f[i][0]=9*(f[i-1][0]+f[i-1][1]+f[i-1][2]); 
    }
}

int main()
{
	// 디버깅용
	freopen("input.txt", "r", stdin);
	int n, t;
	prework();
    cin>>t;
    while(t--){
        cin>>n;
        int len=3;
        while(f[len][3]<n) len++;
        int k=0;
        for(int i=len;i;i--){
            for(int j=0;j<=9;j++){
                long long cnt=f[i-1][3];
				// 현재까지 6의 개수를 확인 K는 현재까지 연속된 6의 개수
				// 만약 앞이 6이라면, 종말의 수를 더하는 것은 f[i-1][2] 만 하면된다. 
				// k(연속된 6의 개수)가 2라면, j도 6이라면 뒤에 어떤 수가 와도 되니 f[i-1][0~3]를 더한다. f[i-1][3]은 위에 카운트의 초기값이기에, 아래에서는 더하지 않음
				// 즉 k + j의 개수가 3이라면 f[i-1][0~3], 2라면 f[i-1][1~3], 1이라면 f[i-1][2~3] 0이라면 f[i-1][3]만 더하는 것이다.
                if(j==6||k==3){
                    for(int l=max(3-k-(j==6),0);l<3;l++){
                        cnt+=f[i-1][l];
                    }
                }
                if(cnt<n) n-=cnt;
                else{
                    if(k<3){
                        if(j==6) k++;
                        else k=0;
                    }
                    cout<<j;
                    break;
                }
            }
        }
        cout<<endl;
 
    }
    return 0;
}