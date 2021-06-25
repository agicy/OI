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
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=2e3+5;
const int MAXM=2e3+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,m;
char M[MAXN][MAXM];
int a[MAXN][MAXM],b[MAXN][MAXM];
int f[MAXN][MAXM];

inline void add(reg int a[MAXN][MAXN],reg int x1,reg int y1,reg int x2,reg int y2,reg int val){
	a[x1][y1]=add(a[x1][y1],val),a[x2+1][y2+1]=add(a[x2+1][y2+1],val);
	a[x1][y2+1]=sub(a[x1][y2+1],val),a[x2+1][y1]=sub(a[x2+1][y1],val);
	return;
}

inline void solve(reg bool flag1,reg bool flag2){
	memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='1'){
				add(a,flag1?i+1:1,flag2?j+1:1,flag1?n:i,flag2?m:j,1);
				add(b,flag1?i+1:1,flag2?j+1:1,flag1?n:i,flag2?m:j,add(flag1?mod-i:i,flag2?mod-j:j));
			}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			a[i][j]=add(a[i][j],sub(add(a[i-1][j],a[i][j-1]),a[i-1][j-1]));
			b[i][j]=add(b[i][j],sub(add(b[i-1][j],b[i][j-1]),b[i-1][j-1]));
			f[i][j]=add(f[i][j],add(b[i][j],add(1ll*a[i][j]*(flag1?i:mod-i)%mod,1ll*a[i][j]*(flag2?j:mod-j)%mod)));
		}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	reg int cnt=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='1')
				++cnt;
	if(!cnt)
		puts("0");
	else{
		solve(false,false),solve(true,false),solve(false,true),solve(true,true);
		reg int inv=fpow(cnt,mod-2);
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j){
				reg int wns=1ll*f[i][j]*inv%mod;
				ans^=wns;
			}
		printf("%d\n",ans);
	}
	return 0;
}