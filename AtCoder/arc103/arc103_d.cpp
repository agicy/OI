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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void Err(void){
	puts("-1");
	exit(0);
}

const int MAXN=1e5+5;

struct Node{
	int id;
	ll dis;
	inline Node(reg int id=0,reg ll dis=0):id(id),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
};

int n;
int siz[MAXN];
int u[MAXN],v[MAXN];
Node d[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static ll x;
		x=readll();
		d[i]=Node(i,x),siz[i]=1;
	}
	sort(d+1,d+n+1);
	reg ll sum=0;
	reg int tot=0;
	for(reg int i=n;i>1;--i){
		reg ll dis=d[i].dis-n+(siz[i]<<1);
		reg int p=lower_bound(d+1,d+1+n,Node(0,dis))-d;
		if(d[p].dis!=dis)
			Err();
		++tot;
		u[tot]=d[i].id,v[tot]=d[p].id;
		siz[p]+=siz[i];
		sum+=siz[i];
	}
	if(sum!=d[1].dis)
		Err();
	else
		for(reg int i=1;i<=tot;++i)
			printf("%d %d\n",u[i],v[i]);
	return 0;
}