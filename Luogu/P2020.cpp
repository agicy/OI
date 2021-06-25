#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

ll n;
int k,p;

inline int add(reg int a,reg int b,reg int mod){
	assert(0<=a&&a<mod);
	assert(0<=b&&b<mod);
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b,reg int mod){
	assert(0<=a&&a<mod);
	assert(0<=b&&b<mod);
	a-=b;
	return a<0?a+p:a;
}

const int MAXSIZE=3;

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		assert(m==a.n);
		Matrix res(n,a.m,0);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg int r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=add(res.unit[i][j],1ll*r*a.unit[k][j]%p,p);
			}
		return res;
	}
	inline Matrix operator^(reg ll exp)const{
		assert(n==m);
		Matrix res(n,m,1),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x,exp>>=1;
		}
		return res;
	}
};

inline ll exgcd(reg ll a,reg ll b,reg ll &x,reg ll &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg ll d=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return d;
}

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline int getInv(reg int x,reg int p){
	if(gcd(x,p)==1){
		ll Inv,tmp;
		exgcd(x,p,Inv,tmp);
		return (Inv%p+p)%p;
	}
	else
		return -1;
}

const int MAXK=1e6+5;
const int inf=0x3f3f3f3f;

int f[MAXK*6];
int len[MAXK];
int tot,val[MAXK],dfn[MAXK];

int main(void){
	scanf("%lld%d%d",&n,&k,&p);
	if(n==1||n==2){
		puts("1");
		return 0;
	}
	f[1]=f[2]=1;
	memset(len,0x3f,sizeof(len));
	for(int i=3;;++i){
		f[i]=add(f[i-2],f[i-1],k);
		if(f[i]==1&&f[i-1]==1)
			break;
		reg int Inv=getInv(f[i],k);
		if(Inv!=-1)
			len[Inv]=min(len[Inv],i);
	}
	reg int ptr=1;
	reg ll len1=0;
	reg bool flag=false;
	while(true){
		val[dfn[ptr]=++tot]=ptr;
		if(len[ptr]>=inf){
			for(reg int i=1;i<tot;++i)
				len1+=len[val[i]];
			flag=true;
			break;
		}
		ptr=1ll*ptr*f[len[ptr]-1]%k;
		if(dfn[ptr]){
			for(reg int i=1;i<dfn[ptr];++i)
				len1+=len[val[i]];
			break;
		}
	}
	Matrix trans1(3,3,0);
	trans1.unit[0][0]=1,trans1.unit[0][1]=1,trans1.unit[0][2]=0,
	trans1.unit[1][0]=1,trans1.unit[1][1]=0,trans1.unit[1][2]=0,
	trans1.unit[2][0]=0,trans1.unit[2][1]=0,trans1.unit[2][2]=1;

	Matrix trans2(3,3,0);
	trans2.unit[0][0]=1,trans2.unit[0][1]=1,trans2.unit[0][2]=0,
	trans2.unit[1][0]=1,trans2.unit[1][1]=0,trans2.unit[1][2]=0,
	trans2.unit[2][0]=p-1,trans2.unit[2][1]=0,trans2.unit[2][2]=1;

	Matrix bas(1,3,0);
	bas.unit[0][0]=1,bas.unit[0][1]=0,bas.unit[0][2]=1;

	if(n<=len1){
		--len[1],--n;
		for(reg int i=1;i<dfn[ptr];++i)
			if(n>=len[val[i]])
				n-=len[val[i]],bas=bas*(trans1^(len[val[i]]-1))*trans2;
			else{
				bas=bas*(trans1^n);
				break;
			}
	}
	else{
		--len[1];
		n-=len1;
		for(reg int i=1;i<dfn[ptr];++i)
			bas=bas*(trans1^(len[val[i]]-1))*trans2;
		if(flag)
			bas=bas*(trans1^n);
		else{
			reg ll len2=0;
			Matrix trans3(3,3,1);
			for(reg int i=dfn[ptr];i<=tot;++i)
				len2+=len[val[i]],trans3=trans3*(trans1^(len[val[i]]-1))*trans2;
			reg ll cnt=n/len2,res=n%len2;
			bas=bas*(trans3^cnt);
			for(reg int i=dfn[ptr];i<=tot;++i)
				if(res>=len[val[i]])
					res-=len[val[i]],bas=bas*(trans1^(len[val[i]]-1))*trans2;
				else{
					bas=bas*(trans1^res);
					break;
				}
		}
	}
	printf("%d\n",bas.unit[0][0]);
	return 0;
}