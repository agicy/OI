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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e6+5;
const __int128 inf=0x3f3f3f3f3f3f3f3f;

struct Node{
	__int128 sum,lMax,rMax,Max;
	inline Node(reg ll val=0):sum(val),lMax(val),rMax(val),Max(val){
		return;
	}
};

inline Node operator+(const Node& a,const Node& b){
	Node res;
	res.sum=a.sum+b.sum;
	res.lMax=max(a.lMax,a.sum+b.lMax);
	res.rMax=max(b.rMax,b.sum+a.rMax);
	res.Max=max(a.rMax+b.lMax,max(a.Max,b.Max));
	return res;
}

int n,p;
int a[MAXN];
__int128 val[MAXN];

int main(void){
	n=read(),p=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	Node tmp=Node(a[1]);
	__int128 Max=a[1]+a[1];
	val[1]=a[1];
	for(reg int i=2;i<=n;++i){
		tmp=tmp+Node(a[i]);
		val[i]=Max;
		Max=max(Max,tmp.Max+val[i]);
	}
	__int128 ans=-inf;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,val[i]);
	int abs=(ans<0?-ans:ans)%p;
	if(ans<0)
		printf("-%d\n",abs);
	else
		printf("%d\n",abs);
	return 0;
}