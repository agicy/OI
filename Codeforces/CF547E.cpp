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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int abs(reg int x){
	return x>=0?x:-x;
}

inline int sgn(reg int x){
	if(!x)
		return 0;
	else
		return x<0?-1:1;
}

const int MAXN=2e5+5;
const int MAXQ=5e5+5;
const int MAXS=2e5+5;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXS];
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

namespace AC{
	const int MAXSIZE=MAXS;
	struct Node{
		int fa,ch[26];
		int fail;
		vector<int> G;
		#define fa(x) unit[(x)].fa
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define G(x) unit[(x)].G
	};
	int tot;
	Node unit[MAXSIZE];
	inline int insert(reg char s[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]-'a';
			if(!ch(p)[c]){
				ch(p)[c]=++tot;
				fa(ch(p)[c])=p;
			}
			p=ch(p)[c];
		}
		return p;
	}
	int siz[MAXS];
	int tim,dfn[MAXS];
	inline void dfs(reg int u){
		siz[u]=1;
		dfn[u]=++tim;
		for(int v:G(u)){
			dfs(v);
			siz[u]+=siz[v];
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
				if(!ch(u)[i])
					ch(u)[i]=ch(fail(u))[i];
				else
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
		}
		for(int i=1;i<=tot;++i)
			G(fail(i)).push_back(i);
		dfs(0);
		return;
	}
}

struct querys{
	int x,pos,id;
	inline querys(reg int x=0,reg int pos=0,reg int id=0):x(x),pos(pos),id(id){
		return;
	}
	inline bool operator<(const querys& a)const{
		return x<a.x;
	}
};

int n,q;
int mat[MAXN];
int ans[MAXQ];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		static char s[MAXS];
		reg int len=read(s)-s;
		mat[i]=AC::insert(s,len);
	}
	AC::build();
	vector<querys> V;
	V.reserve(q<<1);
	for(reg int i=1;i<=q;++i){
		static int l,r,k;
		l=read(),r=read(),k=read();
		V.push_back(querys(l-1,k,-i));
		V.push_back(querys(r,k,i));
	}
	sort(V.begin(),V.end());
	reg int ptr=0;
	while(ptr<(int)V.size()&&!V[ptr].x)
		++ptr;
	BIT::Init(AC::tim);
	for(reg int i=1;i<=n;++i){
		for(reg int j=mat[i];j;j=AC::fa(j))
			BIT::update(AC::dfn[j],1);
		while(ptr<(int)V.size()&&V[ptr].x==i){
			reg int u=mat[V[ptr].pos];
			ans[abs(V[ptr].id)]+=sgn(V[ptr].id)*BIT::query(AC::dfn[u],AC::dfn[u]+AC::siz[u]-1);
			++ptr;
		}
	}
	for(reg int i=1;i<=q;++i)
		writeln(ans[i]);
	flush();
	return 0;
}