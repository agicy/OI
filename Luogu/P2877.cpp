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

const int MAXN=5e4+5;
const double eps=1e-5;

struct Node{
	int t,p;
	inline bool operator<(const Node& a)const{
		return 1ll*t*a.p<1ll*a.t*p;
	}
};

int n;
Node a[MAXN];
double sum[MAXN];
int ans[MAXN];

inline bool check(reg double r,reg int cnt){
	for(reg int i=1;i<=n;++i)
		sum[i]=a[i].t-a[i].p*r;
	sort(sum+1,sum+n+1);
	reg double res=0;
	for(reg int i=n;i>=n-cnt+1;--i)
		res+=sum[i];
	return res>eps;
}

int main(void){
	n=read();
	reg int sumt=0,sump=0;
	for(reg int i=1;i<=n;++i){
		a[i].t=read(),a[i].p=read();
		sumt+=a[i].t,sump+=a[i].p;
	}
	sort(a+1,a+n+1);
	reg int tot=0;
	for(reg int i=1;i<n;++i){
		sumt-=a[i].t,sump-=a[i].p;
		reg double r=1.0*sumt/sump;
		if(check(r,n-i))
			ans[++tot]=i;
	}
	printf("%d\n",tot);
	for(reg int i=1;i<=tot;++i)
		printf("%d\n",ans[i]);
	return 0;
}