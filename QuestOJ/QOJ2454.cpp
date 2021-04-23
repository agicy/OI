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
	while(*s!='.'&&*s!='R'&&*s!='F')*s=getchar();
	while(*s=='.'||*s=='R'||*s=='F')*(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXH=4e3+5;
const int MAXW=4e3+5;

int h,w;
char M[MAXH][MAXW];

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
};

bool vis[MAXH][MAXW];
int cnt[MAXH][MAXW];
Node Q[2][MAXH*MAXW];
int _head[2],_tail[2];

inline void bfs(void){
	reg int ptr=0;
	vis[1][1]=true,Q[ptr][_tail[ptr]++]=Node(1,1);
	while(_head[ptr]<_tail[ptr]){
		while(_head[ptr]<_tail[ptr]){
			static Node s;
			s=Q[ptr][_head[ptr]++];
			reg int x=s.x,y=s.y;
			const int dx[]={-1,0,0,1};
			const int dy[]={0,-1,1,0};
			for(reg int i=0;i<4;++i){
				reg int fx=x+dx[i],fy=y+dy[i];
				if(1<=fx&&fx<=h&&1<=fy&&fy<=w&&!vis[fx][fy]&&M[fx][fy]!='.'){
					vis[fx][fy]=true;
					reg int w=M[fx][fy]!=M[x][y];
					cnt[fx][fy]=cnt[x][y]+w;
					Q[ptr^w][_tail[ptr^w]++]=Node(fx,fy);
				}
			}
		}
		ptr^=1;
	}
	return;
}

int main(void){
	h=read(),w=read();
	for(reg int i=1;i<=h;++i)
		read(M[i]+1);
	bfs();
	reg int ans=0;
	for(reg int i=1;i<=h;++i)
		for(reg int j=1;j<=w;++j)
			ans=max(ans,cnt[i][j]);
	printf("%d\n",ans+1);
	return 0;
}