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

const int MAXN=100000+5;
const int MAXM=50000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int type,val,pos,time;
	inline Node(
		reg int type=0,
		reg int val=0,
		reg int pos=0,
		reg int time=0
	):
		type(type),
		val(val),
		pos(pos),
		time(time)
	{
		return;
	}
};

int n,m,cnt;
int a[MAXN],pos[MAXN];
Node E[MAXN+MAXM];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		pos[a[i]]=i;
		++cnt;
		E[cnt]=Node(1,a[i],i,0);
	}
	for(reg int i=1;i<=m;++i){
		static int x;
		x=read();
		++cnt;
		E[cnt]=Node(-1,x,pos[x],i);
	}
	return;
}

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN];
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
	inline int Query(reg int ID){
		reg int res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

TreeArray T;
ll ans[MAXN];

inline bool cmp(const Node& a,const Node& b){
	return a.pos<b.pos;
}

inline void CDQ(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	CDQ(l,mid),CDQ(mid+1,r);
	sort(E+l,E+mid+1,cmp),sort(E+mid+1,E+r+1,cmp);
	reg int j=l;
	for(reg int i=mid+1;i<=r;++i){
		while(j<=mid&&E[j].pos<=E[i].pos){
			T.Update(E[j].val,E[j].type);
			++j;
		}
		ans[E[i].time]+=E[i].type*(T.Query(n)-T.Query(E[i].val));
	}
	for(reg int i=l;i<j;++i)
		T.Update(E[i].val,-E[i].type);
	j=mid;
	for(reg int i=r;i>mid;--i){
		while(j>=l&&E[j].pos>=E[i].pos){
			T.Update(E[j].val,E[j].type);
			--j;
		}
		ans[E[i].time]+=E[i].type*T.Query(E[i].val-1);
	}
	for(reg int i=mid;i>j;--i)
		T.Update(E[i].val,-E[i].type);
	return;
}

inline void Work(void){
	T.Init(n);
	CDQ(1,cnt);
	reg ll sum=0;
	for(reg int i=1;i<=m;++i){
		sum+=ans[i-1];
		printf("%lld\n",sum);
	}
	return;
}
