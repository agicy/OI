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

const int MAXN=3e5+5;
const int MAXM=3e5+5;
const int MAXSQRTN=548+1;

struct querys{
	int id,t,k;
	inline bool operator<(const querys& a)const{
		return k<a.k;
	}
};

int n,m;
querys q[MAXM];
int a[MAXN];
ll f[MAXN];
ll ans[MAXM];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	m=read();
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].t=read(),q[i].k=read();
	reg int B=sqrt(n);
	sort(q+1,q+m+1);
	for(reg int i=1,las=0;i<=m;++i)
		if(q[i].k<=B){
			if(q[i].k!=las){
				las=q[i].k;
				for(reg int j=n;j>=1;--j)
					if(las+j<=n)
						f[j]=f[j+las]+a[j];
					else
						f[j]=a[j];
			}
			ans[q[i].id]=f[q[i].t];
		}
		else{
			reg ll sum=0;
			for(reg int j=q[i].t;j<=n;j+=q[i].k)
				sum+=a[j];
			ans[q[i].id]=sum;
		}
	for(reg int i=1;i<=m;++i)
		printf("%lld\n",ans[i]);
	return 0;
}