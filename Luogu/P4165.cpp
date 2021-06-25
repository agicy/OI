#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=5e3+5;

struct Node{
	int h,v;
	ll s;
};

inline bool cmpv(const Node& a,const Node& b){
	return a.v<b.v;
}

inline bool cmps(const Node& a,const Node& b){
	return a.s<b.s;
}

int n,A,B,C;
Node a[MAXN],tmp1[MAXN],tmp2[MAXN];

int main(void){
	n=read(),A=read(),B=read(),C=read();
	for(reg int i=1;i<=n;++i){
		a[i].h=read(),a[i].v=read(),a[i].s=1ll*A*a[i].h+1ll*B*a[i].v;
		tmp1[i]=tmp2[i]=a[i];
	}
	sort(tmp1+1,tmp1+n+1,cmpv),sort(tmp2+1,tmp2+n+1,cmps);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		reg int ptr1=0,ptr2=0,cnt=0;
		reg int Min=a[i].h,Max=a[i].h+C/A;
		for(reg int j=1;j<=n;++j){
			while(ptr1<n&&tmp1[ptr1+1].v<tmp1[j].v)
				++ptr1,cnt-=(Min<=tmp1[ptr1].h&&tmp1[ptr1].h<=Max);
			while(ptr2<n&&tmp2[ptr2+1].s<=C+1ll*A*a[i].h+1ll*B*tmp1[j].v)
				++ptr2,cnt+=(Min<=tmp2[ptr2].h&&tmp2[ptr2].h<=Max);
			ans=max(ans,cnt);
		}
	}
	printf("%d\n",ans);
	return 0;
}