#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define eps 1e-6
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=12+5;

int n,m;
double G[MAXN][MAXN];

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

inline void Gauss(void){
	--n;
	for(reg int i=1;i<=n;++i){
		int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(sgn(G[Max][i]-G[j][i])<0)
				Max=j;
		if(Max!=i)
			swap(G[i],G[Max]);
		if(!G[i][i]){
			puts("0");
			return;
		}
		for(reg int j=i+1;j<=n;++j){
			reg double t=G[j][i]/G[i][i];
			for(reg int k=i;k<=n+1;++k)
				G[j][k]-=t*G[i][k];
		}
	}
	reg double ans=1;
	for(reg int i=1;i<=n;++i)
		ans=ans*G[i][i];
	printf("%.0lf\n",ans);
	return;
}

int main(void){
	reg int T=read();
	while(T--){
		memset(G,0,sizeof(G));
		n=read(),m=read();
		for(reg int i=1;i<=m;++i){
			static int a,b;
			a=read(),b=read();
			G[a][a]+=1,G[b][b]+=1;
			G[a][b]-=1,G[b][a]-=1;
		}
		Gauss();
	}
	return 0;
}