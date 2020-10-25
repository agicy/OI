#include<cstdio>
#include<algorithm>
using std::min;
#include<vector>
using std::vector;
#define reg register
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

const int MAXN=600+5;
const int MAXM=(MAXN*(MAXN-1))>>1;

int n,m;
int u[MAXM],v[MAXM];
double P[MAXN];
double E[MAXN][MAXN];
vector<int> V[MAXN];

int main(void){
	reg int i,j,k,size;
	reg double ans;
	n=read(),m=read();
	for(i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		V[u[i]].push_back(v[i]);
	}
	for(i=n-1;i>=1;--i){
		P[i]=1;
		size=V[i].size();
		for(j=0;j<size;++j)
			P[i]+=P[V[i][j]]/size;
	}
	for(i=1;i<=n-1;++i){
		if(V[i].size()==1u)
			continue;
		E[i][i]=1;
		for(j=i-1;j>=1;--j){
			size=V[j].size();
			for(k=0;k<size;++k)
				E[j][i]+=E[V[j][k]][i]/size;
		}
	}
	ans=P[1];
	for(i=1;i<=m;++i){
		if(V[u[i]].size()==1)
			continue;
		double newf=(P[u[i]]*V[u[i]].size()-P[v[i]]-1)/(V[u[i]].size()-1);
		ans=min((double)ans,P[1]+E[1][u[i]]*(newf-P[u[i]]));
	}
	printf("%.10f\n",ans);
	return 0;
}