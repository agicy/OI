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
	inline Vector operator-(void)const{
		return Vector(-x,-y);
	}
};

inline ll dot(const Vector& a,const Vector& b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

const int MAXN=5e4+5;
const int MAXM=5e4+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m;
int a[MAXN];
int lef[MAXN],rig[MAXN],id[MAXN];

struct Node{
	int id;
	Point p;
	inline Node(reg int id,const Point& p):id(id),p(p){
		return;
	}
};

vector<Node> S[MAXN];

inline void build(reg int id){
	S[id].clear();
	Point sum(0,0);
	for(reg int i=lef[id];i<=rig[id];++i){
		if(a[i]>0)
			sum=sum+Point(a[i],0);
		else
			sum=sum+Point(0,-a[i]);
		while(S[id].size()>=2u&&cross(S[id].back().p-(S[id].end()-2)->p,sum-S[id].back().p)<0)
			S[id].pop_back();
		S[id].push_back(Node(i,sum));
	}
	return;
}

inline int query(reg int id,const Vector& p){
	reg int _l=0,_r=S[id].size()-1,_mid;
	while(_l<_r){
		_mid=(_l+_r)>>1;
		if(cross(S[id][_mid+1].p-S[id][_mid].p,p)>0)
			_l=_mid+1;
		else
			_r=_mid;
	}
	return S[id][_l].id;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	Vector unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,const Vector& a){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=unit[i]+a;
		return;
	}
	inline Vector query(reg int id){
		Vector res;
		for(reg int i=id;i;i^=lowbit(i))
			res=res+unit[i];
		return res;
	}
}

int main(void){
	freopen("joker.in","r",stdin);
	freopen("joker.out","w",stdout);
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	BIT::Init(n);
	for(reg int i=1;i<=n;++i)
		if(a[i]>0)
			BIT::update(i,Vector(a[i],0));
		else
			BIT::update(i,Vector(0,-a[i]));
	reg int B=max(100,int(sqrt(n*log2(n)))),tot=(n+B-1)/B;
	pair<ll,int> ans=make_pair(inf,-1);
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i;
		build(i);
		Vector sum=BIT::query(n);
		int pos=query(i,sum);
		ans=min(ans,make_pair(-cross(BIT::query(pos),sum),pos));
	}
	writeln(ans.second);
	while(m--){
		static int p,v;
		p=read(),v=read();
		if(a[p]>0)
			BIT::update(p,-Vector(a[p],0));
		else
			BIT::update(p,-Vector(0,-a[p]));
		a[p]=v;
		if(a[p]>0)
			BIT::update(p,Vector(a[p],0));
		else
			BIT::update(p,Vector(0,-a[p]));
		build(id[p]);
		ans=make_pair(inf,-1);
		Vector sum=BIT::query(n);
		for(reg int i=1;i<=tot;++i){
			int pos=query(i,sum);
			ans=min(ans,make_pair(-cross(BIT::query(pos),sum),pos));
		}
		writeln(ans.second);
	}
	flush();
	fclose(stdin);
	fclose(stdout);
	return 0;
}