#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F3F3F3F3F
#define int long long
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

const int MAXN=50000+5;
const int MAXX=100000+5;

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum,num,len;
		bool lflag,rflag;
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k,reg int l,reg int r){
		if(unit[k].sum){
			unit[k].num=1;
			unit[k].len=r-l+1;
			unit[k].lflag=unit[k].rflag=true;
		}
		else if(l==r){
			unit[k].num=0;
			unit[k].len=0;
			unit[k].lflag=unit[k].rflag=false;
		}
		else{
			unit[k].len=unit[lson].len+unit[rson].len;
			unit[k].num=unit[lson].num+unit[rson].num;
			if(unit[lson].rflag&&unit[rson].lflag)
				--unit[k].num;
			unit[k].lflag=unit[lson].lflag;
			unit[k].rflag=unit[rson].rflag;
		}
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			unit[k].sum+=val;
			pushup(k,l,r);
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k,l,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
};

struct Line{
	int l,r;
	int h;
	int flag;
	inline Line(reg int l=0,reg int r=0,reg int h=0,reg int flag=0):l(l),r(r),h(h),flag(flag){
		return;
	}
	inline bool operator<(const Line& a)const{
		return h==a.h?flag>a.flag:h<a.h;
	}
};

int n;
SegmentTree T;
Line L[MAXN<<1];

signed main(void){
	n=read();
	int Max=-INF,Min=INF;
	reg int cnt=0;
	for(reg int i=1;i<=n;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		Max=max(Max,max(x1,x2));
		Min=min(Min,min(x1,x2));
		L[++cnt]=Line(x1,x2,y1,1);
		L[++cnt]=Line(x1,x2,y2,-1);
	}
	if(Min<=0){
		for(reg int i=1;i<=cnt;++i){
			L[i].l+=-Min+1;
			L[i].r+=-Min+1;
		}
		Max-=Min;
	}
	sort(L+1,L+cnt+1);
	reg int last=0,ans=0;
	for(reg int i=1;i<=cnt;++i){
		T.Update(1,1,Max,L[i].l,L[i].r-1,L[i].flag);
		while(L[i].h==L[i+1].h&&L[i].flag==L[i+1].flag){
			++i;
			T.Update(1,1,Max,L[i].l,L[i].r-1,L[i].flag);
		}
		ans+=abs(T.unit[1].len-last);
		last=T.unit[1].len;
		ans+=T.unit[1].num*2*(L[i+1].h-L[i].h);
	}
	printf("%lld\n",ans);
	return 0;
}
