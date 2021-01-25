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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s!='.'&&*s!='*')*s=getchar();
	while(*s=='.'||*s=='*')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=9+5;
const int MAXM=9+5;
const int MAXNM=81+5;
const int mod=1e9;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a%=mod,b%=mod;
	a-=b;
	return a<0?a+mod:a;
}

int n,m;
char s[MAXN][MAXM];
int tot,id[MAXN][MAXM];
int G[MAXNM][MAXNM];

inline void Add(reg int u,reg int v){
	G[u][u]=add(G[u][u],1),G[v][v]=add(G[v][v],1);
	G[u][v]=sub(G[u][v],1),G[v][u]=sub(G[v][u],1);
	return;
}

inline int getVal(void){
	reg int res=1;
	for(reg int i=1;i<tot;++i){
		for(reg int j=i+1;j<tot;++j)
			while(G[j][i]){
				reg int d=G[i][i]/G[j][i];
				for(reg int k=i;k<tot;++k)
					G[i][k]=sub(G[i][k],1ll*d*G[j][k]%mod);
				swap(G[i],G[j]);
				res=sub(mod,res);
			}
		res=1ll*res*G[i][i]%mod;
	}
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(s[i]+1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(s[i][j]=='.')
				id[i][j]=++tot;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(s[i][j]=='.'){
				if(j>1&&s[i][j-1]=='.')
					Add(id[i][j],id[i][j-1]);
				if(i>1&&s[i-1][j]=='.')
					Add(id[i][j],id[i-1][j]);
			}
	reg int ans=getVal();
	printf("%d\n",ans);
	return 0;
}