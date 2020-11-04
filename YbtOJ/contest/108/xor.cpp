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
	inline void update(reg int val){
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
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);

	reg int t=read();
	while(t--){
		n=read(),k=read();
		reg ll ans=0;
		Trie::Init();
		Trie::update(0);
		for(reg int i=1,sumx=0;i<=n;++i){
			static int a;
			a=read();
			sumx^=a;
			reg int p=1;
			reg ll res=0;
			for(reg int j=MAXLOGA-1;j>=0;--j){
				if(!p)
					break;
				if((sumx>>j)&1)
					if((k>>j)&1)
						p=Trie::ch(p)[0];
					else{
						res+=Trie::sum(Trie::ch(p)[0]);
						p=Trie::ch(p)[1];
					}
				else
					if((k>>j)&1)
						p=Trie::ch(p)[1];
					else{
						res+=Trie::sum(Trie::ch(p)[1]);
						p=Trie::ch(p)[0];
					}
			}
			ans+=res+Trie::sum(p);
			Trie::update(sumx);
		}
		printf("%lld\n",ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}