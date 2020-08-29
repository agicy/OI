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

const int MAXN=1e6+5;
const int MAXLOG2N=20+1;
const int inf=0x3f3f3f3f;

int n,x;
int a[MAXN];

namespace ST{
	int Lg[MAXN];
	int Min[MAXLOG2N][MAXN],pMin[MAXLOG2N][MAXN];
	int Max[MAXLOG2N][MAXN],pMax[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i){
			Lg[i]=Lg[i>>1]+1;
		}
		for(reg int i=1;i<=n;++i){
			Max[0][i]=Min[0][i]=a[i];
			pMax[0][i]=pMin[0][i]=i;
		}
		for(reg int j=1;j<MAXLOG2N;++j){
			for(reg int i=1;i+(1<<j)-1<=n;++i){
				if(Max[j-1][i]<Max[j-1][i+(1<<(j-1))])
					Max[j][i]=Max[j-1][i+(1<<(j-1))],pMax[j][i]=pMax[j-1][i+(1<<(j-1))];
				else
					Max[j][i]=Max[j-1][i],pMax[j][i]=pMax[j-1][i];
				if(Min[j-1][i]>Min[j-1][i+(1<<(j-1))])
					Min[j][i]=Min[j-1][i+(1<<(j-1))],pMin[j][i]=pMin[j-1][i+(1<<(j-1))];
				else
					Min[j][i]=Min[j-1][i],pMin[j][i]=pMin[j-1][i];
			}
		}
		return;
	}
	inline pair<int,int> queryMax(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		int vl=Max[k][l],pl=pMax[k][l],vr=Max[k][r-(1<<k)+1],pr=pMax[k][r-(1<<k)+1];
		if(vl<vr)
			return make_pair(vr,pr);
		else
			return make_pair(vl,pl);
	}
	inline pair<int,int> queryMin(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		int vl=Min[k][l],pl=pMin[k][l],vr=Min[k][r-(1<<k)+1],pr=pMin[k][r-(1<<k)+1];
		if(vl<vr)
			return make_pair(vl,pl);
		else
			return make_pair(vr,pr);
	}
}

inline ll Solve(reg int l,reg int r){
	if(l>r)
		return 0;
	pair<int,int> Max=ST::queryMax(l,r),Min=ST::queryMin(l,r);
	reg int vMax=Max.first,vMin=Min.first;
	reg int pMax=Max.second,pMin=Min.second;
	reg ll sum=0;
	if(vMin*2>x)
		return 0;
	if(vMax*2<x)
		return 0;
	if(vMax+vMin==x){
		if(pMax<pMin)
			sum+=1ll*(pMax-l+1)*(r-pMin+1)+Solve(l,pMin-1)+Solve(pMax+1,r)-Solve(pMax+1,pMin-1);
		else
			sum+=1ll*(r-pMax+1)*(pMin-l+1)+Solve(l,pMax-1)+Solve(pMin+1,r)-Solve(pMin+1,pMax-1);
	}
	else if(vMax+vMin<x)
		sum+=Solve(pMin+1,r)+Solve(l,pMin-1);
	else if(vMax+vMin>x)
		sum+=Solve(l,pMax-1)+Solve(pMax+1,r);
	return sum;
}

int main(void){
	freopen("interval.in","r",stdin);
	freopen("interval.out","w",stdout);
	n=read(),x=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	ST::Init(n,a);
	printf("%lld\n",Solve(1,n));
	return 0;
}