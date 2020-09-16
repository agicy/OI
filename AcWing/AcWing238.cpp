#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=3e4+5;

int fa[MAXN],siz[MAXN],c[MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else{
		reg int r=find(fa[x]);
		c[x]+=c[fa[x]];
		return fa[x]=r;
	}
}

int main(void){
	int T;
	cin>>T;
	for(reg int i=1;i<=3e4;++i)
		fa[i]=i,siz[i]=1;
	while(T--){
		static char opt;
		static int x,y;
		cin>>opt>>x>>y;
		reg int fx=find(x),fy=find(y);
		if(opt=='M'){
			c[fx]+=siz[fy];
			fa[fx]=fy;
			siz[fy]+=siz[fx];
		}
		else if(fx!=fy)
			puts("-1");
		else
			printf("%d\n",abs(c[x]-c[y])-1);
	}
	return 0;
}