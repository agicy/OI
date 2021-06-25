#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5+5;
const int MAXB=1e5+5;

struct Snow{
	int pos,dep;
	inline bool operator<(const Snow& a)const{
		return dep>a.dep;
	}
};

struct Boot{
	int id,s,d;
	inline bool operator<(const Boot& a)const{
		return s>a.s;
	}
};

int n,b;
Snow a[MAXN];
Boot s[MAXB];
bool tag[MAXN];
bool ans[MAXB];

namespace UnionFind{
	int fa[MAXN],siz[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1;
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
		if(ra!=rb){
			fa[rb]=ra;
			siz[ra]+=siz[rb];
		}
		return;
	}
}

int main(void){
	n=read(),b=read();
	for(reg int i=1;i<=n;++i)
		a[i].pos=i,a[i].dep=read();
	sort(a+1,a+n+1);
	for(reg int i=1;i<=b;++i)
		s[i].id=i,s[i].s=read(),s[i].d=read();
	sort(s+1,s+b+1);
	UnionFind::Init(n);
	reg int ptr=1;
	reg int Max=0;
	for(reg int i=1;i<=b;++i){
		while(ptr<=n&&a[ptr].dep>s[i].s){
			reg int pos=a[ptr].pos;
			tag[pos]=true;
			if(tag[pos-1])
				UnionFind::merge(pos-1,pos);
			if(tag[pos+1])
				UnionFind::merge(pos+1,pos);
			Max=max(Max,UnionFind::siz[UnionFind::find(pos)]);
			++ptr;
		}
		if(s[i].d>Max)
			ans[s[i].id]=true;
	}
	for(reg int i=1;i<=b;++i)
		putchar(ans[i]|'0'),putchar('\n');
	flush();
	return 0;
}