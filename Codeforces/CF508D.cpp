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

inline void read(reg char *s){
	*s=getchar();
	while(!isalnum(*s))*s=getchar();
	while(isalnum(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=2e5+5;

int n;
int inDeg[1<<14],outDeg[1<<14];
int tot;
char ans[MAXN];
vector<int> G[1<<14];

inline void dfs(reg int u){
	while(!G[u].empty()){
		reg int v=G[u].back();
		G[u].pop_back();
		dfs(v);
	}
	ans[++tot]=u&127;
	return;
}

inline void NO(void){
	putchar('N'),putchar('O'),putchar('\n');
	return;
}

inline void YES(void){
	putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
	return;
}

int main(void){
	n=read();
	reg int S=-1;
	for(reg int i=1;i<=n;++i){
		static char s[4];
		static int x,y;
		read(s),x=((s[0])<<7)|s[1],y=((s[1])<<7)|s[2];
		S=x;
		++outDeg[x],++inDeg[y];
		G[x].push_back(y);
	}
	reg bool flag=false;
	reg int cntO=0,cntI=0;
	for(reg int i=0;i<(1<<14);++i){
		reg int delta=inDeg[i]-outDeg[i];
		if(delta==-1)
			++cntO,S=i;
		else if(delta==1)
			++cntI;
		else if(delta)
			flag=true;
	}
	if(flag||cntO>1||cntI>1||cntO+cntI==1)
		NO();
	else{
		dfs(S);
		ans[++tot]=S>>7;
		if(tot!=n+2)
			NO();
		else{
			YES();
			for(reg int i=n+2;i>=1;--i)
				putchar(ans[i]);
			putchar('\n');
		}
	}
	flush();
	return 0;
}