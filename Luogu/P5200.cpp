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

const int MAXN=1e5+5;

int n;
int p[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id){
		for(reg int i=id;i<=n;i+=lowbit(i))
			++unit[i];
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	reg int ptr=n;
	while(ptr>1&&p[ptr-1]<p[ptr])
		--ptr;
	BIT::Init(n);
	for(reg int i=ptr;i<=n;++i)
		BIT::update(p[i]);
	printf("%d\n",ptr-1);
	for(reg int i=1;i<ptr;++i){
		printf("%d%c",ptr-i-1+BIT::query(p[i]-1),i==ptr-1?'\n':' ');
		BIT::update(p[i]);
	}
	return 0;
}