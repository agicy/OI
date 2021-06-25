#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int ans=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch))ans=10*ans+(ch^'0'),ch=getchar();
	return ans;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

int n;
int f[1<<24],g[1<<24];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static char s[4];
		read(s);
		++g[(1<<(s[0]-'a'))|(1<<(s[1]-'a'))|(1<<(s[2]-'a'))];
	}
	reg int ans=0;
	for(reg int S=0;S<(1<<24);++S){
		reg int i=lowbit(S),j=lowbit(S^i),k=lowbit(S^i^j);
		if(!j)
			f[S]=g[S];
		else if(!k)
			f[S]=f[S^i]+f[S^j]+g[S];
		else
			f[S]=f[S^i]+f[S^j]+f[S^k]-f[S^i^j]-f[S^i^k]-f[S^j^k]+f[S^i^j^k]+g[i^j^k];
		ans^=(n-f[S])*(n-f[S]);
	}
	printf("%d\n",ans);
	return 0;
}