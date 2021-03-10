#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=5e5+5;
const ull base=131;

int n,q;
char str[MAXN];
ull basep[MAXN],Hash[MAXN];

inline void InitHash(void){
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*base;
	for(reg int i=1;i<=n;++i)
		Hash[i]=Hash[i-1]*base+(str[i]-'a'+1);
	return;
}

inline ull GetHash(reg int l,reg int r){
	return Hash[r]-Hash[l-1]*basep[r-l+1];
}

bool vis[MAXN];
int tot,prime[MAXN];
int from[MAXN];

inline void InitPrime(reg int n){
	from[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

int fac[MAXN];

int main(void){
	n=read(),read(str+1),q=read();
	InitHash(),InitPrime(n);
	while(q--){
		static int l,r;
		l=read(),r=read();
		reg int len=r-l+1,tmp=len;
		reg int tot=0;
		while(tmp!=1){
			fac[++tot]=from[tmp];
			tmp/=from[tmp];
		}
		for(reg int i=1;i<=tot;++i){
			reg int k=len/fac[i];
			if(GetHash(l,r-k)==GetHash(l+k,r))
				len=k;
		}
		printf("%d\n",len);
	}
	return 0;
}