#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	bool f=false;
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXSIZE=1e7+5;

int a,b;
bitset<MAXSIZE> vis;
int tot,prime[1000000+5];
int key[MAXSIZE];

inline ll solve(int a,int b){
	for(int i=2;i<=b;++i){
		if(!vis[i]){
			prime[++tot]=i;
			key[i]=i;
		}
		for(int j=1;j<=tot&&i*prime[j]<=b;++j){
			vis[i*prime[j]]=true;
			if(!(i%prime[j])){
				key[i*prime[j]]=key[i];
				break;
			}
			key[i*prime[j]]=1;
		}
	}
	ll res=0;
	for(int i=a;i<=b;++i)
		res+=key[i];
	return res;
}

int main(void){
	a=read(),b=read();
	printf("%lld\n",solve(a,b));
	return 0;
}