#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

inline char* read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return s;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e7+5;
const int MAXM=1e5+5;
const int MAXT=100+5;

namespace AC{
	const int MAXSIZE=MAXN;
	struct Node{
		int ch[4];
		int fail;
		bool tag;
		#define ch(x) unit[(x)].ch
		#define fail(x) unit[(x)].fail
		#define tag(x) unit[(x)].tag
	};
	int tot=1;
	Node unit[MAXSIZE];
	inline int insert(reg char s[],reg int len){
		reg int p=1;
		for(reg int i=0;i<len;++i){
			reg int c=s[i];
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
		}
		return p;
	}
	queue<int> Q;
	inline void build(void){
		for(reg int i=0;i<4;++i)
			ch(0)[i]=1;
		Q.push(1);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=0;i<4;++i)
				if(ch(u)[i])
					fail(ch(u)[i])=ch(fail(u))[i],Q.push(ch(u)[i]);
				else
					ch(u)[i]=ch(fail(u))[i];
		}
		return;
	}
	inline void dfs(reg char s[],reg int len){
		reg int p=1;
		for(reg int i=0;i<len;++i){
			reg int c=s[i];
			p=ch(p)[c];
			for(reg int j=p;j>1&&!tag(j);j=fail(j))
				tag(j)=true;
		}
		return;
	}
	inline int solve(reg char s[],reg int len){
		reg int p=1;
		reg int res=-1;
		for(reg int i=0;i<len;++i){
			reg int c=s[i];
			p=ch(p)[c];
			if(tag(p))
				res=i;
		}
		return res+1;
	}
}

inline char trans(reg char c){
	switch(c){
		case 'E':return 0;
		case 'S':return 1;
		case 'W':return 2;
		case 'N':return 3;
	}
	assert(false);
}

int n,m;
char s[MAXN];
char t[MAXM][MAXT];
int len[MAXM];

int main(void){
	n=read(),m=read();
	read(s);
	for(reg int i=0;i<n;++i)
		s[i]=trans(s[i]);
	for(reg int i=1;i<=m;++i){
		len[i]=read(t[i])-t[i];
		for(reg int j=0;j<len[i];++j)
			t[i][j]=trans(t[i][j]);
		AC::insert(t[i],len[i]);
	}
	AC::build();
	AC::dfs(s,n);
	for(reg int i=1;i<=m;++i)
		writeln(AC::solve(t[i],len[i]));
	flush();
	return 0;
}