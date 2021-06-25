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

const int MAXN=600;
const int MAXSIZE=MAXN;

int n,p;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

struct Matrix{
	int n,m;
	int unit[MAXN][MAXN];
	inline Matrix(reg int n,reg int m,reg int x=0):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline int det(void)const{
		Matrix tmp=*this;
		reg int res=1,sgn=0;
		for(reg int i=0;i<n;++i){
			reg int Max=i;
			for(reg int j=i+1;j<n;++j)
				if(abs(tmp.unit[j][i])>abs(tmp.unit[Max][i]))
					Max=j;
			if(i!=Max){
				sgn^=1;
				for(reg int k=0;k<=n-1;++k)
					swap(tmp.unit[i][k],tmp.unit[Max][k]);
			}
			if(!tmp.unit[i][i])
				return 0;
			for(reg int j=i+1;j<n;++j)
				while(tmp.unit[j][i]){
					reg int d=tmp.unit[j][i]/tmp.unit[i][i];
					for(reg int k=i;k<n;++k)
						tmp.unit[j][k]=sub(tmp.unit[j][k],1ll*d*tmp.unit[i][k]%p);
					if(!tmp.unit[j][i])
						break;
					sgn^=1;
					swap(tmp.unit[i],tmp.unit[j]);
				}
			res=1ll*res*tmp.unit[i][i]%p;
		}
		return sgn?p-res:res;
	}
};

int main(void){
	n=read(),p=read();
	Matrix a(n,n,0);
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<n;++j)
			a.unit[i][j]=read()%p;
	printf("%d\n",(a.det()%p+p)%p);
	return 0;
}