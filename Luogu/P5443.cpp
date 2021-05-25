#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=5e4;
const int MAXM=1e5;
const int MAXQ=1e5;

struct Edge{
	int u,v,d;
};

struct updates{
	int tim,id,val;
	inline updates(reg int tim=0,reg int id=0,reg int val=0):tim(tim),id(id),val(val){
		return;
	}
};

struct querys{
	int id,pos,val;
	inline querys(reg int id=0,reg int pos=0,reg int val=0):id(id),pos(pos),val(val){
		return;
	}
};

inline bool Qcmp_val(const querys& a,const querys& b){
	return a.val>b.val;
}

namespace UnionFind{
	struct Node{
		int fa,siz;
		inline Node(reg int fa=0,reg int siz=0):fa(fa),siz(siz){
			return;
		}
	};
	Node unit[MAXN];
	inline void Init(reg int n){
		for(reg int i=0;i<n;++i)
			unit[i]=Node(i,1);
		return;
	}
	inline int find(reg int x){
		if(x==unit[x].fa)
			return x;
		else
			return unit[x].fa=find(unit[x].fa);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb){
			if(unit[rb].siz<=unit[ra].siz)
				unit[rb].fa=ra,unit[ra].siz+=unit[rb].siz;
			else
				unit[ra].fa=rb,unit[rb].siz+=unit[ra].siz;
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

namespace Graph{
	int cnt,head[MAXN],to[MAXQ],w[MAXQ],Next[MAXQ];
	bool in[MAXN],vis[MAXN];
	int top,S[MAXN];
	inline void Init(void){
		cnt=0;
		while(top){
			reg int u=S[--top];
			in[u]=false,vis[u]=false;
			head[u]=0;
		}
		return;
	}
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v){
		Add_Edge(u,v),Add_Edge(v,u);
		if(!in[u]) in[u]=true,S[top++]=u;
		if(!in[v]) in[v]=true,S[top++]=v;
		return;
	}
	inline int dfs(reg int u){
		if(!in[u]) in[u]=true,S[top++]=u;
		vis[u]=true;
		reg int sum=UnionFind::unit[UnionFind::find(u)].siz;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[v])
				sum+=dfs(v);
		}
		return sum;
	}
}

struct edges{
	int id,u,v,w;
	inline edges(reg int id=0,reg int u=0,reg int v=0,reg int w=0):id(id),u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const edges& a)const{
		return w>a.w;
	}
};

int n,m,q;
Edge e[MAXM];
int cntu,cntq;
updates up[MAXQ];
querys qu[MAXQ];
bool upd[MAXM];
int ans[MAXQ];

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<m;++i)
		e[i].u=read()-1,e[i].v=read()-1,e[i].d=read();
	q=read();
	static edges E[MAXM];
	for(reg int i=0;i<m;++i)
		E[i]=edges(i,e[i].u,e[i].v,e[i].d);
	sort(E,E+m);
	reg int B=max(100,int(0.8*sqrt(m*log2(1.0*m)))),tot=(q+B-1)/B;
	for(reg int i=0;i<tot;++i){
		reg int lef=i*B,rig=min(q-1,(i+1)*B-1);
		cntu=cntq=0;
		for(reg int j=lef;j<=rig;++j){
			static int opt,a,b;
			opt=read(),a=read()-1,b=read();
			switch(opt){
				case 1:{
					up[cntu++]=updates(j,a,b);
					break;
				}
				case 2:{
					qu[cntq++]=querys(j,a,b);
					break;
				}
			}
		}
		reg int top=0;
		static int S[MAXM];
		for(reg int j=0;j<cntu;++j)
			if(!upd[up[j].id])
				upd[up[j].id]=true,S[top++]=up[j].id;
		reg int cnt1=0,cnt2=0;
		static edges tmp1[MAXM],tmp2[MAXM];
		for(reg int j=0;j<m;++j)
			if(!upd[E[j].id])
				tmp1[cnt1++]=E[j];
		UnionFind::Init(n);
		sort(qu,qu+cntq,Qcmp_val);
		for(reg int j=0,ptr=0;j<cntq;++j){
			while(ptr<cnt1&&tmp1[ptr].w>=qu[j].val)
				UnionFind::merge(tmp1[ptr].u,tmp1[ptr].v),++ptr;
			static int val[MAXM];
			for(reg int k=0;k<cntu;++k)
				val[up[k].id]=e[up[k].id].d;
			for(reg int k=0;k<cntu;++k)
				if(up[k].tim<qu[j].id)
					val[up[k].id]=up[k].val;
			Graph::Init();
			for(reg int k=0;k<cntu;++k)
				if(val[up[k].id]>=qu[j].val)
					if(!UnionFind::search(e[up[k].id].u,e[up[k].id].v))
						Graph::Add_Tube(UnionFind::find(e[up[k].id].u),UnionFind::find(e[up[k].id].v));
			ans[qu[j].id]=Graph::dfs(UnionFind::find(qu[j].pos));
		}
		for(reg int j=0;j<cntu;++j)
			e[up[j].id].d=up[j].val;
		for(reg int j=0;j<top;++j){
			reg int id=S[j];
			upd[id]=false;
			tmp2[cnt2++]=edges(id,e[id].u,e[id].v,e[id].d);
		}
		sort(tmp2,tmp2+cnt2);
		reg int ptr1=0,ptr2=0,ptr3=0;
		while(ptr1<cnt1&&ptr2<cnt2)
			if(tmp1[ptr1].w>tmp2[ptr2].w)
				E[ptr3++]=tmp1[ptr1++];
			else
				E[ptr3++]=tmp2[ptr2++];
		while(ptr1<cnt1)
			E[ptr3++]=tmp1[ptr1++];
		while(ptr2<cnt2)
			E[ptr3++]=tmp2[ptr2++];
	}
	for(reg int i=0;i<q;++i)
		if(ans[i])
			writeln(ans[i]);
	flush();
	return 0;
}