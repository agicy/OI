#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m;
unordered_map<int,int> M[MAXN];
map<pair<int,int>,int> Ans;

namespace UnionFind{
	int fa[MAXM<<1];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int main(void){
	n=read(),m=read();
	UnionFind::Init(m<<1);
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		if(!M[a][c])
			M[a][c]=++tot;
		if(!M[b][c])
			M[b][c]=++tot;
		UnionFind::merge(M[a][c],M[b][c]);
	}
	reg int q=read();
	while(q--){
		static int u,v;
		static pair<int,int> p;
		u=read(),v=read();
		if(u<=v)
			p=make_pair(u,v);
		else
			p=make_pair(v,u);
		map<pair<int,int>,int>::iterator it=Ans.find(p);
		if(it!=Ans.end())
			writeln(it->second);
		else{
			reg int a=M[u].size()<M[v].size()?u:v,b=u^v^a;
			reg int ans=0;
			for(unordered_map<int,int>::iterator it=M[a].begin();it!=M[a].end();++it){
				unordered_map<int,int>::iterator tmp=M[b].find(it->first);
				if(tmp!=M[b].end()&&UnionFind::search(it->second,tmp->second))
					++ans;
			}
			Ans[p]=ans;
			writeln(ans);
		}
	}
	flush();
	return 0;
}