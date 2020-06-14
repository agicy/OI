#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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


inline void Init(void){
	return;
}

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%d%s%d",&n,str+1,&q);
	return;
}

const ull base=131;
ull basep[MAXN],Hash[MAXN];

inline void InitHash(void){
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*p;
	for(reg int i=1;i<=n;++i)
		Hash[i]=Hash[i-1]*base+str[i]-'a'+1;
	return;
}

inline ull GetHash(reg int l,reg int r){
	return Hash[r]-Hash[l-1]*basep[r-l+1];
}

bool vis[MAXN];
int cnt,prime[MAXN];
int Next[MAXN];

inline void InitPrime(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++cnt]=i;
		}
		for(reg int j=1;j<=cnt&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			Next[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

inline void Work(void){
	InitHash();
	return;
}
