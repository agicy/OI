#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e6+5;

int n,m;
int fa[MAXN],pru[MAXN];
int deg[MAXN];

inline void Tprufer(void){
	for(reg int i=1;i<n;++i){
		fa[i]=read();
		++deg[fa[i]];
	}
	for(reg int i=1,j=1;i<=n-2;++i,++j){
		while(deg[j])
			++j;
		pru[i]=fa[j];
		while(i<=n-2&&!--deg[pru[i]]&&pru[i]<j)
			pru[i+1]=fa[pru[i]],++i;
	}
	return;
}

inline void pruferT(void){
	for(reg int i=1;i<=n-2;++i){
		pru[i]=read();
		++deg[pru[i]];
	}
	pru[n-1]=n;
	for(reg int i=1,j=1;i<n;++i,++j){
		while(deg[j])
			++j;
		fa[j]=pru[i];
		while(i<n&&!--deg[pru[i]]&&pru[i]<j)
			fa[pru[i]]=pru[i+1],++i;
	}
	return;
}

int main(void){
	n=read(),m=read();
	if(m==1)
		Tprufer();
	else
		pruferT();
	reg ll ans=0;
	if(m==1)
		for(reg int i=1;i<=n-2;++i)
			ans^=1ll*i*pru[i];
	else
		for(reg int i=1;i<n;++i)
			ans^=1ll*i*fa[i];
	printf("%lld\n",ans);
	return 0;
}