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

const int MAXN=300+5;

int n,d1,d2;
int col[2][MAXN<<1][MAXN<<1],cnt[2][2];

inline void solve(reg int d,reg int id){
	reg int k=0;
	while(!(d&3))
		d>>=2,++k;
	if((d&3)==3)
		return;
	if((d&3)==1)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				col[id][i][j]=(((i-1)>>k)+((j-1)>>k))&1;
	else
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				col[id][i][j]=((i-1)>>k)&1;
	return;
}

int main(void){
	n=(read()<<1),d1=read(),d2=read();
	solve(d1,0),solve(d2,1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			++cnt[col[0][i][j]][col[1][i][j]];
	reg int x=-1,y=-1;
	for(reg int i=0;i<2;++i)
		for(reg int j=0;j<2;++j)
			if(cnt[i][j]>=((n*n)>>2))
				x=i,y=j;
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(col[0][i][j]==x&&col[1][i][j]==y){
				printf("%d %d\n",i-1,j-1);
				tot+=1;
				if(tot>=((n*n)>>2))
					return 0;
			}
	return 0;
}