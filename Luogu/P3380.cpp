#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

#define INF 0X7FFFFFFF

const int MAXN=50000+5;

int n,m;
int a[MAXN];

namespace SegmentTree{
	namespace Splay{
		int tot,root[MAXN<<2];
		const int MAXSIZE=40*MAXN;
		int fa[MAXSIZE],ch[MAXSIZE][2];
		int size[MAXSIZE],cnt[MAXSIZE];
		int val[MAXSIZE];
		inline bool get(reg int p){
			return ch[fa[p]][1]==p;
		}
		inline void pushup(reg int p){
			size[p]=size[ch[p][0]]+size[ch[p][1]]+cnt[p];
			return;
		}
		inline void rotate(reg int x){
			reg int y=fa[x],z=fa[y],k=get(x),w=ch[x][!k];
			ch[z][get(y)]=x;
			ch[x][!k]=y;
			ch[y][k]=w;
			if(w)
				fa[w]=y;
			fa[y]=x,fa[x]=z;
			pushup(y),pushup(x);
			return;
		}
		inline void splay(reg int id,reg int x,reg int goal){
			for(reg int f=fa[x];f=fa[x],f!=goal;rotate(x))
				if(fa[f]!=goal)
					rotate(get(x)!=get(f)?f:x);
			if(!goal)
				root[id]=x;
			return;
		}
		inline int Init(reg int Val,reg int father){
			++tot;
			val[tot]=Val,fa[tot]=father,cnt[tot]=1;
			pushup(tot);
			return tot;
		}
		inline void insert(reg int id,reg int Val){
			reg int ID=root[id],fa=0;
			if(!ID){
				ID=Init(Val,0);
				root[id]=ID;
				return;
			}
			while(ID&&(val[ID]!=Val)){
				fa=ID;
				ID=ch[ID][val[ID]<Val];
			}
			if(Val==val[ID]&&ID)
				++cnt[ID];
			else{
				ID=Init(Val,fa);
				if(fa)
					ch[fa][val[fa]<Val]=ID;
			}
			splay(id,ID,0);
			return;
		}
		inline void find(reg int id,reg int Val){
			reg int ID=root[id];
			if(!ID)
				return;
			while(ch[ID][val[ID]<Val]&&val[ID]!=Val)
				ID=ch[ID][val[ID]<Val];
			splay(id,ID,0);
			return;
		}
		inline int pre(reg int id,reg int Val){
			find(id,Val);
			reg int ID=root[id];
			if(val[ID]<Val)
				return ID;
			ID=ch[ID][0];
			while(ch[ID][1])
				ID=ch[ID][1];
			return ID;
		}
		inline int suf(reg int id,reg int Val){
			find(id,Val);
			reg int ID=root[id];
			if(val[ID]>Val)
				return ID;
			ID=ch[ID][1];
			while(ch[ID][0])
				ID=ch[ID][0];
			return ID;
		}
		inline void del(reg int id,reg int Val){
			reg int Pre=pre(id,Val),Suf=suf(id,Val);
			splay(id,Suf,0),splay(id,Pre,Suf);
			reg int wh=ch[Pre][1];
			if(cnt[wh]>1){
				--cnt[wh];
				splay(id,wh,0);
			}
			else
				ch[Pre][1]=0;
			pushup(Pre);
			return;
		}
		#undef lson
		#undef rson
	}
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	inline void Build(reg int k,reg int l,reg int r){
		Splay::insert(k,-INF),Splay::insert(k,INF);
		if(l==r)
			return;
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int Val){
		Splay::del(k,a[pos]),Splay::insert(k,Val);
		if(l==r){
			a[pos]=Val;
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,Val);
		else
			Update(rson,mid+1,r,pos,Val);
		return;
	}
	inline void Insert(reg int k,reg int l,reg int r,reg int pos,reg int Val){
		Splay::insert(k,Val);
		if(l==r)
			return;
		if(pos<=mid)
			Insert(lson,l,mid,pos,Val);
		else
			Insert(rson,mid+1,r,pos,Val);
		return;
	}
	inline int QueryRank(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(R<l||r<L)
			return 0;
		if(L<=l&&r<=R){
			Splay::find(k,val);
			reg int ID=Splay::root[k];
			if(Splay::val[ID]>=val)
				return Splay::size[Splay::ch[ID][0]]-1;
			else
				return Splay::size[Splay::ch[ID][0]]+Splay::cnt[ID]-1;
		}
		return QueryRank(lson,l,mid,L,R,val)+QueryRank(rson,mid+1,r,L,R,val);
	}
	inline int QueryPre(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Val){
		if(R<l||r<L)
			return -INF;
		if(L<=l&&r<=R)
			return Splay::val[Splay::pre(k,Val)];
		return max(QueryPre(lson,l,mid,L,R,Val),QueryPre(rson,mid+1,r,L,R,Val));
	}
	inline int QuerySuf(reg int k,reg int l,reg int r,reg int L,reg int R,reg int Val){
		if(R<l||r<L)
			return INF;
		if(L<=l&&r<=R)
			return Splay::val[Splay::suf(k,Val)];
		return min(QuerySuf(lson,l,mid,L,R,Val),QuerySuf(rson,mid+1,r,L,R,Val));
	}
	#undef lson
	#undef rson
	#undef mid
	inline int QueryKth(reg int L,reg int R,reg int k){
		reg int l=0,r=INF,mid,res;
		while(l<=r){
			mid=(l+r)>>1;
			reg int check=QueryRank(1,1,n,L,R,mid)+1;
			if(check>k)
				r=mid-1;
			else
				l=mid+1,res=mid;
		}
		return res;
	}
}

using namespace SegmentTree;

int main(void){
	n=read(),m=read();
	Build(1,1,n);
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		Insert(1,1,n,i,a[i]);
	while(m--){
		static int opt,l,r,pos,k;
		opt=read();
		switch(opt){
			case 1:{
				l=read(),r=read(),k=read();
				printf("%d\n",QueryRank(1,1,n,l,r,k)+1);
				break;
			}
			case 2:{
				l=read(),r=read(),k=read();
				printf("%d\n",QueryKth(l,r,k));
				break;
			}
			case 3:{
				pos=read(),k=read();
				Update(1,1,n,pos,k);
				break;
			}
			case 4:{
				l=read(),r=read(),k=read();
				printf("%d\n",QueryPre(1,1,n,l,r,k));
				break;
			}
			case 5:{
				l=read(),r=read(),k=read();
				printf("%d\n",QuerySuf(1,1,n,l,r,k));
				break;
			}
			default:break;
		}
	}
	return 0;
}