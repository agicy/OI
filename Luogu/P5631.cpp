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

const int MAXN=1e6+5;
const int MAXM=2e6+5;

struct Edge{
	int u,v,w;
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m;
int fa[MAXN],siz[MAXN];
Edge e[MAXM];

inline int find(reg int x){
	while(x!=fa[x])
		x=fa[x];
	return x;
}

inline int merge(reg int a,reg int b){
	reg int ra=find(a),rb=find(b);
	if(ra==rb)
		return 0;
	else if(siz[ra]>siz[rb]){
		fa[rb]=ra;
		siz[ra]+=siz[rb];
		return rb;
	}
	else{
		fa[ra]=rb;
		siz[rb]+=siz[ra];
		return ra;
	}
}

inline void del(reg int x){
	siz[fa[x]]-=siz[x];
	fa[x]=x;
	return;
}

int top,S[MAXM];

inline void solve(reg int l,reg int r,reg int ptr){
	if(l==r){
		if(siz[find(1)]==n){
			printf("%d\n",l);
			exit(0);
		}
		return;
	}
	reg int mid=(l+r)>>1;
	reg int tmp=ptr,tag=0;
	reg int las=top;
	while(e[ptr].w<=r&&ptr<=m){
		if(e[ptr].w>mid&&(tag=merge(e[ptr].u,e[ptr].v)))
			S[++top]=tag;
		++ptr;
	}
	solve(l,mid,tmp);
	while(top>las)
		del(S[top--]);
	ptr=tmp,tag=0;
	while(e[ptr].w<=mid&&ptr<=m){
		if((tag=merge(e[ptr].u,e[ptr].v)))
			S[++top]=tag;
		++ptr;
	}
	solve(mid+1,r,ptr);
	while(top>las)
		del(S[top--]);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		fa[i]=i,siz[i]=1;
	for(reg int i=1;i<=m;++i)
		e[i].u=read(),e[i].v=read(),e[i].w=read();
	sort(e+1,e+m+1);
	solve(0,e[m].w+1,1);
	return 0;
}