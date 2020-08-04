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

const int MAXN=5e4+5;
const int MAXK=10+5;

int n,k;

struct Node{
	int size,Max[15],Min[15];
	inline Node(void){
		memset(Max,0,sizeof(Max));
		memset(Min,0X3F,sizeof(Min));
		return;
	}
	inline bool operator<(const Node& a)const{
		for(reg int i=1;i<=k;++i)
			if(Max[i]>a.Min[i])
				return false;
		return true;
	}
};

set<Node> S;
Node s;

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i){
		s.size=1;
		for(reg int j=1;j<=k;++j)
			s.Max[j]=s.Min[j]=read();
		set<Node>::iterator it;
		while((it=S.find(s))!=S.end()){
			s.size+=it->size;
			for(reg int j=1;j<=k;++j){
				s.Min[j]=min(s.Min[j],it->Min[j]);
				s.Max[j]=max(s.Max[j],it->Max[j]);
			}
			S.erase(it);
		}
		S.insert(s);
		printf("%d\n",(--S.end())->size);
	}
	return 0;
}