#include <bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

struct Node{
	int x,y;
	inline Node(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x||(x==a.x&&y<a.y);
	}
};

struct Event{
	int x,opt;
	inline Event(reg int x=0,reg int opt=0):x(x),opt(opt){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x||(x==a.x&&opt<a.opt);
	}
};

const int MAXN=300+5;

int r,c,n;
Node a[MAXN];
Event b[MAXN*2];
int tot,len[MAXN*2],vis[MAXN*2][MAXN],lim[MAXN*2][3];
ll sum[MAXN*2];

inline bool cmp(const Node& a,const Node& b){
	return a.y<b.y;
}

inline void calc(reg int x){
	reg int las=0,Max=0;
	for(reg int i=1;i<=n;++i)
		if(vis[x][i]){
			if(!las)
				lim[x][0]=a[i].y-1;
			else
				Max=max(Max,a[i].y-a[las].y-1);
			las=i;
		}
	lim[x][1]=c-a[las].y,lim[x][2]=Max;
	return;
}

inline void Init(reg int x){
	sort(a+1,a+n+1,cmp);
	for(reg int i=1;i<=n;++i){
		b[++tot]=Event(a[i].x-x,-i);
		b[++tot]=Event(a[i].x+1,i);
	}
	sort(b+1,b+tot+1);
	for(reg int i=1;i<tot;++i){
		len[i]=b[i+1].x-b[i].x;
		for(reg int j=1;j<=n;++j)
			vis[i][j]=vis[i-1][j];
		if(b[i].opt<0)
			vis[i][-b[i].opt]=true;
		else
			vis[i][b[i].opt]=false;
		calc(i);
	}
	return;
}

inline void Swap(reg int x,reg int y){
	assert(y==x+1);
	swap(b[x],b[y]);
	for(reg int i=x;i<=y;++i){
		for(reg int j=1;j<=n;++j)
			vis[i][j]=vis[i-1][j];
		if(b[i].opt<0)
			vis[i][-b[i].opt]=true;
		else
			vis[i][b[i].opt]=false;
		calc(i);
	}
	return;
}

inline ll solve(reg int x){
	for(reg int i=1;i<=tot;++i)
		if(b[i].opt<0)
			b[i].x-=x;
	reg bool flag=true;
	while(flag){
		flag=false;
		for(reg int i=1;i<tot;++i)
			if(b[i+1]<b[i])
				Swap(i,i+1),flag=true;
	}
	for(reg int i=1;i<tot;++i)
		len[i]=b[i+1].x-b[i].x;
	for(reg int i=2;i<=tot;++i)
		sum[i]=sum[i-1]+len[i-1];
	deque<int> Q[3];
	reg int res=c+c-2;
	for(reg int i=1,j=1;j<=tot;++i){
		while(j<tot&&sum[j]-sum[i]<r){
			if(len[j])
				for(reg int k=0;k<3;++k){
					while(!Q[k].empty()&&lim[Q[k].back()][k]<=lim[j][k])
						Q[k].pop_back();
					Q[k].push_back(j);
				}
			++j;
		}
		if(sum[j]-sum[i]<r)
			break;
		reg int x=lim[Q[0].front()][0],y=lim[Q[1].front()][1],z=lim[Q[2].front()][2];
		res=min(res,max(x+y,z));
		for(reg int k=0;k<3;++k)
			if(Q[k].front()==i)
				Q[k].pop_front();
	}
	return res;
}

int main(void){
	r=read(),c=read(),n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1);
	reg int lef=a[1].x-1,rig=r-a[n].x,Delta=lef+rig;
	for(reg int i=1;i<n;++i)
		Delta=max(Delta,a[i+1].x-a[i].x-1);
	set<int> A,B,U;
	for(reg int i=1;i<=n;++i){
		A.insert(a[i].x-1),B.insert(r-a[i].x);
		for(reg int j=i;j<=n;++j)
			if(a[j].x-a[i].x-1>=Delta)
				U.insert(a[j].x-a[i].x-1);
	}
	for(int i:A)
		for(int j:B)
			if(i+j>=Delta)
				U.insert(i+j);
	Init(*U.begin());
	reg int las=*U.begin();
	reg ll ans=r+c-2;
	for(int i:U)
		ans=min(ans,0ll+i+solve(i-las)),las=i;
	printf("%lld\n",ans);
	return 0;
}