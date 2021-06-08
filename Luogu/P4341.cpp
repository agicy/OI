#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e3+5;

namespace Trie{
	const int MAXSIZE=MAXN*MAXN;
	struct Node{
		int ch[2];
		int cnt;
		#define ch(x) unit[(x)].ch
		#define cnt(x) unit[(x)].cnt
	};
	const int rt=0;
	int tot;
	Node unit[MAXSIZE];
	inline void insert(reg char s[],reg int n){
		reg int p=rt;
		for(reg int i=1;i<=n;++i){
			reg int c=s[i]-'0';
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
			++cnt(p);
		}
		return;
	}
	inline void dfs(reg int p=rt){
		if(cnt(p)>1) writeln(cnt(p));
		if(ch(p)[0]) dfs(ch(p)[0]);
		if(ch(p)[1]) dfs(ch(p)[1]);
		return;
	}
	#undef ch
	#undef cnt
}

int n;
char s[MAXN];

bool ed;

int main(void){
	scanf("%d%s",&n,s+1);
	for(reg int i=1;i<=n;++i)
		Trie::insert(s+i-1,n-i+1);
	Trie::dfs();
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}