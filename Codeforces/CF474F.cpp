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

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int MAXN=1e5+5;
const int MAXT=1e5+5;

struct querys{
	int l,r;
	inline querys(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
};

int n,t;
int s[MAXN];
int id[MAXT];
querys q[MAXT];
int ans[MAXT];
int d[MAXN],cnt[MAXN];

inline void solve(reg int L,reg int R,reg int l,reg int r){
	if(L>R||l>r)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			ans[id[i]]=0;
		return;
	}
	reg int mid=(l+r)>>1;
	d[mid]=s[mid],cnt[mid]=1;
	for(reg int i=mid-1;i>=l;--i){
		d[i]=gcd(d[i+1],s[i]),cnt[i]=(s[i]==d[i]);
		if(d[i]==d[i+1])
			cnt[i]+=cnt[i+1];
	}
	d[mid+1]=s[mid+1],cnt[mid+1]=1;
	for(reg int i=mid+2;i<=r;++i){
		d[i]=gcd(d[i-1],s[i]),cnt[i]=(s[i]==d[i]);
		if(d[i]==d[i-1])
			cnt[i]+=cnt[i-1];
	}
	reg int cntl=0,cntr=0;
	static int idl[MAXT],idr[MAXT];
	for(reg int i=L;i<=R;++i)
		if(q[id[i]].l<=mid&&mid<q[id[i]].r){
			reg int x=gcd(d[q[id[i]].l],d[q[id[i]].r]),val=0;
			if(x==d[q[id[i]].l])
				val+=cnt[q[id[i]].l];
			if(x==d[q[id[i]].r])
				val+=cnt[q[id[i]].r];
			ans[id[i]]=(q[id[i]].r-q[id[i]].l+1)-val;
		}
		else if(q[id[i]].r<=mid)
			idl[++cntl]=id[i];
		else
			idr[++cntr]=id[i];
	for(reg int i=1;i<=cntl;++i)
		id[L+i-1]=idl[i];
	for(reg int i=1;i<=cntr;++i)
		id[R-i+1]=idr[i];
	solve(L,L+cntl-1,l,mid),solve(R-cntr+1,R,mid+1,r);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		s[i]=read();
	t=read();
	for(reg int i=1;i<=t;++i)
		id[i]=i,q[i].l=read(),q[i].r=read();
	solve(1,t,1,n);
	for(reg int i=1;i<=t;++i)
		writeln(ans[i]);
	flush();
	return 0;
}