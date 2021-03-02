#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)&&*s!='?')*s=getchar();
	while(isdigit(*s)||*s=='?')*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=5e5+5;
const int MAXS=5e5+5;

namespace Trie{
	struct Node{
		int ch[2];
		int fa;
		vector<int> V;
		#define ch(x) unit[(x)].ch
		#define fa(x) unit[(x)].fa
		#define V(x) unit[(x)].V
	};
	int tot;
	Node unit[MAXS<<1];
	inline int insert(reg char s[],reg int len){
		reg int p=0;
		for(reg int i=0;i<len;++i){
			reg int c=s[i]^'0';
			if(!ch(p)[c])
				ch(p)[c]=++tot,fa(ch(p)[c])=p;
			p=ch(p)[c];
		}
		return p;
	}
}

namespace Graph{
	const int MAXV=4*MAXN+2*MAXS;
	vector<int> G[MAXV];
	inline void Add_Edge(reg int u,int v){
		G[u].push_back(v);
		return;
	}
	bool vis[MAXV];
	int tim,dfn[MAXV],low[MAXV];
	int top,S[MAXV];
	int scc_cnt,col[MAXV];
	inline void tarjan(reg int u){
		vis[u]=true;
		dfn[u]=low[u]=++tim;
		S[++top]=u;
		for(int v:G[u])
			if(!dfn[v]){
				tarjan(v);
				low[u]=min(low[u],low[v]);
			}
			else if(vis[v])
				low[u]=min(low[u],dfn[v]);
		if(dfn[u]==low[u]){
			++scc_cnt;
			reg int v;
			do{
				v=S[top--];
				vis[v]=false;
				col[v]=scc_cnt;
			}while(v!=u);
		}
		return;
	}
}

using namespace Trie;
using namespace Graph;

int n;
int pos[MAXN],mat[MAXN<<1];
char s[MAXS];
int len[MAXN];

int main(void){
	n=read();
	reg int las=0;
	for(reg int i=1;i<=n;++i){
		pos[i]=-1;
		read(s+las);
		len[i]=strlen(s+las);
		for(reg int j=las;j<las+len[i];++j){
			if(s[j]=='?'){
				pos[i]=j;
				break;
			}
		}
		if(!~pos[i]){
			Add_Edge(i<<1,i<<1|1);
			mat[i<<1]=mat[i<<1|1]=insert(s+las,len[i]);
		}
		else{
			s[pos[i]]='0',mat[i<<1]=insert(s+las,len[i]);
			s[pos[i]]='1',mat[i<<1|1]=insert(s+las,len[i]);
		}
		las+=len[i];
	}
	reg int sum=(n<<1|1)+2;
	for(reg int i=1;i<=tot;++i){
		Add_Edge(sum+(fa(i)<<1),sum+(i<<1));
		Add_Edge(sum+(i<<1|1),sum+(fa(i)<<1|1));
	}
	for(reg int i=2;i<=(n<<1|1);++i){
		V(mat[i]).push_back(i);
		if(ch(mat[i])[0])
			Add_Edge(i,sum+(ch(mat[i])[0]<<1));
		if(ch(mat[i])[1])
			Add_Edge(i,sum+(ch(mat[i])[1]<<1));
		Add_Edge(i,sum+(fa(mat[i])<<1|1));
		Add_Edge(sum+(mat[i]<<1),i^1);
		Add_Edge(sum+(mat[i]<<1|1),i^1);
	}
	sum+=(tot<<1|1)+2;
	for(reg int i=1;i<=tot;++i){
		if(!V(i).size())
			continue;
		Add_Edge(V(i)[0],sum);
		Add_Edge(sum+1,V(i)[0]^1);
		for(reg int j=1,siz=V(i).size();j<siz;++j){
			Add_Edge(sum+(j<<1|1),sum+((j-1)<<1|1));
			Add_Edge(sum+((j-1)<<1),sum+(j<<1));
			Add_Edge(V(i)[j],sum+(j<<1));
			Add_Edge(sum+(j<<1|1),V(i)[j]^1);
			Add_Edge(V(i)[j],sum+((j-1)<<1|1));
			Add_Edge(sum+((j-1)<<1),V(i)[j]^1);
		}
		sum+=((int)V(i).size()<<1|1)+2;
	}
	for(reg int i=1;i<=sum;++i)
		if(!dfn[i])
			tarjan(i);
	reg bool flag=true;
	for(reg int i=1;i<=n;++i)
		if(col[i<<1]==col[i<<1|1]){
			flag=false;
			break;
		}
	if(flag){
		putchar('Y'),putchar('E'),putchar('S'),putchar('\n');
		reg int las=0;
		for(reg int i=1;i<=n;++i){
			if(~pos[i])
				s[pos[i]]=(col[i<<1|1]<col[i<<1])|'0';
			for(reg int j=las;j<las+len[i];++j)
				putchar(s[j]);
			putchar('\n');
			las+=len[i];
		}
	}
	else
		putchar('N'),putchar('O'),putchar('\n');
	flush();
	return 0;
}