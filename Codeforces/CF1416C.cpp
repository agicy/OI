#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=3e5+5;
const int MAXLOG2A=30;

ll f[2][MAXLOG2A];

namespace Trie{
	const int MAXSIZE=MAXN*MAXLOG2A;
	struct Node{
		int ch[2];
		vector<int> V;
		#define ch(x) unit[(x)].ch
		#define V(x) unit[(x)].V
	};
	int tot;
	Node unit[MAXSIZE];
	inline void insert(reg int p,reg int dep,reg int val,int id){
		if(dep==-1)
			return;
		reg int c=(val>>dep)&1;
		if(!ch(p)[c])
			ch(p)[c]=++tot;
		V(ch(p)[c]).push_back(id);
		insert(ch(p)[c],dep-1,val,id);
		return;
	}
	inline void dfs(reg int p,reg int dep){
		if(ch(p)[0])
			dfs(ch(p)[0],dep-1);
		if(ch(p)[1])
			dfs(ch(p)[1],dep-1);
		if(!ch(p)[0]&&!ch(p)[1])
			return;
		reg int ptr=0;
		reg ll res=0;
		for(int i:V(ch(p)[0])){
			while(ptr<(int)V(ch(p)[1]).size()&&V(ch(p)[1])[ptr]<i)
				++ptr;
			res+=ptr;
		}
		f[0][dep]+=res;
		f[1][dep]+=1ll*V(ch(p)[0]).size()*V(ch(p)[1]).size()-res;
		return;
	}
}

int n;

int main(void){
	n=read();
	reg int rt=0;
	for(reg int i=1;i<=n;++i){
		reg int a=read();
		Trie::insert(rt,MAXLOG2A-1,a,i);
	}
	Trie::dfs(rt,MAXLOG2A-1);
	reg ll ans1=0;
	reg int ans2=0;
	for(reg int i=MAXLOG2A-1;i>=0;--i){
		ans1+=min(f[0][i],f[1][i]);
		if(f[1][i]<f[0][i])
			ans2|=(1<<i);
	}
	printf("%lld %d\n",ans1,ans2);
	return 0;
}