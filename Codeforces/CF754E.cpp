#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)&&*s!='?')*s=getchar();
	while(isalpha(*s)||*s=='?')*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int vis=-1;
	if(x==0) putchar('0');
	else while(x) buf[++vis]=(x%10)^'0',x/=10;
	while(~vis) putchar(buf[vis--]);
	putchar('\n');
	return;
}

const int MAXN=400+5;
const int MAXM=400+5;

int n,m,r,c;
bitset<MAXM> ans[MAXN],vis[MAXN][26];

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i){
		static char str[MAXM];
		read(str);
		for(reg int j=0;j<m;++j)
			vis[i][str[j]-'a'][j]=ans[i][j]=true;
	}
	r=read(),c=read();
	for(reg int i=0;i<r;++i){
		static char str[MAXM];
		read(str);
		for(reg int j=0;j<c;++j)
			if(str[j]!='?')
				for(reg int k=0;k<n;++k)
					ans[(k+n-i)%n]&=vis[k][str[j]-'a']>>j%m|vis[k][str[j]-'a']<<m-j%m;
	}
	for(reg int i=0;i<n;++i,putchar('\n'))
		for(reg int j=0;j<m;++j)
			putchar(ans[i][j]|'0');
	flush();
	return 0;
}