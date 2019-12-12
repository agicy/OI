#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

struct Node{
	int ID;
	ll val;
	inline Node(reg int a,reg ll b){
		ID=a,val=b;
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

int n;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	return;
}

inline void Work(void){
	set<Node> S;
	set<Node>::iterator it1,it2;
	S.clear();
	S.insert(Node(0,INT_MIN));
	S.insert(Node(0,INT_MAX));
	for(reg int i=1;i<=n;++i){
		static ll v;
		v=read();
		if(i>=2){
			it2=S.upper_bound(Node(0,v));
			it1=it2;
			--it1;
			reg ll pre=v-it1->val,las=it2->val-v;
			if(pre<=las)
				printf("%lld %d\n",pre,it1->ID);
			else
				printf("%lld %d\n",las,it2->ID);
		}
		S.insert(Node(i,v));
	}
	return;
}
