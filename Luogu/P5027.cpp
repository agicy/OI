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
const double eps=1e-6;

int n;
int M[MAXN][MAXN];
double G[MAXN][MAXN];

inline int Gauss(void){
	for(reg int i=1;i<=n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=n;++j)
			if(fabs(G[j][i])>fabs(G[Max][i]))
				Max=j;
		if(i!=Max)
			for(reg int j=1;j<=n+1;++j)
				swap(G[i][j],G[Max][j]);
		if(fabs(G[i][i])<eps)
			return -1;
		for(reg int j=1;j<=n;++j)
			if(i!=j){
				reg double d=G[j][i]/G[i][i];
				for(reg int k=1;k<=n+1;++k)
					G[j][k]-=d*G[i][k];
			}
	}
	reg int pos=0,Max=0;
	reg bool flag=true;
	for(reg int i=1;i<=n;++i){
		reg double val=G[i][n+1]/G[i][i];
		if(ceil(val)-floor(val)>eps||val<eps)
			return -1;
		reg int S=val;
		if(Max<S){
			Max=S,pos=i;
			flag=false;
		}
		else if(Max==S)
			flag=true;
	}
	return flag?-1:pos;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n+1;++i){
		static int m;
		m=read();
		for(reg int j=1;j<=m;++j){
			static int id;
			id=read();
			M[i][id]=1;
		}
		M[i][n+1]=read();
	}
	reg int ans=-1;
	for(reg int i=1;i<=n+1;++i){
		reg int tot=0;
		for(reg int j=1;j<=n+1;++j)
			if(i!=j){
				++tot;
				for(reg int k=1;k<=n+1;++k)
					G[tot][k]=M[j][k];
			}
		reg int res=Gauss();
		if(res!=-1&&ans!=-1){
			ans=-1;
			break;
		}
		else if(res!=-1)
			ans=res;
	}
	if(ans==-1)
		puts("illegal");
	else
		printf("%d\n",ans);
	return 0;
}