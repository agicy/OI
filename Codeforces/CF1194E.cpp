#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e3+5;

int n;
vector<int> Vx,Vy;

struct hL{
	int x1,x2,y;
	inline hL(reg int x1=0,reg int x2=0,reg int y=0):x1(x1),x2(x2),y(y){
		return;
	}
	inline bool operator<(const hL &a)const{
		return y<a.y;
	}
};

struct vL{
	int x,y1,y2;
	inline vL(reg int x=0,reg int y1=0,reg int y2=0):x(x),y1(y1),y2(y2){
		return;
	}
	inline bool operator<(const vL& a)const{
		return y2<a.y2;
	}
};

int toth,totv;
hL H[MAXN];
vL V[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN<<1];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
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

inline bool check(reg int x,reg int l,reg int r){
	return l<=x&&x<=r;
}

int main(void){
	n=read();
	Vx.resize(n<<1),Vy.resize(n<<1);
	for(reg int i=1;i<=n;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		if(x1>x2)
			swap(x1,x2);
		if(y1>y2)
			swap(y1,y2);
		if(y1==y2)
			H[++toth]=hL(x1,x2,y1);
		else
			V[++totv]=vL(x1,y1,y2);
		Vx[((i-1)<<1)]=x1,Vx[((i-1)<<1)|1]=x2,Vy[((i-1)<<1)]=y1,Vy[((i-1)<<1)|1]=y2;
	}
	sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	for(reg int i=1;i<=toth;++i){
		H[i].x1=lower_bound(Vx.begin(),Vx.end(),H[i].x1)-Vx.begin()+1;
		H[i].x2=lower_bound(Vx.begin(),Vx.end(),H[i].x2)-Vx.begin()+1;
		H[i].y=lower_bound(Vy.begin(),Vy.end(),H[i].y)-Vy.begin()+1;
	}
	for(reg int i=1;i<=totv;++i){
		V[i].x=lower_bound(Vx.begin(),Vx.end(),V[i].x)-Vx.begin()+1;
		V[i].y1=lower_bound(Vy.begin(),Vy.end(),V[i].y1)-Vy.begin()+1;
		V[i].y2=lower_bound(Vy.begin(),Vy.end(),V[i].y2)-Vy.begin()+1;
	}
	sort(H+1,H+toth+1),sort(V+1,V+totv+1);
	reg ll ans=0;
	BIT::Init(Vx.size());
	for(reg int i=1;i<=toth;++i){
		reg int _head=0,_tail=0;
		static int Q[MAXN];
		for(reg int j=1;j<=totv;++j)
			if(check(H[i].y,V[j].y1,V[j].y2)&&check(V[j].x,H[i].x1,H[i].x2))
				BIT::update(V[Q[_tail++]=j].x,1);
		for(reg int j=i+1;j<=toth;++j){
			reg int l=max(H[i].x1,H[j].x1),r=min(H[i].x2,H[j].x2);
			if(l<r){
				while(_head<_tail&&V[Q[_head]].y2<H[j].y)
					BIT::update(V[Q[_head++]].x,-1);
				reg int cnt=BIT::query(l,r);
				ans+=(cnt*(cnt-1)>>1);
			}
		}
		while(_head<_tail)
			BIT::update(V[Q[_head++]].x,-1);
	}
	printf("%lld\n",ans);
	return 0;
}