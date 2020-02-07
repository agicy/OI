#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=500+5;
const int MAXQ=60000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int x,y,val;
	inline Node(reg int x=0,reg int y=0,reg int val=0):x(x),y(y),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

struct Querys{
	int x1,y1,x2,y2,k;
	inline void Read(void){
		x1=read(),y1=read(),x2=read(),y2=read(),k=read();
		return;
	}
};

int n,q;
Node v[MAXN*MAXN];
Querys Q[MAXQ];

inline void Read(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			v[(i-1)*n+j]=Node(i,j,read());
	for(reg int i=1;i<=q;++i)
		Q[i].Read();
	return;
}

int ans[MAXQ];

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,m,unit[MAXN][MAXN];
	inline void Init(reg int size1,reg int size2){
		n=size1,m=size2;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int x,reg int y,reg int val){
		for(reg int i=x;i<=n;i+=lowbit(i))
			for(reg int j=y;j<=m;j+=lowbit(j))
				unit[i][j]+=val;
		return;
	}
	inline int Query(reg int x,reg int y){
		reg int res=0;
		for(reg int i=x;i;i-=lowbit(i))
			for(reg int j=y;j;j-=lowbit(j))
				res+=unit[i][j];
		return res;
	}
	inline int Query(const Querys& Q){
		return Query(Q.x2,Q.y2)+Query(Q.x1-1,Q.y1-1)-(Query(Q.x2,Q.y1-1)+Query(Q.x1-1,Q.y2));
	}
	#undef lowbit
};

TreeArray T;
int id[MAXQ],sum[MAXQ];

inline void Solve(reg int l,reg int r,reg int L,reg int R){
	if(R<L)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			ans[id[i]]=v[l].val;
		return;
	}
	reg int mid=(l+r)>>1;
	for(reg int i=l;i<=mid;++i)
		T.Update(v[i].x,v[i].y,1);
	static int temp1[MAXQ],temp2[MAXQ];
	reg int cnt1=0,cnt2=0;
	for(reg int i=L;i<=R;++i){
		reg int u=id[i];
		reg int Sum=sum[u]+T.Query(Q[u]);
		if(Sum>=Q[u].k)
			temp1[++cnt1]=u;
		else
			sum[temp2[++cnt2]=u]=Sum;
	}
	reg int pos=L;
	for(reg int i=1;i<=cnt1;++i)
		id[pos++]=temp1[i];
	for(reg int i=1;i<=cnt2;++i)
		id[pos++]=temp2[i];
	for(reg int i=l;i<=mid;++i)
		T.Update(v[i].x,v[i].y,-1);
	Solve(l,mid,L,L+cnt1-1),Solve(mid+1,r,L+cnt1,R);
	return;
}

inline void Work(void){
	sort(v+1,v+n*n+1);
	T.Init(n,n);
	for(reg int i=1;i<=q;++i)
		id[i]=i;
	Solve(1,n*n,1,q);
	for(reg int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return;
}
