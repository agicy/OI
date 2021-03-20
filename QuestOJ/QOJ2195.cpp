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
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
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

const int MAXN=2e3+5;
const int MAXM=2e3+5;

int n,m,q;
char M[MAXN][MAXM];
int id,col[MAXN][MAXM],sum[MAXN][MAXM];
bool tag[MAXN][MAXM];
bool vis[MAXN*MAXM];
vector<int> V;
pair<int,int> pos[MAXN*MAXM];

inline bool check(reg int x,reg int l,reg int r){
	return l<=x&&x<=r;
}

inline bool check(reg int x,reg int y,reg int x1,reg int y1,reg int x2,reg int y2){
	return check(x,x1,x2)&&check(y,y1,y2);
}

inline void dfs(reg int x,reg int y){
	col[x][y]=id;
	const int dx[]={-1,0,0,1};
	const int dy[]={0,-1,1,0};
	for(reg int i=0;i<4;++i){
		reg int fx=x+dx[i],fy=y+dy[i];
		if(check(fx,fy,1,1,n,m)&&!col[fx][fy]&&M[x][y]==M[fx][fy])
			dfs(fx,fy);
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
		if(!col[i][j]){
			++id;
			dfs(i,j);
			pos[id]=make_pair(i,j);
			tag[i][j]=1;
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+tag[i][j];
	q=read();
	while(q--){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		vector<int> V;
		reg int ans=sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
		for(reg int i=y1,c;i<=y2;++i){
			c=col[x1][i];
			if(!vis[c]&&!check(pos[c].first,pos[c].second,x1,y1,x2,y2)){
				vis[c]=true;
				++ans;
				V.push_back(c);
			}
			c=col[x2][i];
			if(!vis[c]&&!check(pos[c].first,pos[c].second,x1,y1,x2,y2)){
				vis[c]=true;
				++ans;
				V.push_back(c);
			}
		}
		for(reg int i=x1,c;i<=x2;++i){
			c=col[i][y1];
			if(!vis[c]&&!check(pos[c].first,pos[c].second,x1,y1,x2,y2)){
				vis[c]=true;
				++ans;
				V.push_back(c);
			}
			c=col[i][y2];
			if(!vis[c]&&!check(pos[c].first,pos[c].second,x1,y1,x2,y2)){
				vis[c]=true;
				++ans;
				V.push_back(c);
			}
		}
		writeln(ans);
		for(int id:V)
			vis[id]=false;
	}
	flush();
	return 0;
}