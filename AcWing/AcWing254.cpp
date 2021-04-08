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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int MAXXY=1e6+5;

struct Node{
	bool type;
	int x,y,t;
	inline Node(reg bool type=false,reg int x=0,reg int y=0,reg int t=0):type(type),x(x),y(y),t(t){
		return;
	}
	inline bool operator<(const Node &a)const{
		return x<a.x;
	}
};

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,tim;
	int unit[MAXXY],t[MAXXY];
	inline void Init(reg int s){
		n=s,++tim;
		return;
	}
	inline void update(reg int id,int val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			unit[i]=max(unit[i],val);
		}
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			res=max(res,unit[i]);
		}
		return res;
	}
}

int n,m;
int Maxx,Maxy;
int ans[MAXN+MAXM];
int tot,cnt;
Node Q[MAXN+MAXM],back[MAXN+MAXM];

inline void Init(void){
	int rx=0,ry=0;
	static Node tmp[MAXN+MAXM];
	cnt=0;
	for(reg int i=1;i<=tot;++i)
		if(!Q[i].type)
			rx=max(rx,Q[i].x),ry=max(ry,Q[i].y);
	for(reg int i=1;i<=tot;++i)
		if(Q[i].x<=rx&&Q[i].y<=ry)
			tmp[++cnt]=Q[i];
	for(reg int i=1;i<=cnt;++i)
		Q[i]=tmp[i];
	return;
}

inline void Solve(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	Solve(l,mid),Solve(mid+1,r);
	reg int j=l;
	BIT::Init(Maxy);
	for(reg int i=mid+1;i<=r;++i)
		if(!Q[i].type){
			while(j<=mid&&Q[j].x<=Q[i].x){
				if(Q[j].type)
					BIT::update(Q[j].y,Q[j].x+Q[j].y);
				++j;
			}
			reg int tmp=BIT::query(Q[i].y);
			if(tmp)
				ans[Q[i].t]=min(ans[Q[i].t],Q[i].x+Q[i].y-tmp);
		}
	static Node tmp[MAXN+MAXM];
	merge(Q+l,Q+mid+1,Q+mid+1,Q+r+1,tmp+l);
	for(reg int i=l;i<=r;++i)
		Q[i]=tmp[i];
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int x,y;
		x=read()+1,y=read()+1;
		++tot;
		Q[tot]=Node(true,x,y,tot);
		Maxx=max(Maxx,x),Maxy=max(Maxy,y);
	}
	while(m--){
		static int k,x,y;
		k=read(),x=read()+1,y=read()+1;
		++tot;
		Q[tot]=Node(k&1,x,y,tot);
		Maxx=max(Maxx,x),Maxy=max(Maxy,y);
	}
	for(reg int i=1;i<=tot;++i)
		back[i]=Q[i];
	memset(ans,0x3f,sizeof(ans));
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i){
		Q[i]=back[i];
		Q[i].x=Maxx-back[i].x+1;
	}
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i){
		Q[i]=back[i];
		Q[i].y=Maxy-back[i].y+1;
	}
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i){
		Q[i]=back[i];
		Q[i].x=Maxx-back[i].x+1;
		Q[i].y=Maxy-back[i].y+1;
	}
	Init();
	Solve(1,cnt);
	for(reg int i=1;i<=tot;++i)
		if(!back[i].type)
			writeln(ans[i]);
	flush();
	return 0;
}