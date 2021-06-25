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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
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

const int MAXN=20;
const int MAXS=1048576;

int n,q;
int s[MAXN];
int dis[MAXS];
int Q[MAXS];

inline void bfs(void){
	memset(dis,-1,sizeof(dis));
	reg int _head=0,_tail=0;
	dis[0]=0,Q[_tail++]=0;
	while(_head<_tail){
		reg int u=Q[_head++];
		for(reg int i=0;i<20;++i){
			reg int v=u^(1<<i);
			if(dis[v]==-1){
				dis[v]=dis[u]+1;
				Q[_tail++]=v;
			}
		}
		for(reg int i=0;i<n;++i){
			reg int v=u^s[i];
			if(dis[v]==-1){
				dis[v]=dis[u]+1;
				Q[_tail++]=v;
			}
		}
	}
	return;
}

int main(void){
	n=read(),q=read();
	for(reg int i=0;i<n;++i)
		s[i]=read();
	bfs();
	while(q--)
		writeln(dis[read()^read()]);
	flush();
	return 0;
}