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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXM=1000+5;
const int MAXN=2000+5;

int m,n;
int a[MAXM][MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	int T=read();
	while(T--){
		Read();
		Work();
	}
	return 0;
}

inline void Read(void){
	m=read(),n=read();
	for(reg int i=1;i<=m;++i){
		for(reg int j=1;j<=n;++j)
			a[i][j]=read();
		sort(a[i]+1,a[i]+n+1);
	}
	return;
}

struct Node{
	int val,i,j;
	bool last;
	inline Node(void){
		val=i=j=0,last=false;
		return;
	}
	inline Node(reg int a,reg int b,reg int c,reg bool d){
		val=a,i=b,j=c,last=d;
		return;
	}
	inline bool operator<(const Node &a)const{
		return val<a.val;
	}
	inline bool operator>(const Node &a)const{
		return val>a.val;
	}
};

int ans[MAXN],t[MAXN];
int *now;

inline int GetVal(reg int a,reg int b){
	return ans[a]+now[b];
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		ans[i]=a[1][i];
	for(reg int i=2;i<=m;++i){
		now=a[i];
		priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
		while(!Q.empty())
			Q.pop();
		Q.push(Node(GetVal(1,1),1,1,false));
		for(reg int j=1;j<=n;++j){
			Node temp=Q.top();
			Q.pop();
			reg int i_=temp.i,j_=temp.j;
			t[j]=GetVal(i_,j_);
			Q.push(Node(GetVal(i_,j_+1),i_,j_+1,true));
			if(!temp.last)
				Q.push(Node(GetVal(i_+1,j_),i_+1,j_,false));
		}
		for(reg int j=1;j<=n;++j)
			ans[j]=t[j];
	}
	for(reg int i=1;i<=n;++i)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return;
}
