#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int x;
		x=read();
		if(!x)
			continue;
		if(!cnt||(ll)a[cnt]*x<0)
			a[++cnt]+=x;
		else
			a[cnt]+=x;
	}
	return;
}

struct Node{
	int val,ID;
	inline Node(void){
		val=ID=0;
		return;
	}
	inline Node(reg int a,reg int b){
		val=a,ID=b;
		return;
	}
	inline bool operator<(const Node &a)const{
		return val<a.val;
	}
	inline bool operator>(const Node &a)const{
		return val>a.val;
	}
};

bool vis[MAXN];
int l[MAXN],r[MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void Del(reg int x){
	l[r[x]]=l[x];
	r[l[x]]=r[x];
	vis[x]=true;
	return;
}

inline void Work(void){
	n=cnt;
	cnt=0;
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		l[i]=i-1,r[i]=i+1;
		Q.push(Node(abs(a[i]),i));
		if(a[i]>0){
			ans+=a[i];
			++cnt;
		}
	}
	//printf("%d %d\n",n,cnt);
	Node temp;
	while(cnt>m){
		temp=Q.top();
		Q.pop();
		if(vis[temp.ID]){
			continue;
		}
		if(a[temp.ID]>0||(l[temp.ID]!=0&&r[temp.ID]!=n+1)){
			ans-=temp.val;
			a[temp.ID]+=a[l[temp.ID]]+a[r[temp.ID]];
			Q.push(Node(abs(a[temp.ID]),temp.ID));
			Del(r[temp.ID]);
			Del(l[temp.ID]);
			--cnt;
		}
	}
	printf("%d\n",ans);
	return;
}
