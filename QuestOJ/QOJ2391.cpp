#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e3+5;

int n,k;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
bool flag;

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	reg int cnt=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]==1)
				++cnt;
		}
	}
	if(cnt>=2)
		flag=true;
	return;
}

inline void dfs2(reg int u,reg int father){
	siz[u]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs2(v,u);
			if(siz[v]==2){
				--k;
				siz[v]=0;
			}
			siz[u]+=siz[v];
		}
	}
	if(siz[u]>2)
		flag=true;
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	if(n&1)
		puts("Alan");
	else if(n==2)
		puts("Bob");
	else{
		dfs1(1,0);
		if(flag)
			puts("Alan");
		else{
			dfs2(1,0);
			if(flag||k<0||siz[1]!=2)
				puts("Alan");
			else
				puts("Bob");
		}
	}
	return 0;
}