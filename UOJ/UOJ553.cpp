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
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline double sqr(reg double x){
	return x*x;
}

const int MAXN=1.2e4+5;
const int MAXQ=1e6+5;

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline ll dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

inline bool operator<(const Point& a,const Point& b){
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}

inline ll getDis2(const Point& a,const Point& b){
	return dot(a-b,a-b);
}

inline double getPos(const Point& a,const Point& b){
	return ((sqr(a.x)+sqr(a.y))-(sqr(b.x)+sqr(b.y)))/(2.0*(a.y-b.y));
}

struct Node{
	int id;
	Point p;
	inline bool operator<(const Node& a)const{
		return p<a.p;
	}
};

struct querys{
	int id,z,r;
	inline bool operator<(const querys& a)const{
		return z<a.z||(z==a.z&&r<a.r);
	}
};

struct Event{
	double val;
	int x,y;
	inline Event(reg double val=0,reg int x=0,reg int y=0):val(val),x(x),y(y){
		return;
	}
	inline bool operator<(const Event& a)const{
		return val>a.val;
	}
};

int n,Q;
Node a[MAXN];
int rnk[MAXN];
querys q[MAXQ];
int ans[MAXQ];

inline void solve(reg int lef,reg int rig){
	priority_queue<Event> Qu;
	for(reg int j=lef;j<rig;++j)
		if(a[j].p.y<a[j+1].p.y)
			Qu.push(Event(getPos(a[j].p,a[j+1].p),a[j].id,a[j+1].id));
	for(reg int j=1;j<=Q;++j){
		while(!Qu.empty()){
			static Event e;
			e=Qu.top();
			if(e.val>q[j].z)
				break;
			Qu.pop();
			if(a[rnk[e.x]+1].id==e.y){
				reg int id=rnk[e.x];
				swap(a[id],a[id+1]);
				++rnk[e.x],--rnk[e.y];
				if(lef<id&&a[id-1].p.y<a[id].p.y)
					Qu.push(Event(getPos(a[id-1].p,a[id].p),a[id-1].id,a[id].id));
				if(id+1<rig&&a[id+1].p.y<a[id+2].p.y)
					Qu.push(Event(getPos(a[id+1].p,a[id+2].p),a[id+1].id,a[id+2].id));
			}
		}
		reg ll limit=1ll*q[j].r*q[j].r;
		if(getDis2(a[lef].p,Point(0,q[j].z))<=limit){
			reg int _l=lef,_r=rig,_mid;
			while(_l<_r){
				_mid=(_l+_r)>>1;
				if(getDis2(a[_mid+1].p,Point(0,q[j].z))<=limit)
					_l=_mid+1;
				else
					_r=_mid;
			}
			ans[q[j].id]+=_l-lef+1;
		}
	}
	return;
}

int main(void){
	n=read(),Q=read();
	for(reg int i=1;i<=n;++i)
		a[i].p.x=abs(read()),a[i].p.y=read();
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		a[i].id=i,rnk[i]=i;
	for(reg int i=1;i<=Q;++i)
		q[i].id=i,q[i].z=read(),q[i].r=read();
	sort(q+1,q+Q+1);
	reg int B=max(10,int(sqrt(Q))),tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i)
		solve((i-1)*B+1,min(i*B,n));
	for(reg int i=1;i<=Q;++i)
		writeln(ans[i]);
	flush();
	return 0;
}