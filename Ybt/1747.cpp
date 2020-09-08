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

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

namespace ST{
	int Lg[MAXN];
	int Max[MAXN][MAXLOG2N],pMax[MAXN][MAXLOG2N];
	int Min[MAXN][MAXLOG2N],pMin[MAXN][MAXLOG2N];
	inline void Init(reg int n,reg int a[]){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Max[i][0]=Min[i][0]=a[i],pMax[i][0]=pMin[i][0]=i;
		for(reg int j=1;j<MAXLOG2N;++j){
			for(reg int i=1;i+(1<<j)-1<=n;++i){
				if(Max[i][j-1]>=Max[i+(1<<(j-1))][j-1])
					Max[i][j]=Max[i][j-1],pMax[i][j]=pMax[i][j-1];
				else
					Max[i][j]=Max[i+(1<<(j-1))][j-1],pMax[i][j]=pMax[i+(1<<(j-1))][j-1];
				if(Min[i+(1<<(j-1))][j-1]<=Min[i][j-1])
					Min[i][j]=Min[i+(1<<(j-1))][j-1],pMin[i][j]=pMin[i+(1<<(j-1))][j-1];
				else
					Min[i][j]=Min[i][j-1],pMin[i][j]=pMin[i][j-1];
			}
		}
		return;
	}
	inline int query_pMin(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		reg int left=Min[l][k],right=Min[r-(1<<k)+1][k];
		if(right<=left)
			return pMin[r-(1<<k)+1][k];
		else
			return pMin[l][k];
	}
	inline int query_pMax(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		reg int left=Max[l][k],right=Max[r-(1<<k)+1][k];
		if(left>=right)
			return pMax[l][k];
		else
			return pMax[r-(1<<k)+1][k];
	}
}

int n;
int h[MAXN];
int ans;

inline void Solve(reg int l,reg int r){
	if(l>r||l==r)
		return;
	reg int pMin=ST::query_pMin(l,r),pMax=ST::query_pMax(l,r);
	if(pMax<pMin)
		Solve(l,pMax),Solve(pMax+1,pMin-1),Solve(pMin,r);
	else{
		ans=max(ans,pMax-pMin+1);
		Solve(l,pMin-1),Solve(pMax+1,r);
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	ST::Init(n,h);
	Solve(1,n);
	printf("%d\n",ans);
	return 0;
}