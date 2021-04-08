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

const int MAXN=1e5+5;
const int MAXK=2e5+5;

struct Node{
	int x,y,z,cnt,ans;
	inline void Read(void){
		x=read(),y=read(),z=read();
		return;
	}
};

inline bool cmpx(const Node& a,const Node& b){
	return a.x==b.x?(a.y==b.y?(a.z<b.z):a.y<b.y):a.x<b.x;
}

inline bool cmpy(const Node& a,const Node& b){
	return a.y==b.y?a.z<b.z:a.y<b.y;
}

int n,m,K;
Node a[MAXN],b[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,tim;
	int unit[MAXK],t[MAXK];
	inline void Init(reg int s){
		n=s,++tim;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			unit[i]+=val;
		}
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			res+=unit[i];
		}
		return res;
	}
}

int cnt[MAXN];

inline void solve(reg int l,reg int r,reg Node a[]){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	solve(l,mid,a),solve(mid+1,r,a);
	sort(a+l,a+mid+1,cmpy),sort(a+mid+1,a+r+1,cmpy);
	BIT::Init(K);
	reg int j=l;
	for(reg int i=mid+1;i<=r;++i){
		while(j<=mid&&a[j].y<=a[i].y)
			BIT::update(a[j].z,a[j].cnt),++j;
		a[i].ans+=BIT::query(a[i].z);
	}
	return;
}

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	sort(a+1,a+n+1,cmpx);
	reg int sum=0;
	for(reg int i=1;i<=n;++i){
		++sum;
		if(a[i].x!=a[i+1].x||a[i].y!=a[i+1].y||a[i].z!=a[i+1].z)
			b[++m]=a[i],b[m].cnt=sum,sum=0;
	}
	solve(1,m,b);
	for(reg int i=1;i<=m;++i)
		cnt[b[i].ans+b[i].cnt-1]+=b[i].cnt;
	for(reg int i=0;i<n;++i)
		writeln(cnt[i]);
	flush();
	return 0;
}