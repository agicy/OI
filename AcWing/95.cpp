#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F

const int MAXN=5+5;

int n;
int a[MAXN][MAXN];
int temp[MAXN][MAXN];

int main(void){
	scanf("%d",&n);
	while(n--){
		reg int ans=INF;
		for(reg int i=1;i<=5;++i)
			for(reg int j=1;j<=5;++j){
				static char ch;
				cin>>ch;
				a[i][j]=(ch=='1');
			}
		for(reg int i=0;i<=(1<<5);++i){
			memcpy(temp,a,sizeof(a));
			reg int sum=0;
			for(reg int j=1;j<=5;++j)
				if(i>>(j-1)&1){
					++sum;
					temp[1][j-1]^=1;
					temp[1][j]^=1;
					temp[1][j+1]^=1;
					temp[2][j]^=1;
				}
			for(reg int j=1;j<=4;++j)
				for(reg int k=5;k>=1;--k)
					if(!temp[j][k]){
						++sum;
						temp[j][k]^=1;
						temp[j+1][k-1]^=1;
						temp[j+1][k]^=1;
						temp[j+1][k+1]^=1;
						temp[j+2][k]^=1;
					}
			reg bool flag=true;
			for(reg int j=1;j<=5;++j)
				for(reg int k=1;k<=5;++k)
					if(!temp[j][k]){
						flag=false;
						break;
					}
			if(flag)
				ans=min((int)ans,(int)sum);
		}
		printf("%d\n",ans>6?-1:ans);
	}
	return 0;
}
