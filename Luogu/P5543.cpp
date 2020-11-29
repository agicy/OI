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

int n,m;

namespace UnionFind{
	int fa[MAXN<<1];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int main(void){
	n=read(),m=read();
	UnionFind::Init(n<<1);
	for(reg int i=1;i<=m;++i){
		static char opt;
		static int a,b;
		do
			opt=getchar();
		while(!isalpha(opt));
		a=read(),b=read();
		switch(opt){
			case 'S':{
				UnionFind::merge(a,b);
				UnionFind::merge(a+n,b+n);
				break;
			}
			case 'D':{
				UnionFind::merge(a,b+n);
				UnionFind::merge(a+n,b);
				break;
			}
		}
	}
	reg bool f=false;
	for(reg int i=1;i<=n;++i)
		if(UnionFind::search(i,i+n)){
			f=true;
			break;
		}
	if(f)
		puts("0");
	else{
		reg int cnt=0;
		for(reg int i=1;i<=(n<<1);++i)
			if(i==UnionFind::find(i))
				++cnt;
		cnt>>=1;
		putchar('1');
		while(cnt--)
			putchar('0');
		putchar('\n');
	}
	return 0;
}