#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s!='X'&&*s!='.')*s=getchar();
	while(*s=='X'||*s=='.')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=500+5;
const int MAXM=500+5;

int n,m;
char M[MAXN][MAXM];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read();
		for(reg int i=1;i<=n;++i)
			read(M[i]+1);
		if(n==1){
			for(reg int i=1;i<=m;++i)
				putchar('X');
			putchar('\n');
		}
		else{
			for(reg int i=2;i<=n;++i)
				if(i%3==2)
					fill(M[i]+1,M[i]+m+1,'X');
				else if(i%3==1&&M[i][2]!='X'&&M[i-1][2]!='X')
					M[i][1]=M[i-1][1]='X';
				else if(i%3==1)
					M[i][2]=M[i-1][2]='X';
			if(n%3==1)
				for(reg int i=1;i<=m;++i)
					if(M[n][i]=='X'&&M[n][i-1]!='X')
						M[n-1][i]='X';
			for(reg int i=1;i<=n;++i,putchar('\n'))
				for(reg int j=1;j<=m;++j)
					putchar(M[i][j]);
		}
	}
	flush();
	return 0;
}