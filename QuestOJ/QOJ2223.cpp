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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

int n;
ll K;
int h[MAXN];
int top,S[MAXN];
int fa[MAXN],deg[MAXN],len[MAXN];
ll sum[MAXN];
queue<int> Q;

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i){
		h[i]=read();
		reg int p=0;
		while(top&&h[i]<=h[S[top]])
			p=S[top--];
		if(p)
			fa[p]=i;
		fa[i]=S[top];
		S[++top]=i;
	}
	for(reg int i=1;i<=n;++i){
		len[i]=1;
		++deg[fa[i]];
	}
	for(int i=1;i<=n;++i)
		if(!deg[i])
			Q.push(i);
	reg ll ans=0;
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		int f=fa[ID];
		sum[ID]+=1ll*len[ID]*(h[ID]-h[f]);
		if(sum[ID]>0){
			reg ll temp=(sum[ID]-1)/K+1;
			sum[ID]-=temp*K,ans+=temp;
		}
 		sum[f]+=sum[ID];
		len[f]+=len[ID];
		if(--deg[f]==0)
			Q.push(f);
	}
	printf("%lld\n",ans);
	return 0;
}