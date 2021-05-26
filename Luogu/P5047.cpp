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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int abs(reg int x){
	return x<0?-x:x;
}

inline int sgn(reg int x){
	if(x<0)
		return -1;
	else
		return x?1:0;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m,k;
int a[MAXN];
int blk[MAXN];

struct querys{
	int id,l,r;
	ll ans;
	inline bool operator<(const querys& a)const{
		return blk[l]==blk[a.l]?r<a.r:l<a.l;
	}
};

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		fill(unit+1,unit+n+1,0);
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
}

struct Eventl{
	int id,l,r;
	inline Eventl(reg int id=0,reg int l=0,reg int r=0):id(id),l(l),r(r){
		return;
	}
};

struct Eventg{
	int id,l,r;
	inline Eventg(reg int id=0,reg int l=0,reg int r=0):id(id),l(l),r(r){
		return;
	}
};

querys q[MAXM];
ll ans[MAXM];
ll sumg[MAXN],suml[MAXN];
vector<Eventl> El[MAXN];
vector<Eventg> Eg[MAXN];

namespace Val{
	int k,Bk,totk;
	int lefk[MAXN],rigk[MAXN],idk[MAXN];
	int sumS[MAXN],sumB[MAXN];
	inline void Init(reg int s){
		k=s;
		Bk=max(50,int(sqrt(k))),totk=(k+Bk-1)/Bk;
		for(reg int i=1;i<=k;++i){
			lefk[i]=(i-1)*Bk+1,rigk[i]=min(i*Bk,k);
			for(reg int j=lefk[i];j<=rigk[i];++j)
				idk[j]=i;
		}
		return;
	}
	inline void update(reg int id,reg int Val){
		reg int bid=idk[id];
		for(reg int i=id;i<=rigk[bid];++i)
			sumS[i]+=Val;
		for(reg int i=bid;i<=totk;++i)
			sumB[i]+=Val;
		return;
	}
	inline int query(reg int id){
		return sumB[idk[id]-1]+sumS[id];
	}
}

int main(void){
	n=read(),m=read();
	vector<int> V;
	V.resize(n);
	for(reg int i=1;i<=n;++i)
		V[i-1]=a[i]=read();
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	reg int B=max(100,int(n/sqrt(m))),tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		reg int lef=(i-1)*B+1,rig=min(i*B,n);
		for(reg int j=lef;j<=rig;++j)
			blk[j]=i;
	}
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+m+1);
	BIT::Init(V.size());
	for(reg int i=1;i<=n;++i){
		BIT::update(a[i],1);
		suml[i]=suml[i-1]+(i-BIT::query(a[i]));
	}
	BIT::Init(V.size());
	for(reg int i=1;i<=n;++i){
		BIT::update(a[i],1);
		sumg[i]=sumg[i-1]+BIT::query(a[i]-1);
	}
	reg int l=1,r=0;
	for(reg int i=1;i<=m;++i){
		if(r<q[i].r){
			El[l-1].push_back(Eventl(-i,r+1,q[i].r));
			q[i].ans+=suml[q[i].r]-suml[r],r=q[i].r;
		}
		if(r>q[i].r){
			El[l-1].push_back(Eventl(i,q[i].r+1,r));
			q[i].ans-=suml[r]-suml[q[i].r],r=q[i].r;
		}
		if(l<q[i].l){
			Eg[r].push_back(Eventg(-i,l,q[i].l-1));
			q[i].ans+=sumg[q[i].l-1]-sumg[l-1],l=q[i].l;
		}
		if(l>q[i].l){
			Eg[r].push_back(Eventg(i,q[i].l,l-1));
			q[i].ans-=sumg[l-1]-sumg[q[i].l-1],l=q[i].l;
		}
	}
	Val::Init(V.size());
	for(reg int i=1;i<=n;++i){
		Val::update(a[i],1);
		for(Eventg eg:Eg[i]){
			reg ll sum=0;
			for(reg int j=eg.l;j<=eg.r;++j)
				sum+=Val::query(a[j]-1);
			q[abs(eg.id)].ans+=sgn(eg.id)*sum;
		}
		for(Eventl el:El[i]){
			reg ll sum=0;
			for(reg int j=el.l;j<=el.r;++j)
				sum+=i-Val::query(a[j]);
			q[abs(el.id)].ans+=sgn(el.id)*sum;
		}
	}
	for(reg int i=1;i<=m;++i){
		q[i].ans+=q[i-1].ans;
		ans[q[i].id]=q[i].ans;
	}
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}