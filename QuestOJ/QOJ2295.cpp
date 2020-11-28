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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void read(reg char *s){
	reg char ch=getchar();
	while(!isalpha(ch))ch=getchar();
	while(isalpha(ch))*(s++)=ch,ch=getchar();
	*s='\0';
}

const int MAXN=1e5+5;
const int MAXQ=2e5+5;
const int MAXLOG2N=17+1;
const int MAXV=MAXN<<1;
const int MAXE=MAXN<<1;
const int MAXLOG2V=MAXLOG2N+1;

int n,m,q;
int ed[MAXN],len[MAXN];
char s[MAXN],t[MAXN];
int ans[MAXQ];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int sum;
		#define sum(x) unit[(x)].sum
	};
	Node unit[MAXN<<3];
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		sum(k)+=val;
		if(l==r)
			return;
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int val){
		if(l==r)
			return l;
		if(val>sum(lson))
			return query(rson,mid+1,r,val-sum(lson));
		else
			return query(lson,l,mid,val);
	}
	#undef lson
	#undef rson
	#undef mid
}

namespace SAM{
	struct Node{
		int nex[26];
		int fa,len;
		#define fa(x) sam[(x)].fa
		#define len(x) sam[(x)].len
		#define nex(x) sam[(x)].nex
	};
	Node sam[MAXV];
	int las=1,tot=1;
	int c[MAXN],a[MAXV];
	int siz[MAXV],son[MAXV];
	vector<int> edp[MAXV];
	inline void insert(reg int x,int pos){
		if(nex(las)[x]){
			reg int cur=las,q=nex(cur)[x];
			if(len(cur)+1==len(q)){
				las=q;
				++siz[las];
				edp[las].push_back(pos);
			}
			else{
				reg int nq=++tot;
				sam[nq]=sam[q];
				len(nq)=len(cur)+1,fa(q)=nq;
				while(cur&&nex(cur)[x]==q){
					nex(cur)[x]=nq;
					cur=fa(cur);
				}
				las=nq;
				++siz[las];
				edp[las].push_back(pos);
			}
		}
		else{
			reg int cur=las,p=++tot;
			len(p)=len(cur)+1;
			while(cur&&!nex(cur)[x]){
				nex(cur)[x]=p;
				cur=fa(cur);
			}
			if(!cur)
				fa(p)=1;
			else{
				reg int q=nex(cur)[x];
				if(len(cur)+1==len(q))
					fa(p)=q;
				else{
					reg int nq=++tot;
					sam[nq]=sam[q];
					len(nq)=len(cur)+1;
					fa(p)=fa(q)=nq;
					while(cur&&nex(cur)[x]==q){
						nex(cur)[x]=nq;
						cur=fa(cur);
					}
				}
			}
			las=p,++siz[las],edp[las].push_back(pos);
		}
		return;
	}
	int ecnt,head[MAXV],to[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v){
		Next[++ecnt]=head[u];
		to[ecnt]=v;
		head[u]=ecnt;
		return;
	}
	int f[MAXLOG2V][MAXV];
	inline void build(void){
		for(reg int i=1;i<=tot;++i){
			++c[sam[i].len];
			if(i>1){
				f[0][i]=sam[i].fa;
				Add_Edge(sam[i].fa,i);
			}
		}
		for(reg int i=1;i<MAXLOG2V;++i)
			for(reg int j=2;j<=tot;++j)
				f[i][j]=f[i-1][f[i-1][j]];
		for(reg int i=1;i<=1e5;++i)
			c[i]+=c[i-1];
		for(reg int i=tot;i>1;--i)
			a[c[sam[i].len]--]=i;
		for(reg int i=tot;i>1;--i){
			siz[sam[a[i]].fa]+=siz[a[i]];
			if(!son[sam[a[i]].fa]||siz[son[sam[a[i]].fa]] < siz[a[i]])
				son[sam[a[i]].fa]=a[i];
		}
		return;
	}
	inline int get(reg int p,reg int d){
		if(sam[p].len<d)
			return 0;
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(f[i][p]&&sam[f[i][p]].len>=d)
				p=f[i][p];
		return p;
	}
	vector< pair<int,int> > qry[MAXV];
	int cnt[MAXN];
	inline void dfs(reg int u){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=son[u]){
				dfs(v);
				for(auto it=edp[v].begin();it!=edp[v].end();++it){
					SegmentTree::update(1,0,1e5,cnt[*it],-1);
					--cnt[*it];
					SegmentTree::update(1,0,1e5,cnt[*it],1);
				}
			}
		}
		if(son[u])
			dfs(son[u]);
		for(auto it=edp[u].begin();it!=edp[u].end();++it){
			SegmentTree::update(1,0,MAXN,cnt[*it],-1);
			++cnt[*it];
			SegmentTree::update(1,0,MAXN,cnt[*it],1);
		}
		if(son[u]){
			edp[u].swap(edp[son[u]]);
			for(auto it=edp[son[u]].begin();it!=edp[son[u]].end();++it)
				edp[u].push_back(*it);
			vector<int>().swap(edp[son[u]]);
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=son[u])
				for(auto it=edp[v].begin();it!=edp[v].end();++it){
					edp[u].push_back(*it);
					SegmentTree::update(1,0,1e5,cnt[*it],-1);
					++cnt[*it];
					SegmentTree::update(1,0,1e5,cnt[*it],1);
				}
		}
		for(auto it=qry[u].begin();it!=qry[u].end();++it)
			ans[it->second]=SegmentTree::query(1,0,1e5,it->first);
		return;
	}
}

int main(void){
	n=read(),q=read(),read(s+1);
	m=strlen(s+1);
	for(reg int i=1;i<=n;++i){
		read(t);
		SAM::las=1;
		reg char *ptr=t;
		while(*ptr)
			SAM::insert(*(ptr++)-'a',i);
	}
	SAM::build();
	for(reg int i=1,x,p=1,l=0;i<=m;++i){
		x=s[i]-'a';
		if(SAM::nex(p)[x])
			p=SAM::nex(p)[x],++l;
		else{
			while(p&&!SAM::nex(p)[x])
				p=SAM::fa(p);
			if(!p)
				p=1,l=0;
			else
				l=SAM::len(p)+1,p=SAM::nex(p)[x];
		}
		ed[i]=p,len[i]=l;
	}
	for(int i=1;i<=q;++i){
		static int l,r,k;
		l=read(),r=read(),k=read();
		if(len[r]>=r-l+1)
			SAM::qry[SAM::get(ed[r],r-l+1)].push_back(make_pair(k,i));
	}
	SegmentTree::update(1,0,1e5,0,n);
	SAM::dfs(1);
	for(reg int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}