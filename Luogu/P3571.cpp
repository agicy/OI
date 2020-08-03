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

const int MAXN=1e6+5;

int n,m;
int k[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int Maxdep;
int T[MAXN];
int sum[MAXN];

inline void DFS(reg int u,int dep){
	++T[dep];
	Maxdep=max(Maxdep,dep);
	for(reg int i=head[u];i;i=Next[i])
		DFS(to[i],dep+1);
	return;
}

int f[MAXN];

inline int Calc(reg int i,reg int k){
	return i*k+sum[i];
}

int Q[MAXN];
int x[MAXN],y[MAXN];

inline bool slope(reg int p1,reg int p2,reg int p3){
	return (y[p3]-y[p1])*(x[p2]-x[p1])-(y[p2]-y[p1])*(x[p3]-x[p1])>=0;
}

int main(void){
	n=read(),m=read();
	int Maxk=0;
	for(reg int i=1;i<=m;++i){
		k[i]=read();
		Maxk=max(Maxk,k[i]);
	}
	for(reg int i=2;i<=n;++i){
		static int x;
		x=read();
		Add_Edge(x,i);
	}
	DFS(1,1);
	for(reg int i=Maxdep;i>=1;--i)
		sum[i]=sum[i+1]+T[i+1];
	for(reg int i=1;i<=Maxdep;++i)
		x[i]=i,y[i]=sum[i];
	reg int head=0,tail=0;
	for(reg int i=1;i<=Maxdep;++i){
		while(head<tail&&slope(Q[tail-1],Q[tail],i))
			--tail;
		Q[++tail]=i;
	}
	for(reg int i=1;i<=Maxk;++i){
		while(head<tail&&Calc(Q[head],i)<=Calc(Q[head+1],i))
			++head;
		f[i]=Q[head]+(sum[Q[head]]+i-1)/i;
	}
	for(reg int i=1;i<=m;++i)
		printf("%d%c",f[k[i]],i==m?'\n':' ');
	return 0;
}