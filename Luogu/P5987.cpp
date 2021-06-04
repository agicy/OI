#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(min(l,r)),r(max(l,r)){
		return;
	}
};

int n,X,Y;
Interval a[MAXN];
Interval b[MAXN];

struct Event{
	int x;
	ull val;
	inline Event(reg int x=0,reg ull val=0):x(x),val(val){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x;
	}
};

struct Segment{
	int len;
	ull val;
	inline Segment(reg int len=0,reg ull val=0):len(len),val(val){
		return;
	}
	inline bool operator<(const Segment& a)const{
		return val<a.val;
	}
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int solve(reg int n,reg Interval a[],reg int X){
	vector<Event> E;
	E.reserve((n+1)<<1);
	for(reg int i=1;i<=n;++i){
		reg ull tag=rng();
		E.push_back(Event(a[i].l,tag));
		E.push_back(Event(a[i].r,tag));
	}
	E.push_back(Event(0,0));
	E.push_back(Event(X,0));
	sort(E.begin(),E.end());
	vector<Segment> V;
	reg ull val=0;
	for(reg int i=0,siz=E.size();i<siz-1;++i){
		val^=E[i].val;
		if(E[i].x<E[i+1].x)
			V.push_back(Segment(E[i+1].x-E[i].x,val));
	}
	sort(V.begin(),V.end());
	reg ull las=0;
	reg int sum=0;
	reg int res=0;
	for(reg int i=0,siz=V.size();i<siz;++i){
		if(las==V[i].val)
			sum+=V[i].len;
		else
			las=V[i].val,sum=V[i].len;
		res=max(res,sum);
	}
	return res;
}

int main(void){
	n=read(),X=read(),Y=read();
	for(reg int i=1;i<=n;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		a[i]=Interval(x1,x2);
		b[i]=Interval(y1,y2);
	}
	reg int ansx=solve(n,a,X);
	reg int ansy=solve(n,b,Y);
	reg ll ans=1ll*ansx*ansy;
	printf("%lld\n",ans);
	return 0;
}