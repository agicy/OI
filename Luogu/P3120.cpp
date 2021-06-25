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

const int MAXR=750+5;
const int MAXC=750+5;
const int MAXK=MAXR*MAXC;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int r,c,k;
int val[MAXR][MAXC];
int f[MAXR][MAXC];
int T[MAXK];

inline void solve(reg int l,reg int r){
	if(l==r){
		if(l==1)
			f[1][1]=1;
		return;
	}
	reg int mid=(l+r)>>1;
	solve(l,mid);
	reg int sum=0;
	for(reg int i=1;i<c;++i){
		for(reg int j=l;j<=mid;++j)
			T[val[i][j]]=add(T[val[i][j]],f[i][j]),sum=add(sum,f[i][j]);
		for(reg int j=mid+1;j<=r;++j)
			f[i+1][j]=add(f[i+1][j],sub(sum,T[val[i+1][j]]));
	}
	for(reg int i=1;i<c;++i)
		for(reg int j=l;j<=mid;++j)
			T[val[i][j]]=0;
	solve(mid+1,r);
	return;
}

int main(void){
	r=read(),c=read(),k=read();
	for(reg int i=1;i<=r;++i)
		for(reg int j=1;j<=c;++j)
			val[i][j]=read();
	solve(1,r);
	printf("%d\n",f[r][c]);
	return 0;
}