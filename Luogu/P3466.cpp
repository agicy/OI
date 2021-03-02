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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,k;
int a[MAXN];

namespace FHQTreap{
	const int MAXSIZE=MAXN;
	struct Node{
		int lson,rson,siz;
		int val;
		ll sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	int rt;
	inline int New(reg int v){
		reg int p=++tot;
		lson(p)=rson(p)=0,siz(p)=1;
		val(p)=sum(p)=v;
		return p;
	}
	inline void pushup(reg int p){
		siz(p)=siz(lson(p))+siz(rson(p))+1;
		sum(p)=sum(lson(p))+sum(rson(p))+val(p);
		return;
	}
	inline void split(reg int p,reg int v,reg int &x,reg int &y){
		if(!p){
			x=y=0;
			return;
		}
		if(val(p)<=v){
			x=p;
			split(rson(x),v,rson(x),y);
			pushup(x);
		}
		else{
			y=p;
			split(lson(y),v,x,lson(y));
			pushup(y);
		}
		return;
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		if(rand()%(siz(x)+siz(y))<siz(x)){
			rson(x)=merge(rson(x),y);
			pushup(x);
			return x;
		}
		else{
			lson(y)=merge(x,lson(y));
			pushup(y);
			return y;
		}
	}
	inline int kth(reg int p,reg int k){
		while(true)
			if(k<=siz(lson(p)))
				p=lson(p);
			else{
				k-=siz(lson(p))+1;
				if(!k)
					return val(p);
				else
					p=rson(p);
			}
		return -1;
	}
	inline void insert(reg int v){
		static int rt1,rt2;
		split(rt,v,rt1,rt2);
		rt=merge(merge(rt1,New(v)),rt2);
		return;
	}
	inline void del(reg int v){
		static int rt1,mid,rt2;
		split(rt,v,rt1,rt2),split(rt1,v-1,rt1,mid);
		mid=merge(lson(mid),rson(mid));
		rt=merge(merge(rt1,mid),rt2);
		return;
	}
}

using namespace FHQTreap;

int main(void){
	srand(time(0));
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg ll ans1=inf;
	int lef,rig,ans2;
	for(reg int i=1;i<=n;++i){
		insert(a[i]);
		if(i>=k){
			if(i!=k)
				del(a[i-k]);
			reg int val=kth(rt,(k>>1)+1);
			static int rt1,mid,rt2;
			split(rt,val,rt1,rt2),split(rt1,val-1,rt1,mid);
			reg ll sum=1ll*val*siz(rt1)-sum(rt1)+sum(rt2)-1ll*val*siz(rt2);
			if(sum<ans1)
				ans1=sum,lef=i-k+1,rig=i,ans2=val;
			rt=merge(merge(rt1,mid),rt2);
		}
	}
	writeln(ans1);
	for(reg int i=1;i<=n;++i)
		if(lef<=i&&i<=rig)
			writeln(ans2);
		else
			writeln(a[i]);
	flush();
	return 0;
}