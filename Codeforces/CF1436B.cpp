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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXA=1e5+1;

bool vis[MAXA];
int tot,prime[MAXA];

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

int main(void){
	Init(1e5);
	reg int t=read();
	while(t--){
		reg int n=read();
		reg int key=-1;
		for(reg int i=1;i<=tot;++i)
			if(prime[i]-(n-1)>=0&&vis[prime[i]-(n-1)]){
				key=(prime[i]-(n-1));
				break;
			}
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				printf("%d%c",i==j?key:1,j==n?'\n':' ');
	}
	return 0;
}