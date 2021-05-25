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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m,k;
int a[MAXN];
int lef[MAXN],rig[MAXN],blk[MAXN];

struct querys{
	int id,l,r;
	ll ans;
	inline bool operator<(const querys& a)const{
		return blk[l]==blk[a.l]?r<a.r:l<a.l;
	}
};

querys q[MAXM];
ll ans[MAXM];
int T[16384];

int main(void){
	n=read(),m=read(),k=read();
	if(k>14){
		for(reg int i=1;i<=m;++i)
			writeln(0);
	}
	else{
		vector<int> V;
		for(reg int i=0;i<(1<<14);++i)
			if(__builtin_popcount(i)==k)
				V.push_back(i);
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		reg int B=,tot=(n+B-1)/B;
		for(reg int i=1;i<=tot;++i){
			lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
			for(reg int j=lef[i];j<=rig[i];++j)
				blk[j]=i;
		}
		for(reg int i=1;i<=m;++i)
			q[i].id=i,q[i].l=read(),q[i].r=read();
		sort(q+1,q+m+1);

		

		for(reg int i=1;i<=m;++i)
			q[i].ans+=q[i-1].ans;
		for(reg int i=1;i<=m;++i)
			ans[q[i].id]=q[i].ans;
		for(reg int i=1;i<=m;++i)
			writeln(ans[i]);
	}
	flush();
	return 0;
}