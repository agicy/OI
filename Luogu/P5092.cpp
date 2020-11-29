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

const int MAXN=3e4+5;

namespace UnionFind{
	int fa[MAXN],len[MAXN],dis[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,len[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else{
			reg int f=find(fa[x]);
			dis[x]+=dis[fa[x]];
			fa[x]=f;
			return f;
		}
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb){
			fa[ra]=rb;
			dis[ra]+=len[rb];
			len[rb]+=len[ra];
		}
		return;
	}
	inline int query(reg int x){
		find(x);
		return dis[x];
	}
}

int main(void){
	UnionFind::Init(3e4);
	reg int p=read();
	while(p--){
		static char opt;
		static int x,y;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'C':{
				x=read();
				printf("%d\n",UnionFind::query(x));
				break;
			}
			case 'M':{
				x=read(),y=read();
				UnionFind::merge(x,y);
				break;
			}
		}
	}
	return 0;
}