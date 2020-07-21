#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=500+5;
const int MAXM=500+5;

struct Node{
	long double a[MAXM];
	int cost;
	inline bool operator<(const Node& a)const{
		return cost<a.cost;
	}
};

int n,m;
Node z[MAXN];
int p[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			z[i].a[j]=read();
	for(reg int i=1;i<=n;++i)
		z[i].cost=read();
	sort(z+1,z+n+1);
	reg int cnt=0,sum=0;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=m;++j){
			if(fabs(z[i].a[j])>eps){
				if(!p[j]){
					++cnt;
					p[j]=i;
					sum+=z[i].cost;
					break;
				}
				else{
					reg long double t=z[i].a[j]/z[p[j]].a[j];
					for(reg int k=j;k<=m;++k)
						z[i].a[k]-=t*z[p[j]].a[k];
				}
			}
		}
	}
	printf("%d %d\n",cnt,sum);
	return 0;
}