
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

#define Calc(i,j) f[j]+pow(abs(s[i]-s[j]-L),P)

const int MAXN=1e5+5;
const int MAXSIZE=33;

int n,L,P;
int s[MAXN],Q[MAXN],k[MAXN],pr[MAXN];
long double f[MAXN];
char str[MAXN][MAXSIZE];

inline long double pow(reg long double x,reg int exp){
	reg long double res=1.0;
	for(reg int k=P;k;k>>=1,x*=x)
		if(k&1)
			res*=x;
	return res;
}

inline int bound(reg int x,reg int y){
	reg int l=x,r=n+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(Calc(mid,x)>=Calc(mid,y))
			r=mid;
		else
			l=mid+1;
	}
	return l;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),L=read()+1,P=read();
		for(reg int i=1;i<=n;++i){
			scanf("%s",str[i]);
			s[i]=s[i-1]+strlen(str[i])+1;
		}
		reg int head=1,tail=1;
		Q[1]=0;
		for(reg int i=1;i<=n;++i){
			while(head<tail&&k[head]<=i)
				++head;
			f[i]=Calc(i,Q[head]);
			pr[i]=Q[head];
			while(head<tail&&k[tail-1]>=bound(Q[tail],i))
				--tail;
			k[tail]=bound(Q[tail],i),Q[++tail]=i;
		}
		if(f[n]>1e18)
			puts("Too hard to arrange");
		else{
			printf("%.0Lf\n",f[n]);
			reg int i;
			for(Q[tail=0]=i=n;i;i=pr[i])
				Q[++tail]=pr[i];
			for(;tail;--tail){
				for(i=Q[tail]+1;i<Q[tail-1];++i)
					printf("%s ",str[i]);
				puts(str[i]);
			}
		}
		puts("--------------------");
	}
	return 0;
}