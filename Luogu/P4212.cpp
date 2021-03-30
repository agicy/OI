#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=50+5;

int n,x,y;
bool G[MAXN][MAXN];
int p[MAXN];

inline int calc(void){
	vector<int> V;
	for(reg int i=1;i<=n;++i){
		reg bool flag=true;
		for(reg int j=0,siz=V.size();j<siz;++j)
			if(!G[V[j]][p[i]]){
				flag=false;
				break;
			}
		if(flag)
			V.push_back(p[i]);
	}
	return V.size();
}

int main(void){
	scanf("%d",&n);
	while(scanf("%d%d",&x,&y)!=EOF)
		G[x][y]=G[y][x]=true;
	reg int ans=1;
	for(reg int i=1;i<=n;++i)
		p[i]=i;
	reg int cnt=5e4;
	while(cnt--){
		random_shuffle(p+1,p+n+1);
		ans=max(ans,calc());
	}
	printf("%d\n",ans);
	return 0;
}