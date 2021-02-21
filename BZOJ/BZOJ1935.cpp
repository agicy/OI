#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline int abs(reg int x){
	return x<0?-x:x;
}

inline int sgn(reg int x){
	if(!x)
		return 0;
	else
		return x<0?-1:1;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;

struct Node{
	int id,x,y;
	inline Node(reg int id=0,reg int x=0,reg int y=0):id(id),x(x),y(y){
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x||(x==a.x&&abs(id)<abs(a.id));
	}
};

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN+MAXM*2];
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
}

int n,m;
int x[MAXN],y[MAXN];
int a[MAXM],b[MAXM],c[MAXM],d[MAXM];
Node p[MAXN+MAXM*4];
vector<int> Vx,Vy;
int ans[MAXM];

int main(void){
	n=read(),m=read();
	Vx.resize(n+(m<<1)),Vy.resize(n+(m<<1));
	for(reg int i=0;i<n;++i){
		x[i]=read(),y[i]=read();
		Vx[i]=x[i],Vy[i]=y[i];
	}
	for(reg int i=0,j=n;i<m;++i,j+=2){
		a[i]=read()-1,b[i]=read()-1,c[i]=read(),d[i]=read();
		Vx[j]=a[i],Vx[j+1]=c[i];
		Vy[j]=b[i],Vy[j+1]=d[i];
	}
	sort(Vx.begin(),Vx.end());
	Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end());
	Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	reg int tot=0;
	for(reg int i=0;i<n;++i){
		x[i]=lower_bound(Vx.begin(),Vx.end(),x[i])-Vx.begin()+1;
		y[i]=lower_bound(Vy.begin(),Vy.end(),y[i])-Vy.begin()+1;
		p[tot++]=Node(0,x[i],y[i]);
	}
	for(reg int i=0;i<m;++i){
		a[i]=lower_bound(Vx.begin(),Vx.end(),a[i])-Vx.begin()+1;
		c[i]=lower_bound(Vx.begin(),Vx.end(),c[i])-Vx.begin()+1;
		b[i]=lower_bound(Vy.begin(),Vy.end(),b[i])-Vy.begin()+1;
		d[i]=lower_bound(Vy.begin(),Vy.end(),d[i])-Vy.begin()+1;
		reg int id=i+1;
		p[tot]=Node(id,a[i],b[i]),p[tot+1]=Node(-id,c[i],b[i]),p[tot+2]=Node(-id,a[i],d[i]),p[tot+3]=Node(id,c[i],d[i]);
		tot+=4;
	}
	sort(p,p+tot);
	BIT::Init(Vy.size());
	for(reg int i=0;i<tot;++i)
		switch(sgn(p[i].id)){
			case 0:{
				BIT::update(p[i].y,1);
				break;
			}
			case -1:{
				ans[-p[i].id]-=BIT::query(p[i].y);
				break;
			}
			case 1:{
				ans[p[i].id]+=BIT::query(p[i].y);
				break;
			}
		}
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}