#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXN=300+5;
const int MAXM=(MAXN*(MAXN-1))>>1;

struct Graph{
	int M[MAXN][MAXN];
	inline void Init(reg int n){
		reg int i;
		memset(M,0X3F,sizeof(M));
		for(i=1;i<=n;++i)
			M[i][i]=0;
		return;
	}
	inline void Floyd(reg int n){
		reg int i,j,k;
		for(k=1;k<=n;++k)
			for(i=1;i<=n;++i)
				if(i!=k)
					for(j=i+1;j<=n;++j)
						if(j!=k)
							M[i][j]=M[j][i]=min(M[i][j],M[i][k]+M[k][j]);
		return;
	}
};

int n,m,l,Q;
Graph G1,G2;

int main(void){
	reg int i,j;
	n=read(),m=read(),l=read();
	G1.Init(n);
	for(i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		G1.M[a][b]=G1.M[b][a]=c;
	}
	G1.Floyd(n);
	G2.Init(n);
	for(i=1;i<=n;++i)
		for(j=i+1;j<=n;++j)
			if(G1.M[i][j]<=l)
				G2.M[i][j]=G2.M[j][i]=1;
	G2.Floyd(n);
	Q=read();
	while(Q--){
		static int s,t;
		s=read(),t=read();
		printf("%d\n",G2.M[s][t]==INF?-1:G2.M[s][t]-1);
	}
	return 0;
}
