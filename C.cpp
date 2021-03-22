#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXM=1e7+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,m;
bool vis[MAXM];
int tot,prime[MAXM];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

namespace Subtask1{
	const int MAXS=1e5+5;
	ll Max;
	map<ll,bool> M;
	int top;
	ll S[MAXS];
	inline void dfs(reg int dep,ll pod,ll phi){
		if(dep==tot+1){
			if(M[phi]&&!M[pod])
				S[++top]=pod;
			return;
		}
		dfs(dep+1,pod,phi);
		reg ll bas=1;
		while(true){
			if(phi<=Max/(prime[dep]-1)/bas){
				dfs(dep+1,pod*prime[dep]*bas,phi*(prime[dep]-1)*bas);
				bas*=prime[dep];
			}
			else
				break;
		}
		return;
	}
	inline void Solve(void){
		M[1]=true,Max=1;
		reg int siz=1;
		puts("1");
		for(reg int i=2;i<=n;++i){
			dfs(1,1,1);
			while(top){
				ll u=S[top--];
				Max=max(Max,u);
				//printf("insert %lld\n",u);
				M[u]=true;
				++siz;
			}
			printf("%d\n",siz);
		}
		return;
	}
}

namespace Subtask3{
	inline void Solve(void){
		if(m==2){
			for(reg int i=1;i<=n;++i)
				printf("%d\n",i);
		}
		else{
			puts("1");
			reg int bas=2;
			for(reg int i=2;i<=n;++i){
				printf("%d\n",bas);
				bas=add(bas,i+1);
			}
		}
		return;
	}
}

int main(void){
	n=read(),m=read();
	Init(m);
	if(n<=10&&m<=100)
		//puts("S1"),
		Subtask1::Solve();
	else if(m<=3)
		//puts("S3"),
		Subtask3::Solve();
	return 0;
}