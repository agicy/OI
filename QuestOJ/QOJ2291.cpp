#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int ans=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))ans=10*ans+(ch^'0'),ch=getchar();
	return f?-ans:ans;
}

const int MAXN=15+5;
const int MAXSIZE=43046721;
const int inf=0x3f3f3f3f;

int n,K;
int a[MAXN],pre[MAXN];
int basep[MAXN];
bool vis[MAXN];
int dp[MAXSIZE];
int lis[MAXN];

int main(){
	n=read(),K=read();
	for(reg int i=0;i<K;++i){
		a[i]=read();
		if(i)
			pre[a[i]]=a[i-1];
	}
	basep[1]=1;
	for(reg int i=2;i<=n+1;++i)
		basep[i]=basep[i-1]*3;
	reg int ans=0;
	dp[0]=1;
	vis[0]=true;
	for(reg int S=0;S<basep[n+1];++S){
		if(!dp[S])
			continue;
		reg int cnt=1,tot=0;
		for(reg int i=1,tmp=S;i<=n;++i,tmp/=3){
			if(tmp%3)
				vis[i]=true,++tot;
			else
				vis[i]=false;
			if(tmp%3==1)
				lis[cnt++]=i;
		}
		if(tot==n)
			ans+=dp[S];
		else{
			lis[cnt]=inf;
			for(reg int j=1,ptr=1;j<=n;++j){
				if(vis[j]||!vis[pre[j]])
					continue;
				while(lis[ptr]<j)
					++ptr;
				if(ptr>K)
					continue;
				if(ptr==cnt)
					dp[S+basep[j]]+=dp[S];
				else
					dp[S+basep[j]+basep[lis[ptr]]]+=dp[S];
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}