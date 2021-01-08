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

const int MAXN=1e4+5;
const int MAXSIZE=7.2e5+5;

int n,m;

namespace SAM{
	struct Node{
		int next[26];
		int dep,link,size;
		int last;
		#define next(x) unit[(x)].next
		#define dep(x) unit[(x)].dep
		#define link(x) unit[(x)].link
		#define size(x) unit[(x)].size
		#define last(x) unit[(x)].last
	};
	int tot,last;
	Node unit[MAXSIZE];
	inline void Init(void){
		tot=last=1;
		return;
	}
	inline void insert(reg int ch){
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
				reg int nq=++tot;
				memcpy(next(nq),next(q),sizeof(next(q)));
				link(nq)=link(q);
				dep(nq)=dep(p)+1;
				link(q)=link(np)=nq;
				while(p&&next(p)[ch]==q){
					next(p)[ch]=nq;
					p=link(p);
				}
			}
		}
		last=np;
		return;
	}
	inline void update(int x,int y){
		while(x&&last(x)!=y){
			++size(x),last(x)=y;
			x=link(x);
		}
		return;
	}
}

int s[MAXSIZE];
int len[MAXN];

int main(void){
	n=read(),m=read();
	SAM::Init();
	reg int cnt=0;
	for(reg int i=1;i<=n;++i){
		SAM::last=1;
		reg char ch=getchar();
		while(ch!='\n'){
			SAM::insert(s[++cnt]=ch-'a');
			++len[i];
			ch=getchar();
		}
	}
	cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1,x=1;j<=len[i];++j)
			SAM::update(x=SAM::next(x)[s[++cnt]],i);
	while(m--){
		reg bool flag=true;
		reg char ch=getchar();
		reg int p=1;
		while(ch!='\n'&&ch!=EOF){
			reg int k=ch-'a';
			if(flag){
				if(SAM::next(p)[k])
					p=SAM::next(p)[k];
				else
					flag=false;
			}
			ch=getchar();
		}
		printf("%d\n",flag?SAM::size(p):0);
	}
	return 0;
}