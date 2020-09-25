#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
#define reg register
#define INF 0X3F3F3F3F

const int MAXN=12+1;
const int MAXM=1000+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
int road[1<<12][MAXN],f[1<<12][MAXN];
int ans=INF;

inline void Add_Edge(reg int,reg int,reg int);
inline void Read_and_Init(void);
inline void DP(void);
inline void Print(void);

int main(void){
	Read_and_Init();
	DP();
	Print();
	return 0;
}
inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read_and_Init(void){
	reg int i,j,k;
	scanf("%d%d",&n,&m);
	memset(f,0X3F,sizeof(f));
	memset(road,0X3F,sizeof(road));
	for(i=1;i<=n;++i)
		f[1<<(i-1)][1]=0;
	for(i=1;i<=m;++i){
		static int a,b,v;
		scanf("%d%d%d",&a,&b,&v);
		Add_Edge(a,b,v);
		Add_Edge(b,a,v);
	}
	for(i=1;i<(1<<n);++i)
		for(j=1;j<=n;++j)
			for(k=head[j];k;k=Next[k])
				if(i&(1<<(to[k]-1)))
					road[i][j]=min(road[i][j],w[k]);
	return;
}

inline void DP(void){
	reg bool flag;
	reg int i,j,k,S,now,temp;
	for(i=1;i<(1<<n);++i)
		for(j=2;j<=n;++j)
			for(S=(i-1)&i;S;S=(S-1)&i){
				if(f[S][j-1]==INF)
					continue;
				now=i^S,temp=0,flag=true;
				for(k=1;k<=n;++k)
					if(now&(1<<(k-1))){
						if(road[S][k]!=INF)
							temp+=road[S][k];
						else{
							flag=false;
							break;
						}
					}
				if(flag)
					f[i][j]=min(f[i][j],f[S][j-1]+temp*(j-1));
			}
	return;
}

inline void Print(void){
	reg int i;
	for(i=1;i<=n;++i)
		ans=min(ans,f[(1<<n)-1][i]);
	printf("%d\n",ans);
	return;
}