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

const int MAXSIZE=100000+5;

namespace SAM{
	struct Node{
		int dep,link;
		map<int,int> next;
	};
	Node p[MAXSIZE<<1];
	int size;
	int last;
	inline void Init(void){
		p[1].dep=0;
		p[1].link=0;
		last=1;
		size=1;
		return;
	}
	inline int insert(int ch){
		reg int ID=++size,pre=last;
		p[ID].dep=p[last].dep+1;
		while(pre!=0&&p[pre].next[ch]==0){
			p[pre].next[ch]=ID;
			pre=p[pre].link;
		}
		if(pre==0)
			p[ID].link=1;
		else{
			reg int q=p[pre].next[ch];
			if(p[pre].dep+1==p[q].dep)
				p[ID].link=q;
			else{
				reg int clone=++size;
				p[clone]=p[q];
				p[clone].dep=p[pre].dep+1;
				while(pre!=0&&p[pre].next[ch]==q){
					p[pre].next[ch]=clone;
					pre=p[pre].link;
				}
				p[ID].link=p[q].link=clone;
			}
		}
		last=ID;
		return p[ID].dep-p[p[ID].link].dep;
	}
}

using namespace SAM;

int n;

int main(void){
	n=read();
	SAM::Init();
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		ans+=insert(x);
		printf("%lld\n",ans);
	}
	return 0;
}