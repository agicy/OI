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
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e5+5;
const int MAXLOG2N=18+1;

namespace ST{
	int lg[MAXN];
	int Max[MAXLOG2N][MAXN],Min[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[],reg int b[]){
		lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			lg[i]=lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Max[0][i]=a[i],Min[0][i]=b[i];
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i){
				Max[j][i]=max(Max[j-1][i],Max[j-1][i+(1<<(j-1))]);
				Min[j][i]=min(Min[j-1][i],Min[j-1][i+(1<<(j-1))]);
			}
		return;
	}
	inline int queryMax(reg int l,reg int r){
		reg int k=lg[r-l+1];
		return max(Max[k][l],Max[k][r-(1<<k)+1]);
	}
	inline int queryMin(reg int l,reg int r){
		reg int k=lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

int n;
int a[MAXN],b[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	ST::Init(n,a,b);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		reg int lef=-1,rig=-1;
		reg int l,r,mid;
		l=i,r=n;
		while(l<=r){
			mid=(l+r)>>1;
			if(ST::queryMax(i,mid)>ST::queryMin(i,mid))
				r=mid-1;
			else if(ST::queryMax(i,mid)==ST::queryMin(i,mid))
				lef=mid,r=mid-1;
			else
				l=mid+1;
		}
		l=i,r=n;
		while(l<=r){
			mid=(l+r)>>1;
			if(ST::queryMax(i,mid)>ST::queryMin(i,mid))
				r=mid-1;
			else if(ST::queryMax(i,mid)==ST::queryMin(i,mid))
				rig=mid,l=mid+1;
			else
				l=mid+1;
		}
		if(lef!=-1&&rig!=-1)
			ans+=rig-lef+1;
	}
	printf("%lld\n",ans);
	return 0;
}