#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=200000+5;

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			unit[k]=1;
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int val){
		if(l==r){
			--unit[k];
			return l;
		}
		reg int res=0;
		if(val<=unit[lson])
			res=Query(lson,l,mid,val);
		else
			res=Query(rson,mid+1,r,val-unit[lson]);
		pushup(k);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

int n;
int a[MAXN];
int ans[MAXN];
SegmentTree T;

int main(void){
	n=read();
	a[1]=1;
	for(reg int i=2;i<=n;++i)
		a[i]=read()+1;
	T.Build(1,1,n);
	for(reg int i=n;i>=1;--i)
		ans[i]=T.Query(1,1,n,a[i]);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}
