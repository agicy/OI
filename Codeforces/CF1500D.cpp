#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1.5e3+4;
const int MAXQ=10+2;

int n,q;
int c[MAXN][MAXN];
int up[MAXN][MAXN][MAXQ],le[MAXN][MAXN][MAXQ];
int cl[MAXN][MAXN];
bool vis[MAXN*MAXN];
int x[MAXN][MAXN][MAXQ],y[MAXN][MAXN][MAXQ];
int ans[MAXN];

inline int getVal(reg int a,int b,reg int k){
	return max(a-x[a-1][b-1][k],b-y[a-1][b-1][k]);
}

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			c[i][j]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			le[i][j][le[i][j][0]=1]=j;
			for(reg int k=1;k<=le[i][j-1][0];++k)
				if(c[i][le[i][j-1][k]]!=c[i][j])
					le[i][j][++le[i][j][0]]=le[i][j-1][k];
			up[i][j][up[i][j][0]=1]=i;
			for(reg int k=1;k<=up[i-1][j][0];++k)
				if(c[up[i-1][j][k]][j]!=c[i][j])
					up[i][j][++up[i][j][0]]=up[i-1][j][k];
			x[i][j][1]=i,y[i][j][1]=j;
			vis[c[i][j]]=1;
			reg int ple=1,pup=1,pcl=1;
			cl[i][j]=q+1;
			for(reg int k=2;k<=q+1;++k){
				if(ple>le[i][j-1][0]&&pup>up[i-1][j][0]&&pcl>cl[i-1][j-1]){
					cl[i][j]=k-1;
					break;
				}
				reg int tmp=n;
				if(ple<=le[i][j-1][0])
					tmp=min(tmp,j-le[i][j-1][ple]);
				if(pup<=up[i-1][j][0])
					tmp=min(tmp,i-up[i-1][j][pup]);
				if(pcl<=cl[i-1][j-1])
					tmp=min(tmp,getVal(i,j,pcl));
				if(ple<=le[i][j-1][0]&&tmp==j-le[i][j-1][ple]){
					x[i][j][k]=i;
					y[i][j][k]=le[i][j-1][ple];
					++ple;
				}
				else if(pup<=up[i-1][j][0]&&tmp==i-up[i-1][j][pup]){
					x[i][j][k]=up[i-1][j][pup],y[i][j][k]=j;
					++pup;
				}
				else{
					x[i][j][k]=x[i-1][j-1][pcl],y[i][j][k]=y[i-1][j-1][pcl];
					++pcl;
				}
				if(vis[c[x[i][j][k]][y[i][j][k]]]){
					--k;
					continue;
				}
				vis[c[x[i][j][k]][y[i][j][k]]]=true;
			}
			for(reg int k=1;k<=cl[i][j];++k)
				vis[c[x[i][j][k]][y[i][j][k]]]=false;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j){
			reg int tmp=min(i,j);
			if(q<cl[i][j])
				tmp=min(tmp,max(i-x[i][j][q+1],j-y[i][j][q+1]));
			++ans[tmp];
		}
	for(reg int i=n;i>=1;--i)
		ans[i]+=ans[i+1];
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}