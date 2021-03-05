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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

struct updates{
	int x,y,p;
	inline bool operator<(const updates& a)const{
		return x<a.x;
	}
};

struct querys{
	int opt,id,x,y;
	inline querys(reg int opt=0,reg int id=0,reg int x=0,reg int y=0):opt(opt),id(id),x(x),y(y){
		return;
	}
	inline bool operator<(const querys& a)const{
		return x<a.x;
	}
};

int n,m;
updates u[MAXN];
querys q[MAXM*4];
vector<int> Vx,Vy;
int Y;
ll ans[MAXM];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,tim;
	int t[MAXN+MAXM*4];
	ll unit[MAXN+MAXM*4];
	inline void Init(reg int s){
		n=s,++tim;
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			unit[i]+=val;
		}
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			res+=unit[i];
		}
		return res;
	}
}

int idu[MAXN],idq[MAXM*4];

inline void solve(reg int L,reg int R,reg int l,reg int r,reg int lef,reg int rig){
	if(L>R||l>r||lef>rig)
		return;
	if(lef==rig){
		BIT::Init(Y);
		for(reg int i=l;i<=r;++i)
			BIT::update(u[idu[i]].y,u[idu[i]].p);
		for(reg int i=L;i<=R;++i)
			ans[q[idq[i]].id]+=q[idq[i]].opt*BIT::query(q[idq[i]].y);
		return;
	}
	reg int mid=(lef+rig)>>1;
	BIT::Init(Y);
	reg int cntlu=0,cntru=0;
	static int idlu[MAXN],idru[MAXN];
	for(reg int i=l;i<=r;++i)
		if(u[idu[i]].x<=mid){
			BIT::update(u[idu[i]].y,u[idu[i]].p);
			idlu[++cntlu]=idu[i];
		}
		else
			idru[++cntru]=idu[i];
	for(reg int i=1;i<=cntlu;++i)
		idu[l+i-1]=idlu[i];
	for(reg int i=1;i<=cntru;++i)
		idu[r-i+1]=idru[i];
	reg int cntlq=0,cntrq=0;
	static int idlq[MAXM*4],idrq[MAXM*4];
	for(reg int i=L;i<=R;++i)
		if(q[idq[i]].x<=mid)
			idlq[++cntlq]=idq[i];
		else{
			ans[q[idq[i]].id]+=q[idq[i]].opt*BIT::query(q[idq[i]].y);
			idrq[++cntrq]=idq[i];
		}
	for(reg int i=1;i<=cntlq;++i)
		idq[L+i-1]=idlq[i];
	for(reg int i=1;i<=cntrq;++i)
		idq[R-i+1]=idrq[i];
	solve(L,L+cntlq-1,l,l+cntlu-1,lef,mid),solve(R-cntrq+1,R,r-cntru+1,r,mid+1,rig);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		u[i].x=read(),u[i].y=read(),u[i].p=read();
		Vx.push_back(u[i].x),Vy.push_back(u[i].y);
	}
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		q[++tot]=querys(1,i,x1-1,y1-1);
		q[++tot]=querys(-1,i,x1-1,y2);
		q[++tot]=querys(-1,i,x2,y1-1);
		q[++tot]=querys(1,i,x2,y2);
		Vx.push_back(x1-1),Vx.push_back(x2);
		Vy.push_back(y1-1),Vy.push_back(y2);
	}
	sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	for(reg int i=1;i<=n;++i){
		u[i].x=lower_bound(Vx.begin(),Vx.end(),u[i].x)-Vx.begin()+1;
		u[i].y=lower_bound(Vy.begin(),Vy.end(),u[i].y)-Vy.begin()+1;
	}
	for(reg int i=1;i<=tot;++i){
		q[i].x=lower_bound(Vx.begin(),Vx.end(),q[i].x)-Vx.begin()+1;
		q[i].y=lower_bound(Vy.begin(),Vy.end(),q[i].y)-Vy.begin()+1;
	}
	sort(u+1,u+n+1),sort(q+1,q+tot+1);
	for(reg int i=1;i<=n;++i)
		idu[i]=i;
	for(reg int i=1;i<=tot;++i)
		idq[i]=i;
	Y=Vy.size();
	solve(1,tot,1,n,1,Vx.size());
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}