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

const int MAXN=2e5+5;

int n;
int Max;
int las[MAXN];

struct Node{
	int t,w;
	inline bool operator<(const Node& a)const{
		return w>a.w;
	}
};

Node a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i].t=read(),a[i].w=read();
		Max=max(Max,a[i].t);
	}
	sort(a+1,a+n+1);
	for(reg int i=1;i<=Max;++i)
		las[i]=i;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		if(las[a[i].t]){
			ans+=a[i].w;
			las[a[i].t]=las[las[a[i].t]-1];
		}
	printf("%lld\n",ans);
	return 0;
}