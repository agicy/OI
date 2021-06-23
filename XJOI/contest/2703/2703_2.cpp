#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5;
const int MAXM=7;
const int inf=0x3f3f3f3f;

int n,m;
char M[MAXN+1][MAXM];
int len[1<<MAXM];
int mir[MAXN+1];
int f[2][MAXN*MAXM+1][1<<MAXM];

inline int lg(reg int x){
	switch(x){
		case 1<<0:return 0;
		case 1<<1:return 1;
		case 1<<2:return 2;
		case 1<<3:return 3;
		case 1<<4:return 4;
		case 1<<5:return 5;
		case 1<<6:return 6;
		default:assert(false);return -1;
	}
}

inline int lowbit(reg int x){
	return x&(-x);
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=0;j<m;++j)
				do
					M[i][j]=getchar();
				while(!isdigit(M[i][j]));
		for(reg int i=1;i<=n;++i){
			mir[i]=0;
			for(reg int j=0;j<m;++j)
				if(M[i][j]=='1')
					mir[i]|=1<<j;
		}
		for(reg int S=0;S<(1<<m);++S){
			if(__builtin_parity(S))
				continue;
			reg int sum=0,las=-1;
			for(reg int T=S;T;T^=lowbit(T))
				if(las==-1)
					las=lg(lowbit(T));
				else
					sum+=lg(lowbit(T))-las,las=-1;
			len[S]=sum;
		}
		fill(f[0][0],f[0][0]+(1<<m),-inf);
		f[0][0][0]=0;
		for(reg int i=0;i<n;++i){
			for(reg int j=0;j<=(i+1)*m;++j)
				for(reg int S=0;S<(1<<m);++S)
					f[(i+1)&1][j][S]=-inf;
			for(reg int j=0;j<=i*m;++j)
				for(reg int S=0;S<(1<<m);++S)
					if(f[i&1][j][S]>-inf)
						for(reg int T=0;T<(1<<m);++T)
							if((!__builtin_parity(T))&&((mir[i+1]&T)==T))
								f[(i+1)&1][j+__builtin_popcount(T)][S^T]=max(f[(i+1)&1][j+__builtin_popcount(T)][S^T],f[i&1][j][S]+len[T]+(__builtin_popcount(S&T)-__builtin_popcount(T^(S&T)))*(i+1));
		}
		f[n&1][0][0]=max(f[n&1][0][0],0);
		for(reg int i=1;i<=n*m;++i)
			f[n&1][i][0]=max(f[n&1][i][0],f[n&1][i-1][0]);
		for(reg int i=0;i<=n*m;++i)
			printf("%d%c",4*n*m-2*f[n&1][i][0],i==n*m?'\n':' ');
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}