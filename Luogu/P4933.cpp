#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int MAXV=2e4+5;
const int Delta=MAXV;
const int p=998244353;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int n;
int h[MAXN];
int f[MAXN][MAXV<<1];
bitset<MAXV<<1> vis[MAXN];

inline int Calc(reg int x){
	reg int sum=0;
	for(reg int i=x-1;i>=1;--i){
		if(!vis[i][h[i]-h[x]+Delta]){
			vis[i][h[i]-h[x]+Delta]=true;
			++f[i][h[i]-h[x]+Delta];
		}
		sum=add(sum,f[i][h[i]-h[x]+Delta]);
		f[x][h[i]-h[x]+Delta]=add(f[x][h[i]-h[x]+Delta],f[i][h[i]-h[x]+Delta]);
	}
	return sum;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans=add(ans,Calc(i));
	printf("%d\n",add(ans,n));
	return 0;
}