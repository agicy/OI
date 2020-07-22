#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;

int n,m;
int a[MAXN];
int Max[MAXN],Min[MAXN];
int p[MAXN];
int f[MAXN];

namespace TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXN];
	inline void Init(reg int S){
		n=S;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=max(unit[i],val);
		return;
	}
	inline int query(reg int id){
		int res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res=max(res,unit[i]);
		return res;
	}
	inline void clear(reg int id){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=0;
		return;
	}
	#undef lowbit
}

inline bool cmp1(reg int a,reg int b){
	return Max[a]<Max[b];
}

inline bool cmp2(reg int x,reg int y){
	return a[x]<a[y];
}

inline void Solve(reg int l,reg int r){
	if(l==r){
		f[l]=max(f[l],1);
		return;
	}
	reg int mid=(l+r)>>1;
	Solve(l,mid);
	for(reg int i=l;i<=r;++i)
		p[i]=i;
	sort(p+l,p+mid+1,cmp1);
	sort(p+mid+1,p+r+1,cmp2);
	reg int j=l;
	for(reg int i=mid+1;i<=r;++i){
		while(j<=mid&&Max[p[j]]<=a[p[i]]){
			TreeArray::update(a[p[j]],f[p[j]]);
			++j;
		}
		f[p[i]]=max(f[p[i]],TreeArray::query(Min[p[i]])+1);
	}
	for(reg int i=l;i<=r;++i)
		TreeArray::clear(a[p[i]]);
	Solve(mid+1,r);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		Max[i]=Min[i]=a[i]=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Max[x]=max(Max[x],y);
		Min[x]=min(Min[x],y);
	}
	int M=0;
	for(reg int i=1;i<=n;++i)
		M=max(M,Max[i]);
	TreeArray::Init(M);
	Solve(1,n);
	int ans=1;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
