#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=250+5;
const int MAXM=250+5;
const int MAXLOG2N=8+1;
const int MAXLOG2M=8+1;

int a[MAXN][MAXM];

namespace ST{
	int Lg[MAXN];
	int Max[MAXN][MAXM][MAXLOG2N][MAXLOG2M];
	inline void Init(int n,int m){
		Lg[0]=-1;
		reg int S=max(n,m);
		for(reg int i=1;i<=S;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				Max[i][j][0][0]=a[i][j];
		for(reg int k=0;k<MAXLOG2N;++k)
			for(reg int l=0;l<MAXLOG2M;++l)
				if(!l&&!k)
					continue;
				else if(!l)
					for(reg int i=1;i+(1<<k)-1<=n;++i)
						for(reg int j=1;j+(1<<l)-1<=m;++j)
							Max[i][j][k][0]=max(Max[i][j][k-1][0],Max[i+(1<<(k-1))][j][k-1][0]);
				else
					for(reg int i=1;i+(1<<k)-1<=n;++i)
						for(reg int j=1;j+(1<<l)-1<=m;++j)
							Max[i][j][k][l]=max(Max[i][j][k][l-1],Max[i][j+(1<<(l-1))][k][l-1]);
		return;
	}
	inline int query(reg int x1,reg int y1,reg int x2,reg int y2){
		reg int k=Lg[x2-x1+1],l=Lg[y2-y1+1];
		return max(
			max(Max[x1][y1][k][l],Max[x2-(1<<k)+1][y1][k][l]),
			max(Max[x1][y2-(1<<l)+1][k][l],Max[x2-(1<<k)+1][y2-(1<<l)+1][k][l])
		);
	}
}

int n,m,K;

int main(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read();
	ST::Init(n,m);
	while(K--){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		printf("%d\n",ST::query(x1,y1,x2,y2));
	}
	return 0;
}