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

inline char* read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return s;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXS=5e5+5;

namespace AC{
	struct Node{
		int ch[26],fail;
		ll sum;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXS];
	inline int insert(reg char *s,reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return p;
	}
	vector<int> G[MAXS];
	int Q[MAXS];
	inline void build(void){
		reg int _head=0,_tail=0;
		for(reg int i=0;i<26;++i)
			if(ch(0)[i])
				Q[_tail++]=ch(0)[i];
		while(_head<_tail){
			reg int u=Q[_head++];
			for(reg int i=0;i<26;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q[_tail++]=ch(u)[i];
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		for(int i=1;i<=tot;++i)
			G[fail(i)].push_back(i);
		return;
	}
	int tim,dfn[MAXS],siz[MAXS];
	inline void dfs(reg int u){
		siz[u]=1;
		dfn[u]=++tim;
		for(int v:G[u]){
			dfs(v);
			siz[u]+=siz[v];
		}
		return;
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		ll Max;
		#define Max(x) unit[(x)].Max
	};
	Node unit[MAXS<<2];
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg ll val){
		if(L<=l&&r<=R){
			Max(k)=max(Max(k),val);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		return;
	}
	inline ll query(reg int k,reg int l,reg int r,reg int pos){
		if(l==r)
			return Max(k);
		if(pos<=mid)
			return max(Max(k),query(lson,l,mid,pos));
		else
			return max(Max(k),query(rson,mid+1,r,pos));
	}
	#undef lson
	#undef rson
	#undef mid
	#undef Max
}

inline ll query(const string& s){
	reg int p=0;
	reg ll res=0;
	for(reg int i=0,len=s.length();i<len;++i){
		reg int c=s[i]-'a';
		p=AC::ch(p)[c];
		res=max(res,SegmentTree::query(1,1,AC::tot,AC::dfn[p]));
	}
	return res;
}

int n;
int val[MAXS],mat[MAXS];
string a[MAXS];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static char s[MAXS];
		reg int len=read(s)-s;
		a[i]=s;
		val[i]=read(),mat[i]=AC::insert(s,len);
	}
	AC::build();
	AC::dfs(0);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		reg ll res=query(a[i])+val[i];
		ans=max(ans,res);
		SegmentTree::update(1,1,AC::tot,AC::dfn[mat[i]],AC::dfn[mat[i]]+AC::siz[mat[i]]-1,res);
	}
	printf("%lld\n",ans);
	return 0;
}