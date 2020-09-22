#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXM=1e6+5;
const int inf=0x3f3f3f3f;

int l,r;
bool vis[MAXN];
int tot,prime[MAXN];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
		}
	}
	return;
}

bool p[MAXM];

int main(void){
	Init(1<<16);
	while(scanf("%d%d",&l,&r)!=EOF){
		memset(p,false,sizeof(p));
		if(l==1)
			p[0]=true;
		for(reg int i=1;i<=tot;++i){
			for(reg int j=ceil(l/prime[i]);j<=floor(r/prime[i]);++j)
				if(j!=1)
					p[1ll*prime[i]*j-l]=true;
		}
		reg int Max=-inf,Min=inf;
		pair<int,int> ans1,ans2;
		for(ll i=l,las=0;i<=r;++i)
			if(!p[i-l]){
				if(las){
					if(Max<i-las){
						Max=i-las;
						ans1=make_pair(las,i);
					}
					if(Min>i-las){
						Min=i-las;
						ans2=make_pair(las,i);
					}
				}
				las=i;
			}
		if(Max==-inf&&Min==inf)
			printf("There are no adjacent primes.\n");
		else
			printf("%d,%d are closest, %d,%d are most distant.\n",ans2.first,ans2.second,ans1.first,ans1.second);
	}
	return 0;
}