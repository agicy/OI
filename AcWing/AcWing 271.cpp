#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=30;

int n,a[MAXN];
ll f[MAXN][MAXN][MAXN][MAXN][MAXN];

inline ll DFS(reg int i,reg int j,reg int k,reg int l,reg int p){
	if(i+j+k+l+p==0)
		return 1;
	reg ll &tp=f[i][j][k][l][p];
	if(tp)
		return tp;
	if(i>j)
		tp+=DFS(i-1,j,k,l,p);
	if(j>k)
		tp+=DFS(i,j-1,k,l,p);
	if(k>l)
		tp+=DFS(i,j,k-1,l,p);
	if(l>p)
		tp+=DFS(i,j,k,l-1,p);
	if(p)
		tp+=DFS(i,j,k,l,p-1);
	return tp;
}

int main(void){
	while(n=read(),n){
		a[0]=a[1]=a[2]=a[3]=a[4]=0;
		for(reg int i=0;i<n;++i)
			a[i]=read();
		printf("%lld\n",DFS(a[0],a[1],a[2],a[3],a[4]));
	}
	return 0;
}
