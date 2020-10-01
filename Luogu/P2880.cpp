#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e4+5;
const int MAXLOG2N=16+1;

int n,q;
int h[MAXN];

namespace ST{
	int Lg[MAXN];
	int Max[MAXLOG2N][MAXN],Min[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Max[0][i]=Min[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i){
				Max[j][i]=max(Max[j-1][i],Max[j-1][i+(1<<(j-1))]);
				Min[j][i]=min(Min[j-1][i],Min[j-1][i+(1<<(j-1))]);
			}
		return;
	}
	inline int queryMax(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		return max(Max[k][l],Max[k][r-(1<<k)+1]);
	}
	inline int queryMin(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	ST::Init(n,h);
	while(q--){
		static int a,b;
		a=read(),b=read();
		printf("%d\n",ST::queryMax(a,b)-ST::queryMin(a,b));
	}
	return 0;
}