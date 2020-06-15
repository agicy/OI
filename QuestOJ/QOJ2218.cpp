#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=800000+5;
const int MAXS=10*MAXN;

namespace SAM{
	struct Node{
		int dep,link,size;
		int next[3];
		#define dep(x) unit[(x)].dep
		#define link(x) unit[(x)].link
		#define next(x) unit[(x)].next
		#define size(x) unit[(x)].size
	};
	int tot;
	Node unit[MAXN<<1];
	inline void Init(void){
		tot=1;
		return;
	}
	inline int insert(reg int last,reg int ch,reg int cnt){
		if(next(last)[ch]&&dep(next(last)[ch])==dep(last)+1){
			size(next(last)[ch])+=cnt;
			return next(last)[ch];
		}
		reg int np=++tot,p=last;
		dep(np)=dep(p)+1;
		while(p&&next(p)[ch]==0){
			next(p)[ch]=np;
			p=link(p);
		}
		if(!p)
			link(np)=1;
		else{
			reg int q=next(p)[ch];
			if(dep(p)+1==dep(q))
				link(np)=q;
			else{
				reg bool flag=false;
				if(dep(np)==dep(p)+1)
					flag=true;
				reg int nq=++tot;
				memcpy(next(nq),next(q),sizeof(next(q)));
				link(nq)=link(q);
				dep(nq)=dep(p)+1;
				link(q)=link(np)=nq;
				while(p&&next(p)[ch]==q){
					next(p)[ch]=nq;
					p=link(p);
				}
				if(flag)
					np=nq;
			}
		}
		size(np)+=cnt;
		return np;
	}
	int tax[MAXN<<1],ord[MAXN<<1];
	ll sum[MAXN<<1];
	inline void build(void){
		for(reg int i=1;i<=tot;++i)
			++tax[dep(i)];
		for(reg int i=1;i<=tot;++i)
			tax[i]+=tax[i-1];
		for(reg int i=1;i<=tot;++i)
			ord[tax[dep(i)]--]=i;
		for(reg int i=tot;i>=1;--i){
			reg int u=ord[i];
			reg int f=link(u);
			size(f)+=size(u);
		}
		for(reg int i=1;i<=tot;++i)
			sum[i]=1ll*size(i)*(dep(i)-dep(link(i)));
		for(reg int i=1;i<=tot;++i){
			reg int u=ord[i];
			reg int f=link(u);
			sum[u]+=sum[f];
		}
		return;
	}
}

namespace Trie{
	const int MAXSIZE=MAXN*2;
	int tot;
	int next[MAXSIZE][3];
	int size[MAXSIZE];
	int spos[MAXSIZE];
	inline void Init(void){
		tot=1;
		return;
	}
	inline int insert(reg int id,reg int ch){
		if(!next[id][ch])
			next[id][ch]=++tot;
		id=next[id][ch];
		++size[id];
		return id;
	}
	queue<int> Q;
	inline void build(void){
		SAM::Init();
		spos[1]=1;
		Q.push(1);
		while(!Q.empty()){
			reg int ID=Q.front();
			Q.pop();
			for(reg int i=0;i<3;++i)
				if(next[ID][i]){
					int v=next[ID][i];
					spos[v]=SAM::insert(spos[ID],i,size[v]);
					Q.push(v);
				}
		}
		return;
	}
}

int n;
int pos[MAXN];
char str[MAXS];

int main(void){
	scanf("%d",&n);
	pos[1]=1;
	Trie::Init();
	for(reg int i=2;i<=n;++i){
		static int fa;
		static char w[4];
		scanf("%d%s",&fa,w);
		pos[i]=Trie::insert(pos[fa],w[0]-'a');
	}
	Trie::build();
	SAM::build();
	scanf("%s",str+1);
	reg int len=strlen(str+1);
	reg ll ans=0;
	reg int p=1;
	int Max=0;
	using namespace SAM;
	for(reg int i=1;i<=len;++i){
		reg int ch=str[i]-'a';
		while(p&&next(p)[ch]==0)
			p=link(p),Max=dep(p);
		if(!p)
			p=1,Max=0;
		else{
			p=next(p)[ch];
			++Max;
			ans+=sum[link(p)];
			ans+=1ll*size(p)*(Max-dep(link(p)));
		}
	}
	printf("%lld\n",ans);
	return 0;
}