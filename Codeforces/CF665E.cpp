#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e6+5;
const int MAXLOGA=29+1;

namespace Trie{
	const int MAXSIZE=MAXN*35;
	struct Node{
		int ch[2];
		int sum;
		#define ch(x) unit[(x)].ch
		#define sum(x) unit[(x)].sum
	};
	int rt,tot;
	Node unit[MAXSIZE];
	inline int New(void){
		reg int id=++tot;
		ch(id)[0]=ch(id)[1]=sum(id)=0;
		return id;
	}
	inline void Init(void){
		tot=0;
		rt=New();
		return;
	}
	inline void insert(reg int val){
		reg int p=rt;
		for(reg int i=MAXLOGA-1;i>=0;--i){
			reg int c=(val>>i)&1;
			if(!ch(p)[c])
				ch(p)[c]=New();
			p=ch(p)[c];
			++sum(p);
		}
		return;
	}
}

int n,k;

int main(void){
	n=read(),k=read();
	reg ll ans=0;
	Trie::Init();
	Trie::insert(0);
	for(reg int i=1,sumx=0;i<=n;++i){
		static int a;
		a=read();
		sumx^=a;
		reg int p=Trie::rt;
		reg ll res=0;
		for(reg int j=MAXLOGA-1;j>=0;--j){
			if(!p)
				break;
			if(!((k>>j)&1))
				res+=Trie::sum(Trie::ch(p)[!((sumx>>j)&1)]);
			p=Trie::ch(p)[((sumx^k)>>j)&1];
		}
		ans+=res+Trie::sum(p);
		Trie::insert(sumx);
	}
	printf("%lld\n",ans);
	return 0;
}