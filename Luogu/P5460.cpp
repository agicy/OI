#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

struct IP{
	uint ip;
	int cnt;
	inline IP(reg uint ip=0,reg int cnt=0):ip(ip),cnt(cnt){
		return;
	}
};

inline void read(reg IP &a){
	reg char ch=getchar();
	reg uint ip=0;
	reg int cnt=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='1')ip+=((ch-'0')<<cnt),++cnt,ch=getchar();
	a=IP(ip,cnt);
	return;
}

struct Updates{
	char opt;
	IP ip;
	inline void Read(void){
		static char str[32];
		scanf("%s",str);
		read(ip);
		opt=str[0];
		return;
	}
};

struct Querys{
	IP ip;
	int ID;
	inline void Read(reg int i){
		read(ip),ID=i;
		return;
	}
};

int n,m,ans[MAXN];
Updates U[MAXN];
vector<Querys> r[MAXN],l[MAXN];

namespace Trie{
	const int MAXSIZE=MAXN<<6;
	
	int root;
	int tot;
	int ch[MAXSIZE][2];
	int val[MAXSIZE],tag[MAXSIZE];
	int vis[MAXSIZE];
	inline void Set(reg int &k,reg int v){
		if(!k)
			k=++tot;
		if(!vis[k]){
			val[k]+=v;
			tag[k]+=v;
		}
		return;
	}
	inline void pushdown(reg int k){
		if(tag[k]){
			Set(ch[k][0],tag[k]);
			Set(ch[k][1],tag[k]);
			tag[k]=0;
		}
		return;
	}
	inline void ins(reg int &k,const IP& ip,int p){
		if(!k)
			k=++tot;
		if(p==ip.cnt){
			Set(k,1);
			++vis[k];
			return;
		}
		pushdown(k);
		ins(ch[k][(ip.ip>>p)&1],ip,p+1);
		return;
	}
	inline void del(reg int &k,const IP& ip,reg int p){
		if(!k)
			k=++tot;
		if(p==ip.cnt){
			--vis[k];
			Set(k,1);
			return;
		}
		pushdown(k);
		del(ch[k][(ip.ip>>p)&1],ip,p+1);
		return;
	}
	inline int Query(reg int k,const IP& ip,reg int p){
		if(!k)
			return 0;
		if(p==ip.cnt)
			return val[k];
		pushdown(k);
		return Query(ch[k][(ip.ip>>p)&1],ip,p+1);
	}
}

using namespace Trie;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		U[i].Read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		static Querys Q;
		Q.Read(i);
		a=read(),b=read();
		l[a].push_back(Q);
		r[b].push_back(Q);
	}
	for(reg int i=1;i<=n;++i){
		if(U[i].opt=='A')
			ins(root,U[i].ip,0);
		else
			del(root,U[i].ip,0);
		for(reg int j=0,size=r[i].size();j<size;++j)
			ans[r[i][j].ID]+=Query(root,r[i][j].ip,0);
		for(reg int j=0,size=l[i].size();j<size;++j)
			ans[l[i][j].ID]-=Query(root,l[i][j].ip,0);
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
