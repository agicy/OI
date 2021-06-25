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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=200;
const int MAXSIZE=MAXN;
const int MAXS=1e5+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Matrix{
	int n,m;
	ll unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n,reg int m,reg ll x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:inf;
		return;
	}
	inline void print(void)const{
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				printf("%lld%c",unit[i][j],j==m-1?'\n':' ');
		return;
	}
	inline Matrix operator*(const Matrix& a)const{
		Matrix res(n,a.m,inf);
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				reg ll r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=min(res.unit[i][j],r+a.unit[k][j]);
			}
		return res;
	}
	inline Matrix operator^(reg int exp){
		Matrix res=Matrix(n,n,0),x=*this;
		while(exp){
			if(exp&1)
				res=res*x;
			x=x*x;
			exp>>=1;
		}
		return res;
	}
};

int n,m;
vector<char> str[MAXN];
vector<int> kmp[MAXN];

inline vector<int> getKMP(vector<char> str){
	reg int len=str.size();
	vector<int> kmp;
	kmp.resize(len);
	kmp[0]=-1;
	for(reg int i=1,j=-1;i<len;++i){
		while(j>=0&&str[i]!=str[j+1])
			j=kmp[j];
		if(str[i]==str[j+1])
			++j;
		kmp[i]=j;
	}
	return kmp;
}

inline int getDis(reg int a,reg int b){
	reg int lena=str[a].size(),lenb=str[b].size();
	reg int j=-1;
	for(reg int i=1;i<lena;++i){
		while(j>=0&&str[a][i]!=str[b][j+1])
			j=kmp[b][j];
		if(str[a][i]==str[b][j+1])
			++j;
	}
	return lenb-j-1;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i){
		static char s[MAXS];
		read(s);
		reg int len=strlen(s);
		str[i].resize(len);
		for(reg int j=0;j<len;++j)
			str[i][j]=s[j];
		kmp[i]=getKMP(str[i]);
	}
	Matrix f(n,n);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			f.unit[i][j]=getDis(i,j);
	Matrix A(1,n);
	for(reg int i=0;i<n;++i)
		A.unit[0][i]=str[i].size();
	Matrix res=A*(f^(m-1));
	reg ll ans=inf;
	for(reg int i=0;i<n;++i)
		ans=min(ans,res.unit[0][i]);
	printf("%lld\n",ans);
	return 0;
}