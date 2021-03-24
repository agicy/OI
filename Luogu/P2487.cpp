#include<bits/stdc++.h>
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

const int MAXN=5e4+5;

int n;
int h[MAXN],v[MAXN];
vector<int> Vh,Vv;
int f[MAXN];
double g[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,tim;
	int t[MAXN];
	pair<int,double> unit[MAXN];
	inline void Init(reg int s){
		n=s,++tim;
		return;
	}
	inline void update(reg int id,const pair<int,double>& val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=make_pair(0,0.0);
			if(unit[i].first<val.first)
				unit[i].first=val.first,unit[i].second=0;
			if(unit[i].first==val.first)
				unit[i].second+=val.second;
		}
		return;
	}
	inline pair<int,double> query(reg int id){
		pair<int,double> res=make_pair(0,0.0);
		for(reg int i=id;i;i^=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=make_pair(0,0.0);
			if(res.first<unit[i].first)
				res.first=unit[i].first,res.second=0;
			if(res.first==unit[i].first)
				res.second+=unit[i].second;
		}
		return res;
	}
}

struct Node{
	int x,y,z;
	inline Node(reg int x=0,reg int y=0,reg int z=0):x(x),y(y),z(z){
		return;
	}
};

inline bool cmpy(const Node& a,const Node& b){
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}

inline bool cmpx(const Node& a,const Node& b){
	return a.x<b.x;
}

Node a[MAXN];

inline void solve(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	solve(l,mid);
	sort(a+l,a+mid+1,cmpy),sort(a+mid+1,a+r+1,cmpy);
	BIT::Init(Vv.size());
	reg int ptr=l;
	for(reg int i=mid+1;i<=r;++i){
		while(ptr<=mid&&a[ptr].y<=a[i].y){
			BIT::update(a[ptr].z,make_pair(f[a[ptr].x],g[a[ptr].x]));
			++ptr;
		}
		pair<int,double> tmp=BIT::query(a[i].z);
		if(f[a[i].x]<tmp.first+1)
			f[a[i].x]=tmp.first+1,g[a[i].x]=0;
		if(f[a[i].x]==tmp.first+1)
			g[a[i].x]+=tmp.second;
	}
	sort(a+mid+1,a+r+1,cmpx);
	solve(mid+1,r);
	return;
}

int dp[MAXN][2];
double cnt[MAXN][2];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		h[i]=read(),v[i]=read();
		Vh.push_back(h[i]),Vv.push_back(v[i]);
	}
	sort(Vh.begin(),Vh.end()),Vh.erase(unique(Vh.begin(),Vh.end()),Vh.end());
	sort(Vv.begin(),Vv.end()),Vv.erase(unique(Vv.begin(),Vv.end()),Vv.end());
	for(reg int i=1;i<=n;++i){
		h[i]=lower_bound(Vh.begin(),Vh.end(),h[i])-Vh.begin()+1;
		v[i]=lower_bound(Vv.begin(),Vv.end(),v[i])-Vv.begin()+1;
	}
	reg int H=Vh.size(),V=Vv.size();
	for(reg int i=1;i<=n;++i){
		a[i]=Node(i,H-h[i]+1,V-v[i]+1);
		f[i]=1,g[i]=1;
	}
	solve(1,n);
	for(reg int i=1;i<=n;++i)
		dp[i][0]=f[i],cnt[i][0]=g[i];
	for(reg int i=1;i<=n;++i){
		a[i]=Node(n-i+1,h[i],v[i]);
		f[i]=1,g[i]=1;
	}
	reverse(a+1,a+n+1);
	solve(1,n);
	reverse(f+1,f+n+1),reverse(g+1,g+n+1);
	for(reg int i=1;i<=n;++i)
		dp[i][1]=f[i],cnt[i][1]=g[i];
	reg int ans=0;
	reg double sum=0;
	for(reg int i=1;i<=n;++i){
		if(ans<dp[i][0])
			ans=dp[i][0],sum=0;
		if(ans==dp[i][0])
			sum+=cnt[i][0];
	}
	printf("%d\n",ans);
	for(reg int i=1;i<=n;++i)
		if(dp[i][0]+dp[i][1]-1==ans)
			printf("%.4lf%c",cnt[i][0]*cnt[i][1]/sum,i==n?'\n':' ');
		else
			printf("0%c",i==n?'\n':' ');
	return 0;
}