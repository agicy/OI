#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline void writeln(reg const char *s){
	while(*s)
		putchar(*s++);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

namespace Tree{
	int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int fa[MAXN],dep[MAXN],dis[MAXN];
	int siz[MAXN],son[MAXN];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dis[v]=dis[u]+w[i];
				dfs1(v,u);
				siz[u]+=siz[v];
				if(siz[son[u]]<siz[v])
					son[u]=v;
			}
		}
		return;
	}
	int top[MAXN];
	inline void dfs2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				dfs2(v,u,v);
		}
		return;
	}
	inline int LCA(reg int x,reg int y){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				x=fa[top[x]];
			else
				y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	inline int getDis(reg int x,reg int y){
		return dis[x]+dis[y]-(dis[LCA(x,y)]<<1);
	}
}

struct Heap{
	priority_queue<int> p,q;
	int siz;
	inline void pop(int x){
		--siz,q.push(x);
		return;
	}
	inline void push(int x){
		++siz,p.push(x);
		return;
	}
	inline int top(void){
		while(!q.empty()&&p.top()==q.top())
			p.pop(),q.pop();
		if(siz)
			return p.top();
		else
			return -inf;
	}
	inline int getVal(void){
		if(siz<2)
			return 0;
		else{
			reg int x=top();
			pop(x);
			reg int y=top();
			push(x);
			return max(x+y,0);
		}
	}
	inline void opt(reg int x,reg int col){
		if(col)
			pop(x);
		else
			push(x);
		return;
	}
};

namespace TreeDivide{
	bool del[MAXN];
	int rt,MaxPart,sum;
	int siz[MAXN];
	int top,S[MAXN];
	inline void getRt(reg int u,reg int father){
		siz[u]=1;
		S[++top]=u;
		reg int Max=0;
		for(reg int i=Tree::head[u];i;i=Tree::Next[i]){
			reg int v=Tree::to[i];
			if(v!=father&&!del[v]){
				getRt(v,u);
				siz[u]+=siz[v];
				Max=max(Max,siz[v]);
			}
		}
		Max=max(Max,sum-siz[u]);
		if(Max<MaxPart)
			rt=u,MaxPart=Max;
		return;
	}
	int fa[MAXN];
	Heap a[MAXN],b[MAXN],ans;
	inline int build(reg int u){
		del[u]=true;
		reg int p=fa[u];
		b[u].push(0);
		if(p)
			for(reg int i=1;i<=top;++i)
				a[u].push(Tree::getDis(p,S[i]));
		for(reg int i=Tree::head[u];i;i=Tree::Next[i]){
			reg int v=Tree::to[i];
			if(!del[v]){
				rt=0,MaxPart=inf,sum=siz[v],top=0;
				getRt(v,0);
				fa[rt]=u;
				reg int son=build(rt);
				b[u].push(a[son].top());
			}
		}
		ans.push(b[u].getVal());
		return u;
	}
	inline void update(reg int x,reg int col){
		reg int l1=b[x].getVal();
		b[x].opt(0,col);
		reg int l2=b[x].getVal();
		if(l1!=l2)
			ans.pop(l1),ans.push(l2);
		for(reg int u=x,p=fa[x];p;u=p,p=fa[p]){
			reg int s1=a[u].top();
			a[u].opt(Tree::getDis(p,x),col);
			reg int s2=a[u].top();
			if(s1!=s2){
				reg int l1=b[p].getVal();
				if(s1!=-inf)
					b[p].pop(s1);
				if(s2!=-inf)
					b[p].push(s2);
				reg int l2=b[p].getVal();
				if(l1!=l2)
					ans.pop(l1),ans.push(l2);
			}
		}
		return;
	}
}

int n;
int col[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b,c;
		a=read(),b=read(),c=read();
		Tree::Add_Edge(a,b,c),Tree::Add_Edge(b,a,c);
	}
	Tree::dfs1(1,0),Tree::dfs2(1,0,1);
	TreeDivide::rt=0,TreeDivide::MaxPart=inf,TreeDivide::sum=n,TreeDivide::top=0;
	TreeDivide::getRt(1,0),TreeDivide::build(TreeDivide::rt);
	reg int tot=n;
	reg int q=read();
	while(q--){
		static char opt;
		static int a;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'A':{
				switch(tot){
					case 0:{
						writeln("They have disappeared.");
						break;
					}
					case 1:{
						writeln(0);
						break;
					}
					default:{
						writeln(TreeDivide::ans.top());
						break;
					}
				}
				break;
			}
			case 'C':{
				a=read();
				tot+=col[a]?1:-1;
				col[a]^=1;
				TreeDivide::update(a,col[a]);
				break;
			}
		}
	}
	flush();
	return 0;
}