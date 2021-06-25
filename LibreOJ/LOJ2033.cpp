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
	while(isdigit(ch)) res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXSIZE=100000+5;

namespace SAM{
	struct Node{
		int dep,fa;
		map<int,int> ch;
	};
	Node p[MAXSIZE<<1];
	int size;
	int last;
	inline void Init(void){
		p[1].dep=0;
		p[1].fa=0;
		last=1;
		size=1;
		return;
	}
	inline int insert(int ch){
		reg int ID=++size,pre=last;
		p[ID].dep=p[last].dep+1;
		while(pre!=0&&p[pre].ch[ch]==0){
			p[pre].ch[ch]=ID;
			pre=p[pre].fa;
		}
		if(pre==0)
			p[ID].fa=1;
		else{
			reg int q=p[pre].ch[ch];
			if(p[pre].dep+1==p[q].dep)
				p[ID].fa=q;
			else{
				reg int clone=++size;
				p[clone]=p[q];
				p[clone].dep=p[pre].dep+1;
				while(pre!=0&&p[pre].ch[ch]==q){
					p[pre].ch[ch]=clone;
					pre=p[pre].fa;
				}
				p[ID].fa=p[q].fa=clone;
			}
		}
		last=ID;
		return p[ID].dep-p[p[ID].fa].dep;
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