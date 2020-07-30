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

const int MAXN=50+5;
const int MAXM=4e3+5;

int n,m;
int f[MAXN][MAXN][MAXM],pre[MAXN][MAXN][MAXM],Max[MAXN][MAXN][MAXM];
int g[MAXN][MAXM];
int a[MAXM],b[MAXM],c[MAXM];
int ans[MAXM];
vector<int> V;

inline void query(reg int l,reg int r,int k){
	if(l>r)
		return;
	k=pre[l][r][k];
	reg int pos=f[l][r][k];
	ans[pos]=V[k-1];
	query(l,pos-1,k),query(pos+1,r,k);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		a[i]=read(),b[i]=read(),c[i]=read();
		V.push_back(c[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=m;++i)
		c[i]=lower_bound(V.begin(),V.end(),c[i])-V.begin()+1;
	reg int tot=V.size();
	for(reg int i=n;i>=1;--i)
		for(reg int j=i;j<=n;++j){
			for(reg int k=i;k<=j;++k)
				for(reg int l=0;l<=tot;++l)
					g[k][l]=0;
			for(reg int k=1;k<=m;++k)
				if(i<=a[k]&&b[k]<=j)
					for(reg int l=a[k];l<=b[k];++l)
						++g[l][c[k]];
			for(reg int k=i;k<=j;++k)
				for(reg int l=tot-1;l>=1;--l)
					g[k][l]+=g[k][l+1];
			for(reg int k=tot;k>=1;--k){
				reg int _Max=0;
				for(reg int l=i;l<=j;++l){
					reg int w=Max[i][l-1][k]+Max[l+1][j][k]+g[l][k]*V[k-1];
					if(_Max<=w)
						_Max=w,f[i][j][k]=l;
				}
				if(_Max>=Max[i][j][k+1])
					Max[i][j][k]=_Max,pre[i][j][k]=k;
				else
					Max[i][j][k]=Max[i][j][k+1],pre[i][j][k]=pre[i][j][k+1];
			}
		}
	query(1,n,1);
	printf("%d\n",Max[1][n][1]);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}