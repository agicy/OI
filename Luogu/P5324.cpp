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

const int MAXN=150000*3+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	n=read(),m=read();
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int ans,Min,cnt,tag;
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].Min=min(unit[lson].Min,unit[rson].Min);
		unit[k].cnt=(unit[lson].Min==unit[k].Min?unit[lson].cnt:0)+(unit[rson].Min==unit[k].Min?unit[rson].cnt:0);
		unit[k].ans=unit[lson].ans+unit[rson].ans;
		return;
	}
	inline void Add(reg int k,reg int val){
		unit[k].Min+=val;
		unit[k].ans=(unit[k].Min==0)?unit[k].cnt:0;
		unit[k].tag+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(unit[k].tag){
			Add(lson,unit[k].tag);
			Add(rson,unit[k].tag);
			unit[k].tag=0;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			unit[k].ans=unit[k].cnt=1;
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			Add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			Update(lson,l,mid,L,R,val);
		if(R>mid)
			Update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].ans;
		pushdown(k);
		reg int res=0;
		if(L<=mid)
			res+=Query(lson,l,mid,L,R);
		if(R>mid)
			res+=Query(rson,mid+1,r,L,R);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

int st,lim;

int t[MAXN];
SegmentTree T;

inline void Change(reg int x,reg int c){
	reg int k=x-t[x]+1-(c>0);
	T.Update(1,1,lim,k,k,c);
	t[x]+=c;
	return;
}

inline void Work(void){
	st=150000+1,lim=450000+5;
	T.Build(1,1,lim);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		a[i]+=st;
		Change(a[i],1);
	}
	while(m--){
		static int p,x;
		p=read(),x=read();
		if(p>0){
			if(a[p]<=st+n)
				Change(a[p],-1);
			else
				--t[a[p]];
			a[p]=st+x;
			if(a[p]<=st+n)
				Change(a[p],1);
			else
				++t[a[p]];
		}
		else if(x>0){
			reg int pos=st+n;
			if(t[pos])
				T.Update(1,1,lim,pos-t[pos]+1,pos,-1);
			--st;
		}
		else{
			++st;
			reg int pos=st+n;
			if(t[pos])
				T.Update(1,1,lim,pos-t[pos]+1,pos,1);
		}
		printf("%d\n",T.Query(1,1,lim,st+1,st+n));
	}
	return;
}
