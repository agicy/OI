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
	while(isspace(*s))*s=getchar();
	while(!isspace(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=500+5;
const int MAXM=500+5;

int n,m;
char M[MAXN][MAXM];
char a[MAXN][MAXM],b[MAXN][MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		read(M[i]+1);
		for(reg int j=1;j<=m;++j)
			a[i][j]=b[i][j]=M[i][j];
	}
	for(reg int i=1;i<=n;++i){
		a[i][1]=b[i][m]='#';
		if(i&1)
			for(reg int j=2;j<m;++j)
				a[i][j]='#';
		else
			for(reg int j=2;j<m;++j)
				b[i][j]='#';
	}
	for(reg int i=1;i<=n;++i)
		puts(a[i]+1);
	puts("");
	for(reg int i=1;i<=n;++i)
		puts(b[i]+1);
	return 0;
}