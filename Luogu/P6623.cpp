#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=525010+500;
const int MAXV=525010+500;

int n;
int v[MAXN];

int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

const int MAXNV=MAXN+MAXV;
const int MAXLOG2NV=26+1;

namespace Trie{
	struct Node{
		int val,cnt,dep;
		int ch[2];
		#define val(x) unit[(x)].val
		#define cnt(x) unit[(x)].cnt
		#define dep(x) unit[(x)].dep
		#define ch(x) unit[(x)].ch
	};
	int tot;
	int top,S[MAXNV*4];
	Node unit[MAXNV*4];
	inline int New(void){
		if(top)
			return S[top--];
		else
			return ++tot;
	}
	inline void Del(reg int k){
		val(k)=cnt(k)=ch(k)[0]=ch(k)[1]=0;
		S[++top]=k;
		return;
	}
	inline void pushup(reg int k){
		cnt(k)=val(k)=0;
		if(ch(k)[0]){
			cnt(k)+=cnt(ch(k)[0]);
			val(k)^=val(ch(k)[0]);
		}
		if(ch(k)[1]){
			cnt(k)+=cnt(ch(k)[1]);
			val(k)^=(cnt(ch(k)[1])&1)<<dep(k)^val(ch(k)[1]);
		}
		return;
	}
	inline void insert(reg int root,reg int depth,reg int val){
		dep(root)=depth;
		if(depth==MAXLOG2NV-1){
			++cnt(root);
			return;
		}
		reg int c=(val>>depth)&1;
		if(!ch(root)[c])
			ch(root)[c]=New();
		insert(ch(root)[c],depth+1,val);
		pushup(root);
		return;
	}
	inline int merge(reg int a,reg int b){
		if(!a||!b)
			return a+b;
		val(a)^=val(b);
		cnt(a)+=cnt(b);
		ch(a)[0]=merge(ch(a)[0],ch(b)[0]);
		ch(a)[1]=merge(ch(a)[1],ch(b)[1]);
		Del(b);
		return a;
	}
	inline void modify(reg int root){
		swap(ch(root)[0],ch(root)[1]);
		if(ch(root)[0])
			modify(ch(root)[0]);
		pushup(root);
		return;
	}
}

using namespace Trie;

int root[MAXN];
ll ans;

inline void DFS(reg int ID,reg int father){
	root[ID]=New();
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS(to[i],ID);
			root[ID]=merge(root[ID],root[to[i]]);
		}
	modify(root[ID]);
	insert(root[ID],0,v[ID]);
	ans+=val(root[ID]);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read();
	for(reg int i=2;i<=n;++i){
		static int p;
		p=read();
		Add_Edge(p,i);
	}
	DFS(1,0);
	printf("%lld\n",ans);
	return 0;
}