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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=2e5+5;

int n;
int a[MAXN],dep[MAXN];

inline void bfs(void){
	queue<int> Q;
	memset(dep,0,sizeof(dep));
	Q.push(1);
	reg int pos=2;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		reg int las=pos;
		if(pos>n)
			break;
		while(pos<n&&a[pos+1]>a[pos])
			++pos;
		for(reg int i=las;i<=pos;++i){
			dep[a[i]]=dep[u]+1;
			Q.push(a[i]);
		}
		++pos;
	}
	return;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		int ans=0;
		bfs();
		for(reg int i=1;i<=n;++i)
			cMax(ans,dep[i]);
		printf("%d\n",ans);
	}
	return 0;
}