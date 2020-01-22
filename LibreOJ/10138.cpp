#include<cstdio>
#include<algorithm>
using std::max;
using std::swap;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool flag=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)flag|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return flag?-res:res;
}

const int MAXN=500000+5;

struct SegmentTree{
	struct Node{
		ll val_sum,val_max;
		inline Node operator+(const Node &a)const{
			Node res;
			res.val_sum=val_sum+a.val_sum;
			res.val_max=max(val_max,a.val_max);
			return res;
		}
	};
	Node unit[MAXN<<2];
	inline void Build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			unit[k].val_sum=unit[k].val_max=a[l];
			return;
		}
		reg int mid=(l+r)>>1;
		Build(k<<1,l,mid,a);
		Build(k<<1|1,mid+1,r,a);
		unit[k]=unit[k<<1]+unit[k<<1|1];
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int index,reg int val){
		if(l==r&&index==l){
			unit[k].val_sum=unit[k].val_max=val;
			return;
		}
		reg int mid=(l+r)>>1;
		if(index<=mid)
			Update(k<<1,l,mid,index,val);
		if(index>mid)
			Update(k<<1|1,mid+1,r,index,val);
		unit[k]=unit[k<<1]+unit[k<<1|1];
		return;
	}
	inline ll QueryMax(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].val_max;
		reg int mid=(l+r)>>1;
		reg ll ans1,ans2;
		if(l<=mid)
			ans1=QueryMax(k<<1,l,mid,L,R);
		if(r>mid)
			ans2=QueryMax(k<<1|1,mid+1,r,L,R);
		return max((ll)ans1,(ll)ans2);
	}
	inline ll QuerySum(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k].val_sum;
		reg int mid=(l+r)>>1;
		reg ll ans1,ans2;
		if(l<=mid)
			ans1=QueryMax(k<<1,l,mid,L,R);
		if(r>mid)
			ans2=QueryMax(k<<1|1,mid+1,r,L,R);
		return ans1+ans2;
	}
};

int n,m,q;
int w[MAXN],a[MAXN];
int cnt,head[MAXN],Next[MAXN],to[MAXN];
int son[MAXN],id[MAXN],fa[MAXN];
int Time,dep[MAXN],size[MAXN],top[MAXN];
SegmentTree T;

inline void Add_Edge(reg int,reg int);
inline void DFS1(reg int,reg int,reg int);
inline void DFS2(reg int,reg int);
inline void Update(int,int,int);
inline ll QueryMax(int,int);
inline ll QuerySum(int,int);

int main(void){
	reg int i;
	n=read();
	for(i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	for(i=1;i<=n;++i)
		w[i]=read();
	for(i=1;i<=n;++i)
		a[i]=w[id[i]];
	DFS1(1,0,1);
	DFS2(1,1);
	T.Build(1,1,n,a);
	q=read();
	while(q--){
		static char ch;
		do
			ch=getchar();
		while(ch!='C'&&ch!='Q');
		if(ch=='C'){
			static int u,t;
			u=read(),t=read();
			T.Update(1,1,n,id[u],t);
		}
		if(ch=='Q'){
			ch=getchar();
			if(ch=='M'){
				
			}
			if(ch=='S'){
				
			}
		}
	}
	return 0;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS1(reg int ID,reg int father,reg int depth){
	reg int i,Wson=-1;
	dep[ID]=depth;
	fa[ID]=father;
	size[ID]=1;
	for(i=head[ID];i;i=Next[i]){
		if(to[i]==father)
			continue;
		DFS1(to[i],ID,depth+1);
		size[ID]+=size[to[i]];
		if(size[to[i]]>Wson)
			son[ID]=to[i],Wson=size[to[i]];
	}
	return;
}

inline void DFS2(int ID,int Top){
	id[ID]=++Time;
	top[ID]=Top;
	if(!son[ID])
		return;
	DFS2(son[ID],Top);
	for(reg int i=head[ID];i;i=Next[i]){
		if(to[i]==fa[ID]||to[i]==son[ID])
			continue;
		DFS2(to[i],to[i]);
	}
	return;
}

inline ll QueryMax(int l,int r){
	reg ll ans=0;
	while(top[l]!=top[r]){
		if(dep[top[l]]<dep[top[r]])
			swap(l,r);
		ans=max((ll)ans,T.QueryMax(1,1,n,id[top[l]],id[l]));
		l=fa[top[l]];
	}
	if(dep[l]>dep[r])
		swap(l,r);
	ans=max((ll)ans,T.QueryMax(1,1,n,id[l],id[r]));
	return ans;
}
