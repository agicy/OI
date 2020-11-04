#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=320;
const int inf=0x3f3f3f3f;

struct Matrix{
	int unit[MAXN][MAXN];
};

int n;
Matrix G;
ll ans;

inline void solve(reg int l,reg int r,const Matrix& x){
	if(l==r){
		for(reg int i=0;i<n;++i)
			if(i!=l)
				for(reg int j=0;j<n;++j)
					if(j!=l)
						ans+=(x.unit[i][j]==inf?-1:x.unit[i][j]);
		return;
	}
	reg int mid=(l+r)>>1;
	Matrix tmp=x;
	for(reg int k=l;k<=mid;++k)
		for(reg int i=0;i<n;++i)
			if(i!=k)
				for(reg int j=0;j<n;++j)
					if(i!=j&&j!=k)
						if(tmp.unit[i][k]+tmp.unit[k][j]<tmp.unit[i][j])
							tmp.unit[i][j]=tmp.unit[i][k]+tmp.unit[k][j];
	solve(mid+1,r,tmp);
	tmp=x;
	for(reg int k=mid+1;k<=r;++k)
		for(reg int i=0;i<n;++i)
			if(i!=k)
				for(reg int j=0;j<n;++j)
					if(i!=j&&j!=k)
						if(tmp.unit[i][k]+tmp.unit[k][j]<tmp.unit[i][j])
							tmp.unit[i][j]=tmp.unit[i][k]+tmp.unit[k][j];
	solve(l,mid,tmp);
	return;
}

int main(void){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);

	n=read();
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j){
			G.unit[i][j]=read();
			if(G.unit[i][j]==-1)
				G.unit[i][j]=inf;
		}
	solve(0,n-1,G);
	printf("%lld\n",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}