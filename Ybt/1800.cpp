#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=6e3+5;
const int MAXS=36e6+5;

int ans[MAXN];
bool vis[MAXS];
int tot,prime[MAXS];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

inline void solve(reg int sum){
	int x=sum;
	while(x){
		if(ans[x]==1){
			ans[x]=2;
			sum-=x;
		}
		--x;
		cMin(x,sum);
	}
	return;
}

int main(void){
	reg int n=read();
	reg int sum=n*(n+1)/2;
	Init(sum);
	for(reg int i=1;i<=n;++i)
		ans[i]=1;
	int ans_cnt=-1;
	if(n>1){
		if(vis[sum]){
			if(sum&1){
				if(!vis[sum-2])
					ans_cnt=ans[2]=2;
				else{
					ans[3]=3;
					sum-=3;
					for(reg int j=1;j<=tot;++j){
						if(!vis[sum-prime[j]]){
							ans_cnt=3;
							solve(prime[j]);
							break;
						}
					}
				}
			}
			else{
				for(reg int j=1;j<=tot;++j)
					if(!vis[sum-prime[j]]){
						ans_cnt=2;
						solve(prime[j]);
						break;
					}
			}
		}
		else{
			ans_cnt=1;
		}
	}
	printf("%d\n",ans_cnt);
	if(ans_cnt>0)
		for(reg int i=1;i<=n;++i)
			printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}