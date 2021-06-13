#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=50+5;
const int mod=1e9+7;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		x=(x%mod+mod)%mod;
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

inline modInt operator/(const modInt& a,const modInt& b){
	return a*fpow(b,mod-2);
}

inline void operator/=(modInt& a,const modInt& b){
	a*=fpow(b,mod-2);
	return;
}

struct Node{
	int delta,l,r;
};

int n,m,k,A;
Node a[MAXN];
modInt f[MAXN][MAXN];

inline modInt getVal(reg int R){
	for(reg int i=0;i<=n;++i)
		for(reg int j=0;j<=i;++j)
			f[i][j]=0;
	f[0][0]=1;
	for(reg int i=0;i<n;++i){
		for(reg int j=0;j<=i;++j)
			if(f[i][j].x){
				reg ll val=1ll*a[i+1].delta*R;
				if(val>=a[i+1].r)
					f[i+1][j+1]+=f[i][j]*(a[i+1].r-a[i+1].l+1);
					//(len) x
				else if(val<a[i+1].l)
					f[i+1][j]+=f[i][j]*(a[i+1].r-a[i+1].l+1);
					//(len)
				else{
					f[i+1][j]+=f[i][j]*(a[i+1].r-val);
					f[i+1][j+1]+=f[i][j]*(val-a[i+1].l+1);
					//(rig)+(lef)*x
				}
			}
	}
	modInt res=0;
	for(reg int i=k;i<=n;++i)
		res+=f[n][i];
	return res;
}

int B;

inline modInt Lagrange(reg int lef,reg int rig,modInt x[],modInt y[],reg int X){
	modInt res=0;
	for(reg int i=lef;i<=rig;++i){
		modInt pod=1;
		for(reg int j=lef;j<=rig;++j)
			if(i!=j)
				pod*=(modInt(X)-x[j])/(x[i]-x[j]);
		res+=y[i]*pod;
	}
	return res;
}

inline modInt getAns(reg int lef,reg int rig){
	if(rig-lef+1<=B){
		modInt res=0;
		for(reg int i=lef;i<=rig;++i)
			res+=getVal(i);
		return res;
	}
	else{
		modInt x[B],y[B];
		for(reg int i=0;i<B;++i)
			x[i]=lef+i,y[i]=getVal(lef+i);
		for(reg int i=1;i<B;++i)
			y[i]+=y[i-1];
		return Lagrange(0,B-1,x,y,rig)-Lagrange(0,B-1,x,y,lef-1);
	}
}

int main(void){
	n=read(),m=read(),k=read(),A=read();
	B=n+2;
	for(reg int i=1;i<=n;++i){
		static int d,x,y;
		d=read(),x=read(),y=read();
		a[i].delta=max(A-d,1),a[i].l=x,a[i].r=y;
	}
	vector<int> V;
	V.push_back(1),V.push_back(m+1);
	for(reg int i=1;i<=n;++i){
		V.push_back((a[i].l+a[i].delta-1)/a[i].delta);
		V.push_back(a[i].r/a[i].delta+1);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	while(V.back()>m+1) V.pop_back();
	modInt ans=0;
	for(reg int i=1,siz=V.size();i<siz;++i)
		ans+=getAns(V[i-1],V[i]-1);
	printf("%d\n",ans.x);
	return 0;
}