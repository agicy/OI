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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;
const int MAXS=2e5+5;

struct Event{
	int x,y,id;
	inline Event(reg int x=0,reg int y=0,reg int id=0):x(x),y(y),id(id){
		return;
	}
};

struct Link{
	int val,id;
	inline Link(reg int val=0,reg int id=0):val(val),id(id){
		return;
	}
};

int n;

inline pair<int,int> solve(void){
	n=read();
	reg int sum=0;
	vector<vector<int>> S(n+1);
	vector<int> V;
	for(reg int i=1;i<=n;++i){
		reg int k=read();
		sum+=k;
		S[i].resize(k);
		for(reg int j=0;j<k;++j)
			S[i][j]=read(),V.push_back(S[i][j]);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		for(int& x:S[i])
			x=lower_bound(V.begin(),V.end(),x)-V.begin();
	reg int m=V.size();
	reg size_t B=sqrt(sum/16);
	vector<int> Big,Sma;
	for(int i=1;i<=n;++i)
		if(S[i].size()>=B)
			Big.push_back(i);
		else
			Sma.push_back(i);
	vector<bool> vis(m);
	vis.resize(m);
	for(reg int i=0,siz=Big.size();i<siz;++i){
		int u=Big[i];
		for(int x:S[u])
			vis[x]=true;
		for(reg int j=1;j<=n;++j){
			int v=j;
			if(u!=v){
				reg int cnt=0;
				for(int x:S[v])
					if(vis[x])
						++cnt;
				if(cnt>=2)
					return make_pair(u,v);
			}
		}
		for(int x:S[u])
			vis[x]=false;
	}
	vector<Event> E;
	for(reg int i=0,siz=Sma.size();i<siz;++i){
		reg int u=Sma[i];
		for(reg int j=0,siz=S[u].size();j<siz;++j)
			for(reg int k=j+1;k<siz;++k)
				E.push_back(Event(S[u][j],S[u][k],u));
	}
	vector<vector<Link>> G;
	G.resize(m);
	for(Event e:E)
		if(e.x<e.y)
			G[e.x].push_back(Link(e.y,e.id));
		else
			G[e.y].push_back(Link(e.x,e.id));
	vector<int> from;
	from.resize(m);
	for(reg int i=0;i<m;++i){
		for(Link L:G[i])
			if(!from[L.val])
				from[L.val]=L.id;
			else
				return make_pair(from[L.val],L.id);
		for(Link L:G[i])
			from[L.val]=0;
	}
	return make_pair(-1,-1);
}

int main(void){
	reg int t=read();
	while(t--){
		static pair<int,int> ans;
		ans=solve();
		if(ans.first==-1)
			write(-1),putchar('\n');
		else
			write(ans.first),putchar(' '),write(ans.second),putchar('\n');
	}
	flush();
	return 0;
}