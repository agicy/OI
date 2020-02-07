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

const int MAXN=300000+5;
const int MAXM=300000+5;
const int MAXK=300000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Updates{
	int l,r,val;
	inline void Read(void){
		l=read(),r=read(),val=read();
		return;
	}
};

struct Querys{
	int val;
	vector<int> id;
};

int n,m,K;
Updates U[MAXK];
Querys Q[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(int i=1;i<=m;++i)
		Q[read()].id.push_back(i);
	for(reg int i=1;i<=n;++i)
		Q[i].val=read();
	K=read();
	for(reg int i=1;i<=K;++i)
		U[i].Read();
	return;
}

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXM];
	inline void Init(reg int size){
		n=size;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,reg int val){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline void Update(const Updates& a){
		if(a.l<=a.r){
			Update(a.l,a.val);
			Update(a.r+1,-a.val);
		}
		else{
			Update(1,a.val);
			Update(a.r+1,-a.val);
			Update(a.l,a.val);
		}
		return;
	}
	inline void unUpdate(const Updates& a){
		if(a.l<=a.r){
			Update(a.l,-a.val);
			Update(a.r+1,a.val);
		}
		else{
			Update(1,-a.val);
			Update(a.r+1,a.val);
			Update(a.l,-a.val);
		}
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline int Query(const Querys& a){
		reg int res=0;
		for(reg int i=0;i<(int)a.id.size();++i){
			res+=Query(a.id[i]);
			if(res>=a.val)
				return res;
		}
		return res;
	}
	#undef lowbit
};

int now=1;
int id[MAXN];
TreeArray T;
int ans[MAXN];

inline void Solve(reg int l,reg int r,reg int L,reg int R){
	if(R<L)
		return;
	if(l==r){
		for(reg int i=L;i<=R;++i)
			ans[id[i]]=l;
		return;
	}
	reg int mid=(l+r)>>1;
	while(now<=mid){
		T.Update(U[now]);
		++now;
	}
	while((now>mid+1)){
		--now;
		T.unUpdate(U[now]);
	}
	static int temp1[MAXN],temp2[MAXN];
	reg int cnt1=0,cnt2=0;
	for(reg int i=L;i<=R;++i){
		reg int u=id[i];
		reg int sum=T.Query(Q[u]);
		if(sum>=Q[u].val)
			temp1[++cnt1]=u;
		else
			temp2[++cnt2]=u;
	}
	reg int pos=L;
	for(reg int i=1;i<=cnt1;++i)
		id[pos++]=temp1[i];
	for(reg int i=1;i<=cnt2;++i)
		id[pos++]=temp2[i];
	Solve(mid+1,r,L+cnt1,R),Solve(l,mid,L,L+cnt1-1);
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		id[i]=i;
	T.Init(m);
	Solve(1,K+1,1,n);
	for(reg int i=1;i<=n;++i)
		if(ans[i]!=K+1)
			printf("%d\n",ans[i]);
		else
			puts("NIE");
	return;
}
