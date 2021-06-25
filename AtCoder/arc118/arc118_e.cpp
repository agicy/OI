#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=200+5;
const int mod=998244353;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

int n,K;
int a[MAXN];
bool row[MAXN],col[MAXN];
modInt f[MAXN][MAXN][MAXN][2][2];
modInt fac[MAXN];

inline bool check(reg int x){
	return 1<=x&&x<=n;
}

int main(void){
	n=read();
	a[0]=a[n+1]=-1;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]!=-1){
			row[i]=col[a[i]]=true;
			++K;
		}
	}
	f[0][0][0][0][0]=1;
	for(reg int i=0;i<=n+1;++i)
		for(reg int j=0;j<=n+1;++j)
			for(reg int k=0;k<=n-K;++k)
				for(reg int r=0;r<2;++r)
					for(reg int c=0;c<2;++c)
						if(f[i][j][k][r][c].x){
							if(a[i+1]!=j){
								if(!c&&i<n&&check(j)&&!row[i+1]&&!col[j])
									f[i+1][j][k+1][1][1]+=f[i][j][k][r][c];
								f[i+1][j][k][0][c]+=f[i][j][k][r][c];
							}
							if(a[i]!=j+1){
								if(!r&&check(i)&&j<n&&!row[i]&&!col[j+1])
									f[i][j+1][k+1][1][1]+=f[i][j][k][r][c];
								f[i][j+1][k][r][0]+=f[i][j][k][r][c];
							}
						}
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i;
	modInt ans=0;
	for(reg int i=0;i<=n-K;++i)
		if(i&1)
			ans-=f[n+1][n+1][i][0][0]*fac[n-K-i];
		else
			ans+=f[n+1][n+1][i][0][0]*fac[n-K-i];
	printf("%d\n",ans.x);
	return 0;
}