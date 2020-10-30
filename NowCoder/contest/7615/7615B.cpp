#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5000+5;
const int MAXM=4000+5;
const int MAXLOG2M=11+3;
const int inf=0x3f3f3f3f;

int n,m,k;
int l[MAXN];
int Min[MAXM][MAXLOG2M];
int Lg[MAXM];

inline int query(int l,int r){
	if(l>r)
		return inf;
	int k=Lg[r-l+1];
	return min(Min[l][k],Min[r-(1<<k)+1][k]);
}

int c[MAXN][MAXM];
int add[MAXN][MAXM];

int main(void){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;++i)
		read(),l[i]=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			c[i][j]=read();
	Lg[0]=-1;
	for(int i=1;i<=m*2;++i)
		Lg[i]=Lg[i>>1]+1;
	for(int i=1;i<=n;++i){
		static int tmp[MAXM*2];
		for(int j=1;j<=m;++j)
			tmp[j]=tmp[j+m]=c[i][j];
		for(int j=1;j<=m*2;++j)
			Min[j][0]=tmp[j];
		for(int j=1;j<=MAXLOG2M;++j)
			for(int i=1;i+(1<<j)-1<=m*2;++i)
				Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
		for(int j=1;j<=m;++j){
			int L=j,R=L+k-1;
			if(R<=m)
				L+=m;
			else
				R-=m;
			add[i][j]=query(R+1,L-l[i]);
		}
	}
	ll ans=inf;
	for(int i=1;i<=m;++i){
		ll sum=0;
		for(int j=1;j<=n;++j)
			sum+=add[j][i];
		ans=min(ans,sum);
	}
	if(ans>=inf)
		puts("-1");
	else
		printf("%lld\n",ans);
	return 0;
}