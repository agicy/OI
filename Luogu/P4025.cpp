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

const int MAXN=1e5+5;

struct Node{
	int d,a,id;
	inline bool operator<(const Node& x)const{
		if(1ll*(a-d)*(x.a-x.d)<0)
			return a-d>0;
		else if(a-d<0)
			return a>x.a;
		else
			return d<x.d;
	}
};

int n;
Node a[MAXN];

int main(void){
	reg ll sum=0;
	n=read(),sum+=read();
	for(reg int i=1;i<=n;++i)
		a[i].id=i,a[i].d=read(),a[i].a=read();
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i){
		if(sum<=a[i].d){
			puts("NIE");
			return 0;
		}
		sum+=a[i].a-a[i].d;
	}
	puts("TAK");
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i].id,i==n?'\n':' ');
	return 0;
}