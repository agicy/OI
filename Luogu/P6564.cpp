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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];

struct Node{
	int x,id;
	inline Node(reg int x=0,reg int id=0):x(x),id(id){
		return;
	}
	inline bool operator<(const Node& a)const{
		return (id-x<a.id-a.x)||((id-x==a.id-a.x)&&(id<a.id));
	}
};

Node p[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		for(reg int i=1;i<=s;++i)
			unit[i]=0;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			cMax(unit[i],val);
		return;
	}
	inline int query(reg int id){
		int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			cMax(res,unit[i]);
		return res;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		p[i]=Node(a[i],i);
	}
	sort(p+1,p+n+1);
	BIT::Init(n);
	int ans=0;
	for(reg int i=1;i<=n;++i){
		if(p[i].id-p[i].x<0)
			continue;
		reg int res=BIT::query(p[i].x-1)+1;
		BIT::update(p[i].x,res);
		cMax(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}