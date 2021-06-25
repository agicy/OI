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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e5;
const int MAXQ=5e5;

struct Point{
	int x,y,w;
	inline bool operator<(const Point& a)const{
		return y<a.y;
	}
};

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return l<a.l;
	}
};

int n;
Point r[MAXN],b[MAXN];
int q;
querys qu[MAXQ];
int ans[MAXQ];

inline int getId(const vector<int>& V,int x){
	return lower_bound(V.begin(),V.end(),x)-V.begin()+1;
}

struct Event{
	int rx,bx,w;
	inline Event(reg int rx=0,reg int bx=0,reg int w=0):rx(rx),bx(bx),w(w){
		return;
	}
	inline bool operator<(const Event& a)const{
		return rx<a.rx;
	}
};

vector<Event> V;

inline void solve(reg int _l,reg int _r,reg int lr,reg int rr,reg int lb,reg int rb){
	reg int _mid=(_l+_r)>>1;
	reg int midr;
	if(r[lr].y>_mid)
		midr=lr-1;
	else if(r[rr].y<=_mid)
		midr=rr;
	else{
		reg int __l=lr,__r=rr,__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(r[__mid+1].y<=_mid)
				__l=__mid+1;
			else
				__r=__mid;
		}
		midr=__l;
	}
	reg int midb;
	if(b[lb].y>_mid)
		midb=lb-1;
	else if(b[rb].y<=_mid)
		midb=rb;
	else{
		reg int __l=lb,__r=rb,__mid;
		while(__l<__r){
			__mid=(__l+__r)>>1;
			if(b[__mid+1].y<=_mid)
				__l=__mid+1;
			else
				__r=__mid;
		}
		midb=__l;
	}
	reg int Maxr=-1;
	for(reg int i=lr;i<=midr;++i)
		if(Maxr==-1||r[i].w>r[Maxr].w)
			Maxr=i;
	if(Maxr!=-1){
		V.reserve(rb-midb);
		for(reg int i=midb+1;i<=rb;++i)
			V.push_back(Event(r[Maxr].x,b[i].x,r[Maxr].w+b[i].w));
	}
	reg int Maxb=-1;
	for(reg int i=midb+1;i<=rb;++i)
		if(Maxb==-1||b[i].w>b[Maxb].w)
			Maxb=i;
	if(Maxb!=-1){
		V.reserve(midr-lr+1);
		for(reg int i=lr;i<=midr;++i)
			V.push_back(Event(r[i].x,b[Maxb].x,r[i].w+b[Maxb].w));
	}
	if(lr<=midr&&lb<=midb)
		solve(_l,_mid,lr,midr,lb,midb);
	if(midr<rr&&midb<rb)
		solve(_mid+1,_r,midr+1,rr,midb+1,rb);
	return;
}

namespace BIT{
	const int inf=0x3f3f3f3f;
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	int unit[MAXN+MAXQ+2];
	inline void Init(reg int s){
		n=s;
		fill(unit+1,unit+s+1,-inf);
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=max(unit[i],val);
		return;
	}
	inline int query(reg int id){
		reg int res=-inf;
		for(reg int i=id;i;i^=lowbit(i))
			res=max(res,unit[i]);
		return res;
	}
}

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		r[i].x=read(),r[i].y=read(),r[i].w=read();
	for(reg int i=0;i<n;++i)
		b[i].x=read(),b[i].y=read(),b[i].w=read();
	q=read();
	for(reg int i=0;i<q;++i)
		qu[i].id=i,qu[i].l=read(),qu[i].r=read();
	vector<int> Vy,Vrx,Vbx;
	Vy.resize(n<<1),Vrx.resize(n+q),Vbx.resize(n+q);
	for(reg int i=0;i<n;++i)
		Vrx[i]=r[i].x,Vy[i]=r[i].y;
	for(reg int i=0;i<n;++i)
		Vbx[i]=b[i].x,Vy[i+n]=b[i].y;
	for(reg int i=0;i<q;++i)
		Vrx[i+n]=qu[i].l,Vbx[i+n]=qu[i].r;
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	sort(Vrx.begin(),Vrx.end()),Vrx.erase(unique(Vrx.begin(),Vrx.end()),Vrx.end());
	sort(Vbx.begin(),Vbx.end()),Vbx.erase(unique(Vbx.begin(),Vbx.end()),Vbx.end());
	for(reg int i=0;i<n;++i)
		r[i].y=getId(Vy,r[i].y),r[i].x=getId(Vrx,r[i].x);
	for(reg int i=0;i<n;++i)
		b[i].y=getId(Vy,b[i].y),b[i].x=getId(Vbx,b[i].x);
	for(reg int i=0;i<q;++i)
		qu[i].l=getId(Vrx,qu[i].l),qu[i].r=getId(Vbx,qu[i].r);
	sort(r,r+n),sort(b,b+n);
	solve(1,Vy.size(),0,n-1,0,n-1);
	sort(V.begin(),V.end());
	memset(ans,-1,sizeof(int)*q);
	sort(qu,qu+q);
	const int S=Vbx.size();
	BIT::Init(S+1);
	for(reg int i=0,ptr=0;i<q;++i){
		while(ptr<(int)V.size()&&V[ptr].rx<qu[i].l)
			BIT::update(S-V[ptr].bx+1,V[ptr].w),++ptr;
		ans[qu[i].id]=max(ans[qu[i].id],BIT::query(S-qu[i].r+1));
	}
	BIT::Init(S+1);
	for(reg int i=q-1,ptr=V.size()-1;i>=0;--i){
		while(ptr>=0&&V[ptr].rx>qu[i].l)
			BIT::update(V[ptr].bx+1,V[ptr].w),--ptr;
		ans[qu[i].id]=max(ans[qu[i].id],BIT::query(qu[i].r+1));
	}
	for(reg int i=0;i<q;++i)
		writeln(ans[i]);
	flush();
	fprintf(stderr,"%.3lf ms\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}