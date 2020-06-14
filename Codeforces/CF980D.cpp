#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5000+5;
const int MAXSIZE=10000+5;

int tot,prime[MAXSIZE];
bool vis[MAXSIZE];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

int n;
int a[MAXN];
int pre[MAXN];
map<int,int> M;
int ans[MAXN];

int main(void){
	Init(1e4);
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]!=0)
			for(reg int j=1;j<=tot;++j){
				reg int v=prime[j]*prime[j];
				if(a[i]%v==0)
					while(a[i]%v==0)
						a[i]/=v;
			}
	}
	memset(pre,-1,sizeof(pre));
	for(reg int i=1;i<=n;++i){
		if(M.find(a[i])!=M.end())
			pre[i]=M[a[i]];
		M[a[i]]=i;
	}
	for(reg int i=1;i<=n;++i){
		reg bool flag=false;
		reg int cnt=0;
		for(reg int j=i;j<=n;++j){
			if(a[j]!=0){
				if(pre[j]<i)
					++cnt;
			}
			else if(!flag){
				flag=true;
				++cnt;
			}
			if(cnt==1&&flag)
				++ans[1];
			else
				++ans[flag?(cnt-1):cnt];
		}
	}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}