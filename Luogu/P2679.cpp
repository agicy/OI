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
	return f?-res:res;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e3+5;
const int MAXM=200+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int n,m,k;
char a[MAXN],b[MAXM];
int f[MAXM][MAXM];
int g[MAXM][MAXM];

int main(void){
	scanf("%d%d%d%s%s",&n,&m,&k,a+1,b+1);
	g[0][0]=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=min(m,i);j>=1;--j)
			for(reg int l=min(k,j);l>=1;--l){
				f[j][l]=(a[i]==b[j])?add(f[j-1][l],g[j-1][l-1]):0;
				g[j][l]=add(g[j][l],f[j][l]);
			}
	printf("%d\n",g[m][k]);
	return 0;
}