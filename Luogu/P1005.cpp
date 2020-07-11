#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef __int128 lll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=80+5;
const int MAXM=80+5;

int n,m;
int a[MAXN][MAXM];
lll pow2[MAXM];
lll f[MAXN][MAXN];

inline lll dp(reg int i,reg int l,reg int r){
	if(f[l][r]!=-1)
		return f[l][r];
	if(r-l>=1)
		f[l][r]=max(a[i][l]*pow2[m-(r-l)]+dp(i,l+1,r),dp(i,l,r-1)+a[i][r]*pow2[m-(r-l)]);
	else
		f[l][r]=a[i][l]*pow2[m-(r-l)];
	return f[l][r];
}

inline void Print(reg lll x){
	if(x==0)
		return;
	else{
		Print(x/10);
		putchar(x%10+'0');
	}
	return;
}

int main(void){
	reg lll ans=0;
	n=read(),m=read();
	pow2[0]=1;
	for(reg int i=1;i<=m;++i)
		pow2[i]=pow2[i-1]*2;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read();
	for(reg int i=1;i<=n;++i){
		memset(f,-1,sizeof(f));
		ans+=dp(i,1,m);
	}
	if(ans==0)
		puts("0");
	else
		Print(ans),putchar('\n');
	return 0;
}
