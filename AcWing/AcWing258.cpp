#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int MAXM=2e3+5;

struct Edge{
	int x;
	char op;
	int y;
};

Edge E[MAXM];
int n,m;
int line[MAXM];
int fa[MAXN*3];

inline void Init(reg int n){
	for(reg int i=0;i<=n;++i)
		fa[i]=i;
	return;
}

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline bool conflict(const Edge& E){
	reg int x=E.x,y=E.y;
	switch(E.op){
		case '>':{
			if(find(x)==find(y)||find(x)==find(y+n*2))
				return true;
			fa[find(x+n*2)]=find(y);
			fa[find(x)]=find(y+n);
			fa[find(x+n)]=find(y+n*2);
			break;
		}
		case '<':{
			if(find(x)==find(y)||find(x)==find(y+n))
				return true;
			fa[find(x+n)]=find(y);
			fa[find(x)]=find(y+n*2);
			fa[find(x+n*2)]=find(y+n);
			break;
		}
		case '=':{
			if(find(x)==find(y+n)||find(x+n)==find(y))
				return true;
			fa[find(x)]=find(y);
			fa[find(x+n)]=find(y+n);
			fa[find(x+n*2)]=find(y+n*2);
			break;
		}
	}
	return false;
}

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		for(reg int i=0;i<m;++i)
			scanf("%d%c%d",&E[i].x,&E[i].op,&E[i].y);
		memset(line,0,sizeof(line));
		reg int cnt=0,id=0;
		for(reg int i=0;i<n;++i){
			reg bool flag=false;
			Init(3*n);
			for(reg int j=0;j<m;++j)
				if(E[j].x!=i&&E[j].y!=i&&conflict(E[j])){
					flag=true;
					if(j>line[i])
						line[i]=j+1;
					break;
				}
			if(!flag){
				id=i;
				++cnt;
			}
		}
		if(!cnt)
			puts("Impossible");
		else if(cnt==1){
			reg int ans=0;
			for(reg int i=0;i<n;++i)
				if(line[i]>ans)
					ans=line[i];
			printf("Player %d can be determined to be the judge after %d lines\n",id,ans);
		}
		else
			puts("Can not determine");
	}
	return 0;
}