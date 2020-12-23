#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e4+5;
const int MAXD=80;
const int prime[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499};
const double inf=1e9;
const double eps=1e-5;

int n;
double val[MAXN];
double f[MAXD][MAXN];

const int MAXSIZE=1e4;
const int BASE=1e4;
const int BASE_LOG=4;

struct BigNumber{
	int len,unit[MAXSIZE];
	inline BigNumber(reg int x=0){
		memset(unit,0,sizeof(unit));
		unit[0]=x,len=1;
		return;
	}
	inline BigNumber operator*(const int x)const{
		BigNumber res(0);
		res.len=len;
		for(reg int i=0;i<res.len;++i)
			res.unit[i]=unit[i]*x;
		for(reg int i=0;i<res.len;++i)
			if(res.unit[i]>=BASE){
				res.unit[i+1]+=res.unit[i]/BASE;
				res.unit[i]%=BASE;
			}
		while(res.unit[res.len]){
			if(res.unit[res.len]>=BASE){
				res.unit[res.len+1]+=res.unit[res.len]/BASE;
				res.unit[res.len]%=BASE;
			}
			++res.len;
		}
		return res;
	}
	inline BigNumber operator*(const BigNumber &a)const{
		BigNumber res(0);
		res.len=len+a.len-1;
		for(reg int i=0;i<len;++i)
			for(reg int j=0;j<a.len;++j){
				if(res.unit[i+j]>=BASE){
					res.unit[i+j+1]+=res.unit[i+j]/BASE;
					res.unit[i+j]%=BASE;
				}
				res.unit[i+j]+=unit[i]*a.unit[j];
			}
		for(reg int i=0;i<res.len;++i)
			if(res.unit[i]>=BASE){
				res.unit[i+1]+=res.unit[i]/BASE;
				res.unit[i]%=BASE;
			}
		while(res.unit[res.len]){
			if(res.unit[res.len]>=BASE){
				res.unit[res.len+1]+=res.unit[res.len]/BASE;
				res.unit[res.len]%=BASE;
			}
			++res.len;
		}
		return res;
	}
	inline void print(void){
		printf("%d",unit[len-1]);
		for(reg int i=len-2;i>=0;--i)
			printf("%0*d",BASE_LOG,unit[i]);
		return;
	}
};

BigNumber ans(1);

inline BigNumber fpow(BigNumber x,reg int exp){
	BigNumber res(1);
	while(exp){
		if(exp&1)
			res=res*x;
		x=x*x;
		exp>>=1;
	}
	return res;
}

int main(void){
	n=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		if(n%i==0)
			++tot;
	for(reg int i=1;i<=tot;++i)
		val[i]=log(prime[i]);
	for(reg int i=1;i<=n;++i)
		f[0][i]=inf;
	f[0][1]=0;
	for(reg int i=1;i<=tot;++i){
		for(reg int j=1;j<=n;++j)
			f[i][j]=inf;
		for(reg int k=1;k<=n;++k)
			for(reg int j=k,c=1;j<=n;j+=k,++c)
				f[i][j]=min(f[i][j],f[i-1][c]+(k-1)*val[i]);
	}
	reg int ptr=n;
	for(reg int i=tot;i>=1;--i)
		for(reg int k=1;k<=ptr;++k)
			if(ptr%k==0&&fabs(f[i-1][ptr/k]+(k-1)*val[i]-f[i][ptr])<eps){
				ans=ans*fpow(prime[i],k-1);
				ptr/=k;
				break;
			}
	ans=ans*fpow(prime[1],ptr-1);
	ans.print();
	putchar('\n');
	return 0;
}