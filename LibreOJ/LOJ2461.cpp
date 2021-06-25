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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5;
const int MAXM=1e5;
const int MAXA=1e5;
const int inf=0x3f3f3f3f;

struct Interval{
	int l,r;
	inline Interval(reg int l=inf,reg int r=-inf):l(l),r(r){
		return;
	}
	inline bool in(reg int x){
		return l<=x&&x<=r;
	}
	inline bool contain(const Interval& a)const{
		return l<=a.l&&a.r<=r;
	}
	inline bool cap(const Interval& a)const{
		return l<=a.r&&a.l<=r;
	}
};

struct updates{
	Interval inv;
	int val,f;
};

struct Event{
	int tim,pos,val;
	inline Event(reg int tim=0,reg int pos=0,reg int val=0):tim(tim),pos(pos),val(val){
		return;
	}
	inline bool operator<(const Event& a)const{
		return tim<a.tim;
	}
};

int n,m;
int a[MAXN];
updates up[MAXM];
int tmp[MAXN];

inline void update(reg int l,reg int r,reg int val,const updates& up,reg int& tot,reg int& Max){
	if(up.inv.contain(Interval(l,r)))
		tot+=val;
	else if(up.inv.cap(Interval(l,r))){
		for(reg int lef=max(l,up.inv.l),rig=min(r,up.inv.r),i=lef;i<=rig;++i)
			tmp[i]-=val;
		Max=*max_element(tmp+l,tmp+r+1);
	}
	return;
}

int sum[MAXM],cov[MAXM],ncov[MAXM],pos[MAXM];

inline void solve(reg int l,reg int r){
	for(reg int i=l;i<=r;++i)
		tmp[i]=a[i];
	int tot=0,Max=*max_element(tmp+l,tmp+r+1);
	reg int cntC=0,cntnC=0;
	for(reg int lef=0,rig=0;lef<m;++lef){
		update(l,r,-1,up[lef],tot,Max);
		while(rig<m&&Max>tot)
			update(l,r,1,up[rig++],tot,Max);
		if(rig==m&&Max>tot)
			++rig;
		sum[lef]=sum[lef-1];
		if(up[lef].inv.contain(Interval(l,r))){
			cov[cntC++]=lef,++sum[lef];
			up[lef].f=max(up[lef].f,rig-1);
		}
		else if(up[lef].inv.cap(Interval(l,r))){
			ncov[cntnC]=lef,pos[cntnC]=cntC-1;
			++cntnC;
		}
	}
	for(reg int i=l;i<=r;++i){
		reg int val=a[i];
		for(reg int lef=0,rig=0;lef<cntnC;++lef){
			val+=sum[ncov[lef]]-sum[ncov[lef-1]];
			if(up[ncov[lef]].inv.in(i)){
				++val;
				while(rig<cntnC&&val>0){
					val-=sum[ncov[rig]]-sum[ncov[rig-1]];
					if(up[ncov[rig]].inv.in(i))
						--val;
					++rig;
				}
				if(val>0)
					if(sum[m-1]-sum[ncov[rig-1]]>=val)
						up[ncov[lef]].f=max(up[ncov[lef]].f,cov[pos[rig-1]+val]);
					else
						up[ncov[lef]].f=max(up[ncov[lef]].f,m);
				else
					if(up[ncov[rig-1]].inv.in(i))
						if(val)
							up[ncov[lef]].f=max(up[ncov[lef]].f,cov[pos[rig-1]+val+1]);
						else
							up[ncov[lef]].f=max(up[ncov[lef]].f,ncov[rig-1]);
					else
						up[ncov[lef]].f=max(up[ncov[lef]].f,cov[pos[rig-1]+val]);
			}
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	for(reg int i=0;i<m;++i)
		up[i].inv.l=read()-1,up[i].inv.r=read()-1,up[i].val=read()-1;
	reg int B=max(10,int(sqrt(n))),tot=(n+B-1)/B;
	for(reg int i=0;i<tot;++i)
		solve(i*B,min((i+1)*B,n)-1);
	reg int etot=0;
	static Event e[MAXM<<1];
	for(reg int i=0;i<m;++i)
		e[etot++]=Event(i,up[i].val,1),e[etot++]=Event(up[i].f,up[i].val,-1);
	sort(e,e+etot);
	reg int ans=0;
	static int T[MAXA];
	for(reg int i=0,ptr=0;i<m;++i){
		while(ptr<etot&&e[ptr].tim<=i){
			if(e[ptr].val==1){
				if(!T[e[ptr].pos]++)
					++ans;
			}
			else{
				if(!--T[e[ptr].pos])
					--ans;
			}
			++ptr;
		}
		writeln(ans);
	}
	flush();
	return 0;
}