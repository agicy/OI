#include <bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const int MAXP1=300+5;
const int MAXP2=300+5;
const int MAXV=(MAXP1+MAXP2)*2;
const int MAXSIZE=8;

int n;
int tot,a[MAXP1+MAXP2],b[MAXP1+MAXP2],dp[MAXP1+MAXP2][MAXP1+MAXP2];
int fa[MAXV],siz[MAXV],vis[MAXV];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void merge(reg int a,reg int b){
	reg int ra=find(a),rb=find(b);
	if(ra!=rb){
		fa[rb]=ra;
		siz[ra]+=siz[rb];
	}
	return;
}

int main(void){
	int p1,p2;
	while(scanf("%d%d%d",&n,&p1,&p2)!=EOF&&(n!=0||p1!=0||p2!=0)){
		memset(dp,0,sizeof(dp));
		reg int sum=p1+p2,tot=0;
		dp[0][0]=1;
		for(reg int i=1;i<=sum;++i){
			fa[i]=i,fa[i+sum]=i+sum;
			siz[i]=1,siz[i+sum]=0;
			vis[i]=vis[i+sum]=0;
		}
		for(reg int i=1;i<=n;++i){
			static int x,y;
			static char str[MAXSIZE];
			scanf("%d%d%s",&x,&y,str+1);
			if(str[1]=='y')
				merge(x,y),merge(x+sum,y+sum);
			else
				merge(x,y+sum),merge(x+sum,y);
		}
		for(reg int i=1;i<=sum;++i)
			if(i==find(i)){
				vis[i]=vis[i+sum]=++tot;
				a[tot]=siz[i],b[tot]=siz[i+sum];
			}
		for(reg int i=1;i<=tot;++i)
			for(reg int j=min(a[i],b[i]);j<=p1;++j){
				if(j>=a[i])
					dp[i][j]+=dp[i-1][j-a[i]];
				if(j>=b[i])
					dp[i][j]+=dp[i-1][j-b[i]];
			}
		if(dp[tot][p1]!=1)
			puts("no");
		else{
			for(reg int i=tot;i>=1;--i)
				if(dp[i-1][p1-a[i]])
					p1-=a[i],a[i]=-1;
				else if(dp[i-1][p1-b[i]])
					p1-=b[i],a[i]=-2;
			for(reg int i=1,f=find(1);i<=sum;f=find(++i))
				if(vis[f]){
					if(f>sum&&a[vis[f]]==-2)
						printf("%d\n",i);
					else if(f<=sum&&a[vis[f]]== -1)
						printf("%d\n",i);
					}
			puts("end");
		}
	}
	return 0;
}