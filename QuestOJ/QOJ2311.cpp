#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+ch-'0',ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

const int MAXN=4e6+5;

int n;
ll a[MAXN];
int lef[MAXN],rig[MAXN];
bool vis[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=readll();
	for(reg int i=1;i<=n;++i){
		if(vis[i])
			continue;
		reg int ptr=i+1;
		while(ptr<=n&&a[ptr]%a[i]==0){
			vis[ptr]=true;
			++rig[i],++ptr;
		}
	}
	for(reg int i=n;i>=1;--i){
		if(vis[i])
			continue;
		reg int ptr=i-1;
		while(ptr>=1&&a[ptr]%a[i]==0){
			vis[ptr]=true;
			++lef[i],--ptr;
		}
	}
	reg int ans=1;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,lef[i]+rig[i]+1);
	printf("%d\n",ans);
	return 0;
}