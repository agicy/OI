#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e6+5;

int n,m;
int sa[MAXN],rnk[MAXN];
int v[MAXN];
priority_queue<int> Q;

bool ed;

int main(void){
	n=read(),m=read()-1;
	for(reg int i=1;i<=n;++i)
		rnk[sa[i]=read()]=i;
	for(reg int i=1;i<=n;++i)
		v[i]=read()-1;
	reg int cnt=0;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		if(i>1&&rnk[sa[i]+1]<rnk[sa[i-1]+1])
			++cnt;
		reg int val=v[sa[i]];
		val-=cnt,ans+=abs(val),val=max(val,0);
		Q.push(val),Q.push(val),Q.pop();
	}
	if(cnt>m)
		puts("-1");
	else{
		while(!Q.empty())
			ans-=Q.top(),Q.pop();
		printf("%lld\n",ans);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}