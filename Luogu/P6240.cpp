#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=4e4+5;
const int MAXM=2e5+5;
const int MAXT=200+1;

int n,m;
int h[MAXN],w[MAXN];
int id[MAXM],lef[MAXM],rig[MAXM],t[MAXM];
int ans[MAXM];
int f[MAXN][MAXT];

inline void solve(reg int L,reg int R,reg int l,reg int r){
	if(L>R||l>r)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			ans[id[i]]=(h[l]<=t[id[i]])?w[l]:0;
		return;
	}
	reg int mid=(l+r)>>1;
	for(reg int i=0;i<=200;++i)
		f[mid][i]=(h[mid]<=i)?w[mid]:0;
	for(reg int i=mid-1;i>=l;--i)
		for(reg int j=0;j<=200;++j)
			if(j>=h[i])
				f[i][j]=max(f[i+1][j],f[i+1][j-h[i]]+w[i]);
			else
				f[i][j]=f[i+1][j];
	for(reg int i=0;i<=200;++i)
		f[mid+1][i]=(h[mid+1]<=i)?w[mid+1]:0;
	for(reg int i=mid+2;i<=r;++i)
		for(reg int j=0;j<=200;++j)
			if(j>=h[i])
				f[i][j]=max(f[i-1][j],f[i-1][j-h[i]]+w[i]);
			else
				f[i][j]=f[i-1][j];
	reg int cntl=0,cntr=0;
	static int idl[MAXM],idr[MAXM];
	for(reg int i=L;i<=R;++i)
		if(lef[id[i]]<=mid&&mid<rig[id[i]])
			for(reg int j=0;j<=t[id[i]];++j)
				ans[id[i]]=max(ans[id[i]],f[lef[id[i]]][j]+f[rig[id[i]]][t[id[i]]-j]);
		else if(lef[id[i]]<=mid)
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
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=1;i<=m;++i)
		id[i]=i,lef[i]=read(),rig[i]=read(),t[i]=read();
	solve(1,m,1,n);
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}