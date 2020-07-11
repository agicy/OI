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

const int MAXN=100000+5;

int n,m;

struct SegmentTree{
	#define lson ( (k) << 1)
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		double Max;
		int cnt;
	};
	double s[MAXN];
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].Max=max(unit[lson].Max,unit[rson].Max);
		return;
	}
	inline int Cnt(reg int k,reg int l,reg int r,reg double val){
		if(unit[k].Max<=val)
			return 0;
		if(s[l]>val)
			return unit[k].cnt;
		if(l==r)
			return s[l]>val;
		if(unit[lson].Max<=val)
			return Cnt(rson,mid+1,r,val);
		else
			return Cnt(lson,l,mid,val)+unit[k].cnt-unit[lson].cnt;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int x,reg int y){
		if(l==r&&l==x){
			unit[k].Max=(double)y/x;
			s[x]=(double)y/x;
			unit[k].cnt=1;
			return;
		}
		if(x<=mid)
			Update(lson,l,mid,x,y);
		if(x>mid)
			Update(rson,mid+1,r,x,y);
		pushup(k);
		unit[k].cnt=unit[lson].cnt+Cnt(rson,mid+1,r,unit[lson].Max);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		T.Update(1,1,n,x,y);
		printf("%d\n",T.unit[1].cnt);
	}
	return 0;
}
