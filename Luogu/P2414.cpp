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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXM=1e5+5;
const int MAXS=1e5+5;

namespace Tree{
	const int MAXV=MAXS;
	const int MAXE=MAXS;
	int cnt,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int tim,dfn[MAXV];
	int lef[MAXV],rig[MAXV];
	inline void dfs(reg int u){
		lef[u]=dfn[u]=++tim;
		for(reg int i=head[u];i;i=Next[i])
			dfs(to[i]);
		rig[u]=tim;
		return;
	}
}

namespace AC{
	struct node{
		int ch[26],fail;
		int fa;
		vector<int> tag;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define fa(x) unit[(x)].fa
		#define tag(x) unit[(x)].tag
	};
	int tot;
	node unit[MAXS];
	int cnt;
	inline void insert(reg char str[]){
		reg int len=strlen(str);
		reg int p=0;
		for(reg int i=0;i<len;++i)
			switch(str[i]){
				case 'P':{
					tag(p).push_back(++cnt);
					break;
				}
				case 'B':{
					p=fa(p);
					break;
				}
				default:{
					reg int c=str[i]-'a';
					if(!ch(p)[c])
						ch(p)[c]=++tot;
					fa(ch(p)[c])=p;
					p=ch(p)[c];
					break;
				}
			}
		return;
	}
	int tim,dfn[MAXS],rnk[MAXS];
	int lca,lef[MAXS],rig[MAXS];
	inline void dfs(reg int u){
		for(reg int i=0,siz=tag(u).size();i<siz;++i){
			reg int v=tag(u)[i];
			rnk[++tim]=v;
			dfn[v]=tim;
			rig[v]=u;
			lef[tim]=lca;
			lca=u;
		}
		for(reg int i=0;i<26;++i)
			if(ch(u)[i]){
				dfs(ch(u)[i]);
				lca=u;
			}
		return;
	}
	inline void build(void){
		queue<int> Q;
		for(reg int i=0;i<26;++i)
			if(ch(0)[i])
				Q.push(ch(0)[i]);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<26;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		for(reg int i=1;i<=tot;++i)
			Tree::Add_Edge(fail(i),i);
		return;
	}
}

struct querys{
	int id,x,y;
	inline void Read(reg int i){
		id=i,x=read(),y=read();
		return;
	}
	inline bool operator<(const querys& a)const{
		return AC::dfn[y]<AC::dfn[a.y];
	}
};

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXS];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
}

char s[MAXS];
querys q[MAXM];
int ans[MAXM];

int main(void){
	read(s);
	AC::insert(s),AC::dfs(0),AC::build(),Tree::dfs(0),BIT::Init(AC::tot+1);
	reg int m=read();
	for(reg int i=1;i<=m;++i)
		q[i].Read(i);
	sort(q+1,q+m+1);
	reg int p=0;
	for(reg int i=1,ptr=1;i<=AC::cnt;++i){
		reg int u=AC::rnk[i];
		reg int tmp=AC::rig[u];
		while(p!=AC::lef[i]){
			BIT::update(Tree::dfn[p],-1);
			p=AC::fa(p);
		}
		while(tmp!=p){
			BIT::update(Tree::dfn[tmp],1);
			tmp=AC::fa(tmp);
		}
		p=AC::rig[u];
		while(q[ptr].y==u){
			reg int id=AC::rig[q[ptr].x];
			ans[q[ptr].id]=BIT::query(Tree::lef[id],Tree::rig[id]);
			++ptr;
		}
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}