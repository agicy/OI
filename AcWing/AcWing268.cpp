#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=3e5+5;
const int MAXM=3e5+5;
const int MAXK=3e5+5;
const int inf=0x3f3f3f3f;

struct updates{
	int l,r,val;
	inline updates(reg int l=0,reg int r=0,reg int val=0):l(l),r(r),val(val){
		return;
	}
};

int n,m,k;
vector<int> g[MAXM];
updates u[MAXK];
int ned[MAXK];
int ans[MAXN];
int id[MAXN],le[MAXN],ri[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXM];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
}

inline void solve(reg int l,reg int r,reg int ql,reg int qr){
	if(ql>qr)
		return;
	if(l==r){
		for(reg int i=ql;i<=qr;++i)
			ans[id[i]]=l;
		return;
	}
	reg int mid=(l+r)>>1;
	for(reg int i=l;i<=mid;++i){
		reg int val=u[i].val;
		if(u[i].l<=u[i].r){
			BIT::update(u[i].l,val);
			BIT::update(u[i].r+1,-val);
		}
		else{
			BIT::update(u[i].l,val);
			BIT::update(1,val);
			BIT::update(u[i].r+1,-val);
		}
	}
	reg int ptrl=0,ptrr=0;
	for(reg int i=ql;i<=qr;++i){
		reg ll cnt=0;
		for(reg int j=0,siz=g[id[i]].size();j<siz;++j){
			cnt+=BIT::query(g[id[i]][j]);
			if(cnt>=ned[id[i]])
				break;
		}
		if(cnt<ned[id[i]])
			ned[id[i]]-=cnt,ri[++ptrr]=id[i];
		else
			le[++ptrl]=id[i];
	}
	for(reg int i=l;i<=mid;++i){
		reg int val=u[i].val;
		if(u[i].l<=u[i].r){
			BIT::update(u[i].l,-val);
			BIT::update(u[i].r+1,val);
		}
		else{
			BIT::update(u[i].l,-val);
			BIT::update(1,-val);
			BIT::update(u[i].r+1,val);
		}
	}
	for(reg int i=1;i<=ptrl;++i)
		id[ql+i-1]=le[i];
	for(reg int i=1;i<=ptrr;++i)
		id[ql+ptrl+i-1]=ri[i];
	solve(l,mid,ql,ql+ptrl-1),solve(mid+1,r,ql+ptrl,qr);
	return;
}

int main(void){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		static int o;
		o=read();
		g[o].push_back(i);
	}
	for(reg int i=1;i<=n;++i)
		ned[i]=read();
	for(reg int i=1;i<=n;++i)
		id[i]=i;
	k=read();
	for(reg int i=1;i<=k;++i){
		static int l,r,id;
		l=read(),r=read(),id=read();
		u[i]=updates(l,r,id);
	}
	u[k+1]=updates(1,m,inf);
	BIT::Init(m);
	solve(1,k+1,1,n);
	for(reg int i=1;i<=n;++i)
		if(ans[i]>k)
			puts("NIE");
		else
			printf("%d\n",ans[i]);
	return 0;
}