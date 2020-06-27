#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 10007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=MOD?sum-MOD:sum;
}

inline int dec(reg int a,reg int b){
	reg int res=a-b;
	return res<0?res+MOD:res;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%MOD;
}

const int MAXN=100000+5;
const int MAXC=20+5;

int n,c;
int a[MAXN],b[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int val[MAXC],sum;
		#define val(x) unit[(x)].val
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		for(reg int i=0;i<c;++i)
			val(k)[i]=0;
		for(reg int i=0;i<c;++i)
			for(reg int j=0;j<=i;++j)
				val(k)[i]=add(val(k)[i],mul(val(lson)[j],val(rson)[i-j]));
		sum(k)=mul(sum(lson),sum(rson));
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			val(k)[0]=b[l],val(k)[1]=a[l];
			sum(k)=add(a[l],b[l]);
			return;
		}
		Build(lson,l,mid),Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int a,reg int b){
		if(l==r){
			val(k)[0]=b,val(k)[1]=a;
			sum(k)=add(a,b);
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,a,b);
		else
			Update(rson,mid+1,r,pos,a,b);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read(),c=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read()%MOD;
	for(reg int i=1;i<=n;++i)
		b[i]=read()%MOD;
	Build(1,1,n);
	reg int q=read();
	while(q--){
		static int i,x,y;
		i=read(),x=read()%MOD,y=read()%MOD;
		Update(1,1,n,i,x,y);
		reg int ans=unit[1].sum;
		for(reg int i=0;i<c;++i)
			ans=dec(ans,unit[1].val[i]);
		printf("%d\n",ans);
	}
	return 0;
}