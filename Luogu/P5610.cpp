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

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

static char wbuf[1<<21];
int wp1;
const int wp2=1<<21;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
	return;
}

#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXA=5e5+5;

int n,m;
int a[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		while(id<=n){
			unit[id]+=val;
			id+=lowbit(id);
		}
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		while(id){
			res+=unit[id];
			id^=lowbit(id);
		}
		return res;
	}
}

const int BLOCK=500;

struct Vector{
	vector<int> unit;
	int ptr,len;
	inline void getMore(void){
		unit.resize(len+=BLOCK);
		return;
	}
	inline void push_back(const int& x){
		if(ptr>=len)
			getMore();
		unit[ptr++]=x;
		return;
	}
	inline int& operator[](reg int x){
		return unit[x];
	}
	inline void turnToSoild(void){
		unit.resize(ptr);
		return;
	}
};

vector<int> fa[MAXA];
Vector fac[MAXA];

inline int find(vector<int>& fa,reg int x){
	if(x==fa.size())
		return x;
	else
		return fa[x]==x?x:fa[x]=find(fa,fa[x]);
}

inline void update(int l,reg int r,const int& x){
	if(x==1)
		return;
	reg int u=lower_bound(fac[x].unit.begin(),fac[x].unit.end(),l)-fac[x].unit.begin();
	for(reg int i=find(fa[x],u),siz=fac[x].unit.size();i<siz&&fac[x][i]<=r;i=find(fa[x],i+1)){
		if(a[fac[x][i]]%x==0){
			reg int val=a[fac[x][i]]-a[fac[x][i]]/x;
			a[fac[x][i]]-=val;
			BIT::update(fac[x][i],-val);
		}
		if(a[fac[x][i]]%x)
			fa[x][i]=i+1;
	}
	return;
}

int cnt[MAXA];

int main(void){
	n=read(),m=read();
	BIT::Init(n);
	reg int Max=0;
	for(reg int i=1,x,j;i<=n;++i){
		x=read();
		Max=max(Max,x);
		for(j=1;j*j<=x;++j)
			if(x%j==0){
				if(j!=1){
					fac[j].push_back(i);
					++cnt[j];
				}
				if(j*j!=x){
					fac[x/j].push_back(i);
					++cnt[x/j];
				}
			}
		a[i]=x;
		BIT::update(i,x);
	}
	for(reg int i=1;i<=Max;++i)
		if(cnt[i]){
			fac[i].turnToSoild();
			fa[i].resize(cnt[i]);
			while(cnt[i]--)
				fa[i][cnt[i]]=cnt[i];
		}
	reg ll lastans=0;
	reg int opt,l,r,x;
	while(m--){
		do
			opt=getchar();
		while(!isalnum(opt));
		l=read()^lastans,r=read()^lastans;
		if(opt^'2')
			x=read()^lastans,update(l,r,x);
		else
			writeln(lastans=BIT::query(r)-BIT::query(l-1));
	}
	flush();
	return 0;
}