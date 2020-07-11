#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 1e9
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXA=1000+5;
const int MAXB=1000+5;
const int MAXAB=1000+5;
const int MAXLOG2AB=10+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int a,b,n;
int M[MAXA][MAXB];

inline void Read(void){
	a=read(),b=read(),n=read();
	for(reg int i=1;i<=a;++i)
		for(reg int j=1;j<=b;++j)
			M[i][j]=read();
	return;
}

struct STList{
	int Max[MAXA][MAXB][MAXLOG2AB],Min[MAXA][MAXB][MAXLOG2AB];
	int log2[MAXAB];
	inline void Init(reg int a,reg int b,reg int M[MAXA][MAXB]){
		log2[0]=-1;
		for(reg int i=1;i<MAXAB;++i)
			log2[i]=log2[i>>1]+1;
		for(reg int i=1;i<=a;++i)
			for(reg int j=1;j<=b;++j)
				Max[i][j][0]=Min[i][j][0]=M[i][j];
		for(reg int k=1;k<MAXLOG2AB;++k)
			for(reg int i=1;i+(1<<k)-1<=a;++i)
				for(reg int j=1;j+(1<<k)-1<=b;++j){
					Max[i][j][k]=max(
						max(Max[i][j][k-1],Max[i+(1<<(k-1))][j+(1<<(k-1))][k-1]),
						max(Max[i+(1<<(k-1))][j][k-1],Max[i][j+(1<<(k-1))][k-1])
					);
					Min[i][j][k]=min(
						min(Min[i][j][k-1],Min[i+(1<<(k-1))][j+(1<<(k-1))][k-1]),
						min(Min[i+(1<<(k-1))][j][k-1],Min[i][j+(1<<(k-1))][k-1])
					);
				}
		return;
	}
	inline int QueryMax(reg int a,reg int b,reg int n){
		reg int k=log2[n];
		return max(
			max(Max[a][b][k],Max[a+n-(1<<k)][b+n-(1<<k)][k]),
			max(Max[a+n-(1<<k)][b][k],Max[a][b+n-(1<<k)][k])
		);
	}
	inline int QueryMin(reg int a,reg int b,reg int n){
		reg int k=log2[n];
		return min(
			min(Min[a][b][k],Min[a+n-(1<<k)][b+n-(1<<k)][k]),
			min(Min[a+n-(1<<k)][b][k],Min[a][b+n-(1<<k)][k])
		);
	}
};

STList ST;

inline void Work(void){
	ST.Init(a,b,M);
	int ans=INF;
	for(reg int i=1;i<=a-n+1;++i)
		for(reg int j=1;j<=b-n+1;++j)
			ans=min(ans,ST.QueryMax(i,j,n)-ST.QueryMin(i,j,n));
	printf("%d\n",ans);
	return;
}
