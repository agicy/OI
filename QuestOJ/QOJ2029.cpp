#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 20170408

const int MAXM=20000000+5;
const int MAXP=100+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,p;

inline void Read(void){
	scanf("%d%d%d",&n,&m,&p);
	return;
}

bool vis[MAXM];
int cnt,Prime[1270608];
int T[MAXP];

inline void Init(reg int m){
	for(reg int i=2;i<=m;++i){
		if(!vis[i])
			Prime[++cnt]=i;
		for(reg int j=1;j<=cnt&&(ll)i*Prime[j]<=m;++j){
			vis[i*Prime[j]]=true;
			if(i%Prime[j]==0)
				break;
		}
	}
	for(reg int i=1;i<=cnt;++i)
		++T[Prime[i]%p];
	return;
}

struct Matrix{
	int a[MAXP][MAXP];
	inline void Init(void){
		memset(a,0,sizeof(a));
		return;
	}
	inline Matrix(void){
		Init();
		return;
	}
	inline Matrix operator*(const Matrix& b){
		Matrix res;
		for(reg int i=0;i<p;++i)
			for(reg int k=0;k<p;++k)
				for(reg int j=0;j<p;++j)
					res.a[i][j]=(res.a[i][j]+((ll)a[i][k]*b.a[k][j])%MOD)%MOD;
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix x=*this,res;
		for(reg int i=0;i<p;++i)
			res.a[i][i]=1;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x,exp>>=1;
		}
		return res;
	}
};

Matrix dp,F;

inline void Work(void){
	Init(m);
	for(reg int i=0;i<p;++i)
		for(reg int j=0;j<p;++j){
			reg int diff=(i-j+p)%p;
			if(diff==0)
				F.a[j][i]=m/p;
			else if(diff==m)
				F.a[j][i]=1;
			else if(diff<m)
				F.a[j][i]=(int)((m-diff)/p)+1;
			else
				F.a[j][i]=0;
			F.a[j][i]%=MOD;
		}
	dp.a[0][0]=1;
	reg int ans=(dp*(F^n)).a[0][0];
	for(reg int i=0;i<p;++i)
		for(reg int j=0;j<p;++j)
			F.a[j][i]=(F.a[j][i]-T[(i-j+p)%p]+MOD)%MOD;
	ans=(ans-(dp*(F^n)).a[0][0]+MOD)%MOD;
	printf("%d\n",ans);
	return;
}
