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

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int MAXN=5e5+5;

struct Node{
	int w,len,l,r;
	inline Node(reg int w=0,reg int len=0,reg int l=0,reg int r=0):w(w),len(len),l(l),r(r){
		return;
	}
};

inline void update(Node p[],reg int& cnt){
	reg int tot;
	tot=0;
	for(reg int j=1;j<=cnt;++j)
		if(j==1||p[j].w!=p[j-1].w){
			++tot;
			p[tot]=Node(p[j].w,p[j].len,p[tot-1].r+1,p[tot-1].r+p[j].len);
		}
		else
			p[tot].len+=p[j].len,p[tot].r+=p[j].len;
	cnt=tot;
	return;
}

int n,k;
int a[MAXN];
int cnt1;
Node p[MAXN];
int cnt2;
Node q[MAXN];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=cnt1;++j)
			p[j].w=gcd(p[j].w,a[i]);
		p[++cnt1]=Node(a[i],1,i,i);
		update(p,cnt1);
		for(reg int j=1;j<=cnt2;++j)
			q[j].w|=a[i];
		q[++cnt2]=Node(a[i],1,i,i);
		update(q,cnt2);
		static int lef[1<<19],rig[1<<19];
		for(reg int j=1;j<=cnt1;++j)
			lef[p[j].w]=p[j].l,rig[p[j].w]=p[j].r;
		for(reg int j=1;j<=cnt2;++j){
			reg int x=q[j].w^k;
			if(!lef[x])
				continue;
			ans+=max(0,min(q[j].r,rig[x])-max(q[j].l,lef[x])+1);
		}
		for(reg int j=1;j<=cnt1;++j)
			lef[p[j].w]=rig[p[j].w]=0;
	}
	printf("%lld\n",ans);
	return 0;
}