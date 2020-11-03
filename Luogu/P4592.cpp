#include<bits/stdc++.h>
//using namespace std;
#define reg register
typedef long long ll;

namespace Quick{
	class InStream{
	private:
		char buf[1<<21],*p1,*p2;
		inline char getc(void){
			return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
		}
		template<class Type> inline void read(Type &x){
			char c=getc();
			while(!isdigit(c))c=getc();
			for(x=0;isdigit(c);c=getc())x=(x<<1)+(x<<3)+(c^48);
			return;
		}
	public:
		InStream() {p1=p2=buf;}
		~InStream() {}
		template<class Type> InStream& operator>>(Type &&x){
			read(x);
			return *this;
		}
	}cin;
	class OutStream {
	private:
		char buf[1<<21];int p1;const int p2=1<<21;
		inline void flush(void){
			fwrite(buf,1,p1,stdout);
			p1=0;
			return;
		}
		inline void putc(const char &c){
			if(p1==p2)
				flush();
			buf[p1++]=c;
			return;
		}
		template<class Type> inline void write(reg Type x){
			static char buf[25];
			reg int p=-1;
			if(x==0)
				putc('0');
			else
				for(;x;x/=10)
					buf[++p]=x%10+48;
			while(~p)
				putc(buf[p--]);
		}
	public:
		OutStream(){p1=0;}
		~OutStream(){flush();}
		template<class Type> OutStream& operator<<(const Type &x){
			write(x);
			return *this;
		}
	}cout;
	const char endl('\n');
}

using namespace Quick;

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

inline void swap(reg int &a,reg int &b){
	a=a^b,b^=a,a^=b;
	return;
}

const int MAXN=1e5+5;
const int MAXLOG2V=30;

int n,q;
int v[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])
				son[u]=v;
		}
	}
	return;
}

namespace Trie{
	const int MAXSIZE=40*MAXN;
	struct Node{
		int ch[2],sum;
		#define ch(x) unit[(x)].ch
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline int Init(void){
		return tot=1;
	}
	inline void update(reg int rt,reg int pre,reg int val){
		for(reg int i=MAXLOG2V-1;i>=0;--i){
			reg int c=(val>>i)&1;
			ch(rt)[c]=++tot,ch(rt)[!c]=ch(pre)[!c];
			rt=ch(rt)[c],pre=ch(pre)[c];
			sum(rt)=sum(pre)+1;
		}
		return;
	}
	inline int query(reg int k,reg int pre,reg int val){
		reg int res=0;
		for(reg int i=MAXLOG2V-1;i>=0;--i){
			res<<=1;
			reg int c=(val>>i)&1;
			if(sum(ch(k)[!c])-sum(ch(pre)[!c])>0){
				res|=1;
				k=ch(k)[!c],pre=ch(pre)[!c];
			}
			else
				k=ch(k)[c],pre=ch(pre)[c];
		}
		return res;
	}
}

int root[MAXN];
int tim,dfn[MAXN];
int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
	top[u]=topf;
	dfn[u]=++tim;
	root[dfn[u]]=++Trie::tot;
	Trie::update(root[dfn[u]],root[dfn[u]-1],v[u]);
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

inline int query(int x,int y,reg int z){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		cMax(res,Trie::query(root[dfn[y]],root[dfn[top[y]]-1],z));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	cMax(res,Trie::query(root[dfn[y]],root[dfn[x]-1],z));
	return res;
}

int main(void){
	cin>>n>>q;
	for(reg int i=1;i<=n;++i)
		cin>>v[i];
	for(reg int i=1;i<n;++i){
		static int u,v;
		cin>>u>>v;
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs1(1,0);
	root[0]=Trie::Init();
	dfs2(1,0,1);
	while(q--){
		static int op,x,y,z;
		cin>>op;
		switch(op){
			case 1:{
				cin>>x>>z;
				printf("%d\n",Trie::query(root[dfn[x]+siz[x]-1],root[dfn[x]-1],z));
				break;
			}
			case 2:{
				cin>>x>>y>>z;
				printf("%d\n",query(x,y,z));
				break;
			}
		}
	}
	return 0;
}