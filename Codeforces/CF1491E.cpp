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

const int MAXN=2e5+5;

struct Edge{
	int v;
	bool flag;
	inline Edge(reg int v=0,reg bool flag=false):v(v),flag(flag){
		return;
	}
};

int n;
vector<int> fib;
vector<Edge> G[MAXN];

inline void Add_Edge(reg int u,reg int v){
	G[u].push_back(Edge(v,false));
	return;
}

int siz[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	for(Edge e:G[u]){
		reg int v=e.v;
		if(!e.flag&&v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

inline bool find(reg int u,reg int father,reg int ptr,reg int &l,reg int &r,reg int &flag){
	for(Edge e:G[u]){
		reg int v=e.v;
		if(!e.flag&&v!=father){
			if(siz[v]==fib[ptr-1]||siz[v]==fib[ptr-2]){
				l=u,r=v;
				flag=(siz[v]==fib[ptr-1])?ptr-1:ptr-2;
				return true;
			}
			if(find(v,u,ptr,l,r,flag))
				return true;
		}
	}
	return false;
}

inline bool check(reg int u,reg int ptr){
	if(ptr<=1)
		return true;
	dfs(u,0);
	int l=0,r=0,flag;
	if(!find(u,0,ptr,l,r,flag))
		return false;
	for(Edge &e:G[l])
		if(e.v==r)
			e.flag=true;
	for(Edge &e:G[r])
		if(e.v==l)
			e.flag=true;
	return check(r,flag)&&check(l,flag^(ptr-1)^(ptr-2));
}

int main(void){
	n=read();
	fib.push_back(1),fib.push_back(1);
	for(reg int i=1;true;++i){
		if(fib[i]>=n)
			break;
		fib.push_back(fib[i]+fib[i-1]);
	}
	if(fib.back()!=n)
		puts("No");
	else{
		for(reg int i=1;i<n;++i){
			static int u,v;
			u=read(),v=read();
			Add_Edge(u,v),Add_Edge(v,u);
		}
		puts(check(1,fib.size()-1)?"Yes":"No");
	}
	return 0;
}