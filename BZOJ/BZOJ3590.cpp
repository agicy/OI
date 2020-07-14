#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X0F0F0F0F
#define lowbit(x) ( (x) & ( - (x) ) )
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=12+1;
const int MAXM=40+5;

int n,m;
int f[1<<MAXN];
int g[1<<MAXN][MAXN][2];
int h[1<<MAXN][MAXN][MAXN];
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,c;
		x=read()-1,y=read()-1,c=read();
		Add_Edge(x,y,c);
		Add_Edge(y,x,c);
	}
	return;
}

inline void Init(void){
	cnt=0;
	memset(head,0,sizeof(head));
	return;
}

int Log[1<<MAXN];

inline void Work(void){
	memset(f,0X0F,sizeof(f));
	memset(g,0X0F,sizeof(g));
	memset(h,0X0F,sizeof(h));
	for(reg int i=0;i<n;++i){
		Log[1<<i]=i;
		f[1<<i]=0;
		h[1<<i][i][i]=0;
	}
	reg int U=(1<<n)-1;
	for(reg int S=1;S<=U;++S){
		reg int C=U^S;
		for(reg int sub=C;sub;sub-=lowbit(sub)){
			reg int id=Log[lowbit(sub)];
			for(reg int i=head[id];i;i=Next[i]){
				reg int v=to[i];
				if((S>>v)&1){
					if(w[i]<g[S][id][0]){
						g[S][id][1]=g[S][id][0];
						g[S][id][0]=w[i];
					}
					else if(w[i]<g[S][id][1]){
						g[S][id][1]=w[i];
					}
				}
			}
		}
	}
	for(reg int S=1;S<=U;++S)
		for(reg int t1=S;t1;t1-=lowbit(t1))
			for(reg int t2=S;t2;t2-=lowbit(t2)){
				reg int a=Log[lowbit(t1)],b=Log[lowbit(t2)];
				if(a==b)
					continue;
				for(reg int i=head[b];i;i=Next[i]){
					reg int v=to[i];
					if((S>>v)&1)
						h[S][a][b]=min(h[S][a][b],h[S^(1<<b)][a][v]+w[i]);
				}
			}
	for(reg int S=1;S<=U;++S){
		if(S==lowbit(S))
			continue;
		for(reg int sub=S&(S-1);sub;sub=S&(sub-1))
			for(reg int t1=sub;t1;t1-=lowbit(t1))
				for(reg int t2=sub;t2;t2-=lowbit(t2)){
					reg int a=Log[lowbit(t1)],b=Log[lowbit(t2)];
					if(a==b)
						f[S]=min(f[S],f[S^sub]+g[S^sub][a][0]+g[S^sub][a][1]+h[sub][a][b]);
					else
						f[S]=min(f[S],f[S^sub]+g[S^sub][a][0]+g[S^sub][b][0]+h[sub][a][b]);
				}
	}
	if(f[U]!=INF)
		printf("%d\n",f[U]);
	else
		puts("impossible");
	return;
}

int main(void){
	reg int C=read();
	while(C--){
		Init();
		Read();
		Work();
	}
	return 0;
}