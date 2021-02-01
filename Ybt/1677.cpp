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

const int MAXN=100+5;
const int MAXM=100+5;

int n,m;
int d[MAXN][2];
int f[MAXM];

inline bool check(reg int mid){
	static int f[MAXN];
	memset(f,-0x3f,sizeof(f));
	f[0]=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=m;j>=0;--j)
			for(reg int k=0;k<=j&&k<=mid/d[i][0];++k)
				f[j]=max(f[j],f[j-k]+(mid-d[i][0]*k)/d[i][1]);
	return f[m]>=m;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		d[i][0]=read(),d[i][1]=read();
	reg int l=0,r=1e4,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}