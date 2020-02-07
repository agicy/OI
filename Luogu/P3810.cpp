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
const int MAXK=200000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int x,y,z,cnt,ans;
	inline void Read(void){
		x=read(),y=read(),z=read();
		return;
	}
};

inline bool cmpx(const Node& a,const Node& b){
	return a.x==b.x?(a.y==b.y?(a.z<b.z):a.y<b.y):a.x<b.x;
}

inline bool cmpy(const Node& a,const Node& b){
	return a.y==b.y?a.z<b.z:a.y<b.y;
}

int n,m,K;
Node a[MAXN],b[MAXN];

inline void Read(void){
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	return;
}

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXK];
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
int cnt[MAXN];

inline void CDQ(reg int l,reg int r,reg Node a[]){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	CDQ(l,mid,a),CDQ(mid+1,r,a);
	sort(a+l,a+mid+1,cmpy);
	sort(a+mid+1,a+r+1,cmpy);
	reg int i=mid+1,j=l;
	while(i<=r){
		while(a[j].y<=a[i].y&&j<=mid){
			T.Update(a[j].z,a[j].cnt);
			++j;
		}
		a[i].ans+=T.Query(a[i].z);
		++i;
	}
	for(reg int i=l;i<j;++i)
		T.Update(a[i].z,-a[i].cnt);
	return;
}

inline void Work(void){
	T.Init(K);
	sort(a+1,a+n+1,cmpx);
	reg int sum=0;
	for(reg int i=1;i<=n;++i){
		++sum;
		if(a[i].x!=a[i+1].x||a[i].y!=a[i+1].y||a[i].z!=a[i+1].z)
			b[++m]=a[i],b[m].cnt=sum,sum=0;
	}
	CDQ(1,m,b);
	for(reg int i=1;i<=m;++i)
		cnt[b[i].ans+b[i].cnt-1]+=b[i].cnt;
	for(reg int i=0;i<n;++i)
		printf("%d\n",cnt[i]);
	return;
}
