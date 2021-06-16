#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;

int n;
int u[MAXN],v[MAXN];
char col[MAXN];
int deg[MAXN];
vector<int> G[MAXN];
bool del[MAXN];
int val[MAXN];
int f[MAXN];
int ecnt,vcnt,dia;

inline int dfs(reg int u,reg int father){
	reg int Max=val[u];
	for(int v:G[u])
		if(v!=father){
			reg int tmp=dfs(v,u);
			dia=max(dia,Max+tmp);
			Max=max(Max,tmp+val[u]);
		}
	return Max;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read();
		++deg[u[i]],++deg[v[i]];
		G[u[i]].push_back(v[i]),G[v[i]].push_back(u[i]);
	}
	read(col+1);
	queue<int> Q;
	for(int i=1;i<=n;++i)
		if(deg[i]==1&&col[i]=='B')
			Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		del[u]=true;
		for(int v:G[u]){
			--deg[v];
			if(deg[v]==1&&col[v]=='B')
				Q.push(v);
		}
	}
	for(reg int i=1;i<=n;++i)
		deg[i]=0,G[i].clear();
	for(reg int i=1;i<n;++i)
		if(!del[u[i]]&&!del[v[i]]){
			++ecnt;
			++deg[u[i]],++deg[v[i]];
			G[u[i]].push_back(v[i]),G[v[i]].push_back(u[i]);
		}
	reg int rt=-1;
	for(reg int i=1;i<=n;++i)
		if(!del[i]){
			rt=i;
			if(((deg[i]&1)&&col[i]=='B')||((!(deg[i]&1))&&col[i]=='W')){
				val[i]=2;
				++vcnt;
			}
		}
	if(rt==-1)
		puts("0");
	else{
		dfs(rt,0);
		printf("%d\n",(ecnt<<1)+vcnt-dia);
	}
	return 0;
}