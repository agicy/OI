#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X7FFFFFFF
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXM=23;
const int MAXSIZE=1.4e6;

int n,m,k;
int f[1<<MAXM];
int E[MAXM][MAXM],to[2][MAXSIZE][MAXM],w[2][MAXSIZE];

inline void Add_Edge(reg int u,reg int v){
	if(u!=v)
		++E[u-1][v-1];
	return;
}

inline int cmin(reg int &a,reg int b){
	return a>b?a=b:a;
}

inline void ins(reg int* a,reg int x,reg int *b){
	for(reg int i=0;i<m;++i)
		b[i]=a[i]+E[x][i]*(1-k)+E[i][x]*(k+1);
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	reg int S=((1<<m)-1);
	reg int last=0;
	for(reg int i=1;i<=n;++i){
		reg int x=read();
		if(last)
			Add_Edge(last,x);
		last=x;
	}
	for(reg int i=1;i<=S;++i)
		f[i]=INF;
	for(reg int i=0;i<m;++i)
		for(reg int j=0;j<m;++j)
			to[0][0][j]+=E[i][j]*k-E[j][i];
	reg int cnt=0,tot=0;
	reg int lastptr=0,ptr;
	for(reg int x=1;x<=m;++x){
		tot=-1;
		ptr=lastptr^1;
		for(reg int i=0;i<=cnt;++i)
			for(reg int j=0;j<m;++j)
				if(!(w[lastptr][i]>>j)){
					w[ptr][++tot]=1<<j|w[lastptr][i];
					ins(to[lastptr][i],j,to[ptr][tot]);
				}
		for(reg int i=0;i<=cnt;++i)
			for(reg int j=0;j<m;++j)
				if(~w[lastptr][i]>>j&1)
					cmin(f[1<<j|w[lastptr][i]],f[w[lastptr][i]]+to[lastptr][i][j]*x);
		lastptr=ptr,cnt=tot;
	}
	printf("%d\n",f[S]);
	return 0;
}