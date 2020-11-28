#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXM=15;
const int MAXN=15;

int m,n;
int a[MAXM][MAXN];
int tmp[MAXM][MAXN];

inline void change(reg int x,reg int y){
	tmp[x][y]^=1;
	if(x)tmp[x-1][y]^=1;
	if(x+1<m)tmp[x+1][y]^=1;
	if(y)tmp[x][y-1]^=1;
	if(y+1<n)tmp[x][y+1]^=1;
	return;
}

int op[MAXM];
int ans,Ans[MAXM];

int main(void){
	m=read(),n=read();
	for(reg int i=0;i<m;++i)
		for(reg int j=0;j<n;++j)
			a[i][j]=read();
	ans=n*m+1;
	reg int U=(1<<n)-1;
	for(reg int S=0;S<=U;++S){
		reg int cnt=0;
		memcpy(tmp,a,sizeof(a));
		for(reg int i=0;i<n;++i)
			if((S>>(n-i-1))&1){
				++cnt;
				change(0,i);
			}
		op[0]=0;
		for(reg int i=0;i<n;++i)
			if((S>>(n-i-1))&1)
				op[0]|=(1<<i);
		for(reg int i=1;i<m;++i){
			op[i]=0;
			for(reg int j=0;j<n;++j)
				if(tmp[i-1][j]){
					++cnt;
					op[i]|=(1<<j);
					change(i,j);
				}
		}
		reg bool f=true;
		for(reg int i=0;i<n;++i)
			if(tmp[m-1][i]){
				f=false;
				break;
			}
		if(f){
			if(cnt<ans){
				ans=cnt;
				memcpy(Ans,op,sizeof(op));
			}
		}
	}
	if(ans==n*m+1)
		puts("IMPOSSIBLE");
	else{
		for(reg int i=0;i<m;++i,putchar('\n'))
			for(reg int j=0;j<n;++j)
				putchar('0'+((Ans[i]>>j)&1)),putchar(' ');
	}
	return 0;
}