#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=3e5+5;
const int MAXLOG2N=19+1;
const int MAXK=100;
const int B=100;

int n;

namespace Tree{
	struct Edge{
		int v,w;
		inline Edge(reg int v=0,reg int w=0):v(v),w(w){
			return;
		}
	};
	int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int fa[MAXN],dep[MAXN];
	ll dis[MAXN];
	int siz[MAXN],son[MAXN];
	int tim,dfn[MAXN];
	inline void dfs(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		dfn[u]=++tim;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dis[v]=dis[u]+w[i];
				dfs(v,u);
				siz[u]+=siz[v];
				if(siz[son[u]]<siz[v])
					son[u]=v;
			}
		}
		return;
	}
	int top[MAXN];
	inline void dfs2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				dfs2(v,u,v);
		}
		return;
	}
	inline int LCA(reg int x,reg int y){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				x=fa[top[x]];
			else
				y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	inline void getInitLCA(void){
		dfs2(1,0,1);
		return;
	}
	inline ll getDis(reg int u,reg int v){
		return dis[v]-dis[u];
	}
}

struct Data{
	int siz,unit[MAXK<<1];
	inline Data(void){
		siz=0;
		return;
	}
	inline void Init(void){
		siz=0;
		return;
	}
	inline void push_back(reg int val){
		unit[siz++]=val;
		return;
	}
	inline int size(void)const{
		return siz;
	}
	inline int* begin(void){
		return unit;
	}
	inline int* end(void){
		return unit+siz;
	}
};

inline bool cmp(reg int a,reg int b){
	return Tree::dfn[a]<Tree::dfn[b];
}

namespace VirtualTree{
	struct Edge{
		int v;
		ll w;
		inline Edge(reg int v=0,reg ll w=0):v(v),w(w){
			return;
		}
	};
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	ll w[MAXN<<1];
	bool inque[MAXN];
	int _head,_tail,Q[MAXN];
	inline void Add_Edge(reg int u,reg int v,reg ll len){
		if(!inque[u])
			inque[u]=true,Q[_tail++]=u;
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg ll len){
		Add_Edge(u,v,len),Add_Edge(v,u,len);
		return;
	}
	int fa[MAXN];
	ll dis[MAXN],Maxdis[MAXN];
	int son[MAXN];
	inline void dfs1(reg int u,reg int father){
		fa[u]=father;
		Maxdis[u]=dis[u];
		son[u]=0;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dis[v]=dis[u]+w[i];
				dfs1(v,u);
				if(Maxdis[v]>Maxdis[u]){
					Maxdis[u]=Maxdis[v];
					son[u]=v;
				}
			}
		}
		return;
	}
	int top[MAXN];
	ll val[MAXN];
	typedef pair<ll,int> Info;
	priority_queue<Info,vector<Info>,greater<Info>/**/> Qu;
	inline void dfs2(reg int u,reg int father,reg int topf,reg int lim){
		if(u==topf)
			val[topf]=0;
		top[u]=topf;
		val[topf]+=dis[u]-dis[father];
		if(!son[u]){
			Qu.push(make_pair(val[topf],u));
			while((int)Qu.size()>lim-1)
				Qu.pop();
		}
		if(son[u])
			dfs2(son[u],u,topf,lim);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&v!=son[u])
				dfs2(v,u,v,lim);
		}
		return;
	}
	int S[MAXN];
	inline Data build(const Data& V,reg int lim,reg ll &ans){
		cnt=0,_head=0,_tail=0;
		reg int siz=V.size();
		reg int top=0;
		S[++top]=V.unit[0];
		for(reg int i=1;i<siz;++i){
			if(V.unit[i]==V.unit[i-1])
				continue;
			reg int x=V.unit[i],y=Tree::LCA(x,S[top]);
			while(top>1&&Tree::dep[y]<=Tree::dep[S[top-1]]){
				reg ll p=Tree::getDis(S[top-1],S[top]);
				Add_Tube(S[top-1],S[top],p);
				--top;
			}
			if(S[top]!=y){
				reg ll p=Tree::getDis(y,S[top]);
				Add_Tube(y,S[top],p);
				S[top]=y;
			}
			S[++top]=x;
		}
		while(top>1){
			reg ll p=Tree::getDis(S[top-1],S[top]);
			Add_Tube(S[top-1],S[top],p);
			--top;
		}
		reg int rt=V.unit[0];
		dis[rt]=0;
		dfs1(rt,0);
		for(reg int i=1;i<siz;++i)
			if(dis[V.unit[i]]>dis[rt])
				rt=V.unit[i];
		dis[rt]=0;
		dfs1(rt,0);
		dfs2(rt,0,rt,lim);
		Data res;
		res.Init();
		res.push_back(rt);
		ans=0;
		while(!Qu.empty()){
			res.push_back(Qu.top().second);
			ans+=Qu.top().first;
			Qu.pop();
		}
		while(_head<_tail){
			reg int u=Q[_head++];
			inque[u]=false,head[u]=0;
		}
		sort(res.begin(),res.end(),cmp);
		return res;
	}
}

inline Data merge_by_dfn(const Data& a,const Data& b){
	Data res;
	res.Init();
	reg int i=0,j=0;
	while(i<a.size()&&j<b.size())
		if(cmp(a.unit[i],b.unit[j]))
			res.push_back(a.unit[i++]);
		else
			res.push_back(b.unit[j++]);
	while(i<a.size())
		res.push_back(a.unit[i++]);
	while(j<b.size())
		res.push_back(b.unit[j++]);
	return res;
}

inline Data merge(const Data& a,const Data& b,reg int lim){
	Data tmp=merge_by_dfn(a,b);
	if(a.size()+b.size()<=lim)
		return tmp;
	else{
		static ll X;
		return VirtualTree::build(tmp,lim,X);
	}
}

inline ll getRes(const Data& a,reg int lim){
	reg ll res;
	VirtualTree::build(a,lim,res);
	return res;
}

namespace Block{
	const int MAXBLK=(MAXN+B-1)/B+50;
	const int MAXLOG2MAXBLK=log2(MAXBLK)+2;
	int lef[MAXBLK],rig[MAXBLK];
	int id[MAXN];
	Data dat[MAXBLK];
	inline void build(reg int id){
		dat[id].Init();
		for(reg int i=lef[id];i<=rig[id];++i)
			dat[id].push_back(i);
		sort(dat[id].begin(),dat[id].end(),cmp);
		return;
	}
	namespace ST{
		int lg[MAXBLK];
		Data st[MAXLOG2MAXBLK][MAXBLK];
		inline void Init(reg int n,Data dat[]){
			lg[0]=-1;
			for(reg int i=1;i<=n;++i)
				lg[i]=lg[i>>1]+1;
			for(reg int i=1;i<=n;++i)
				st[0][i]=dat[i];
			for(reg int j=1;j<MAXLOG2MAXBLK;++j)
				for(reg int i=1;i+(1<<j)-1<=n;++i)
					st[j][i]=merge(st[j-1][i],st[j-1][i+(1<<(j-1))],min(st[j-1][i].size()+st[j-1][i+(1<<(j-1))].size(),MAXK));
			return;
		}
		inline Data query(reg int l,reg int r){
			reg int k=lg[r-l+1];
			return merge(st[k][l],st[k][r-(1<<k)+1],min(st[k][l].size()+st[k][r-(1<<k)+1].size(),MAXK));
		}
	}
	inline void build(void){
		reg int tot=(n+B-1)/B;
		for(reg int i=1;i<=tot;++i){
			lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
			for(reg int j=lef[i];j<=rig[i];++j)
				id[j]=i;
			build(i);
		}
		ST::Init(tot,dat);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b,z;
		a=read(),b=read(),z=read();
		Tree::Add_Edge(a,b,z),Tree::Add_Edge(b,a,z);
	}
	Tree::dfs(1,0);
	Tree::getInitLCA();
	Block::build();
	reg int q=read();
	while(q--){
		static int l,r,k;
		static ll ans;
		l=read(),r=read(),k=read();
		reg int idl=Block::id[l],idr=Block::id[r];
		if(idl==idr){
			static Data dat;
			dat.Init();
			for(reg int i=l;i<=r;++i)
				dat.push_back(i);
			sort(dat.begin(),dat.end(),cmp);
			ans=getRes(dat,k);
		}
		else{
			if(idl+1==idr){
				static Data dat;
				dat.Init();
				for(reg int i=l;i<=r;++i)
					dat.push_back(i);
				sort(dat.begin(),dat.end(),cmp);
				ans=getRes(dat,k);
			}
			else{
				static Data datl,datr;
				datl.Init();
				for(reg int i=l;i<=Block::rig[idl];++i)
					datl.push_back(i);
				sort(datl.begin(),datl.end(),cmp);
				datr.Init();
				for(reg int i=r;i>=Block::lef[idr];--i)
					datr.push_back(i);
				sort(datr.begin(),datr.end(),cmp);
				ans=getRes(merge(merge(datl,Block::ST::query(idl+1,idr-1),k),datr,k),k);
			}
		}
		writeln(ans);
	}
	flush();
	return 0;
}