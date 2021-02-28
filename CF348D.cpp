#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s!='#'&&*s!='.')*s=getchar();
	while(*s=='#'||*s=='.')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=3e3+5;
const int MAXM=3e3+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,m;
char M[MAXN][MAXM];
int f[MAXN][MAXM];

inline int getCnt(reg int x1,reg int y1,reg int x2,reg int y2){
	memset(f,0,sizeof(f));
	for(reg int i=x1;i<=x2;++i)
		for(reg int j=y1;j<=y2;++j)
			if(M[i][j]=='.'){
				if(i==x1&&j==y1)
					f[i][j]=1;
				else
					f[i][j]=add(f[i-1][j],f[i][j-1]);
			}
	return f[x2][y2];
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	printf("%d\n",sub(1ll*getCnt(1,2,n-1,m)*getCnt(2,1,n,m-1)%mod,1ll*getCnt(2,1,n-1,m)*getCnt(1,2,n,m-1)%mod));
	return 0;
}