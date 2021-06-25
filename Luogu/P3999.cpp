#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)) *s=getchar();
	while(isdigit(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=6;
const int MAXD=100+5;
const int MAXLVL=5;
const int MAXS=46656;
const int inf=0x3f3f3f3f;

int n,d;
char s[MAXD];
int base6[MAXN+1];
int val[MAXS],to[MAXS];
int f[2][MAXS][MAXLVL+1];

inline int getVal(reg int n,reg int b){
	return n/base6[b]%6;
}

int main(void){
	n=read(),d=read(),read(s+1);
	for(reg int i=1;i<=d;++i)
		s[i]^='0';
	base6[0]=1;
	for(reg int i=1;i<=n;++i)
		base6[i]=base6[i-1]*6;
	for(reg int S=0;S<base6[n];++S){
		reg int tot=0;
		for(reg int i=0;i<n-1;++i){
			reg int u=getVal(S,i);
			if(u&&u==getVal(S,i+1)){
				++tot;
				if(tot>1){
					val[S]=-1;
					break;
				}
				reg int cnt=2,sub=u*base6[i]+u*base6[i+1];
				++i;
				while(getVal(S,i+1)==u)
					++i,++cnt,sub+=u*base6[i];
				val[S]=cnt<<u,to[S]=S-sub;
			}
		}
		if(!tot)
			val[S]=0,to[S]=S;
	}
	for(reg int S=0;S<base6[n];++S)
		if(!val[S])
			for(reg int j=0;j<6;++j)
				f[0][S][j]=-inf;
	f[0][0][0]=0;
	reg int ans=0;
	for(reg int i=1;i<=d;++i){
		for(reg int S=0;S<base6[n];++S)
			if(!val[S])
				for(reg int j=0;j<6;++j)
					f[i&1][S][j]=-inf;
		for(reg int S=0;S<base6[n];++S)
			if(!val[S]){
				f[i&1][S][s[i]]=max(f[i&1][S][s[i]],f[(i-1)&1][S][0]);
				for(reg int j=0;j<n;++j)
					if(!getVal(S,j))
						for(reg int k=0;k<6;++k){
							reg int T=S+base6[j]*s[i],sum=0,lvl=1;
							while(val[T]){
								sum+=val[T];
								T=to[T]+(s[i]+lvl)%6*base6[j];
								++lvl;
							}
							f[i&1][T][k]=max(f[i&1][T][k],f[(i-1)&1][S][k]+sum);
						}
			}
		for(reg int S=0;S<base6[n];++S)
			if(!val[S])
				for(reg int j=0;j<n;++j)
					if(!getVal(S,j))
						for(reg int k=1;k<6;++k){
							reg int T=S+base6[j]*k,sum=0,lvl=1;
							while(val[T]){
								sum+=val[T];
								T=to[T]+(k+lvl)%6*base6[j];
								++lvl;
							}
							f[i&1][T][0]=max(f[i&1][T][0],f[i&1][S][k]+sum);
						}
		for(reg int S=0;S<base6[n];++S)
			if(!val[S])
				for(reg int j=0;j<6;++j)
					ans=max(ans,f[i&1][S][j]);
	}
	printf("%d\n",ans);
	return 0;
}