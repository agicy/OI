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

const int MAXK=1e6+5;
const int MAXN=1e6+5;

int k,p,q;
int a[MAXK];
int n;
int ans[MAXN];

struct Node{
	int a,cnt;
	inline Node(reg int a=0,reg int cnt=0):a(a),cnt(cnt){
		return;
	}
	inline bool operator<(const Node& a)const{
		return cnt<a.cnt;
	}
	inline bool operator>(const Node& a)const{
		return cnt>a.cnt;
	}
};

priority_queue<Node,vector<Node>,less<Node>/**/> Q;

inline void Error(void){
	printf("0");
	exit(0);
	return;
}

int main(void){
	k=read(),p=read(),q=read();
	for(reg int i=1;i<=k;++i){
		a[i]=read();
		n+=a[i];
	}
	--a[p],--a[q];
	ans[1]=p,ans[n]=q;
	for(reg int i=3;i<n&&a[p]>0;i+=2)
		if(!ans[i])
			--a[p],ans[i]=p;
	for(reg int i=n-2;i>1&&a[q]>0;i-=2)
		if(!ans[i])
			--a[q],ans[i]=q;
	for(reg int i=1;i<=k;++i)
		if(a[i])
			Q.push(Node(i,a[i]));
	for(reg int i=2;i<n;++i)
		if(!ans[i]){
			static Node u;
			u=Q.top();
			Q.pop();
			reg int a=u.a,cnt=u.cnt;
			if(ans[i-1]==a){
				static Node v;
				v=Q.top();
				Q.pop();
				reg int va=v.a,vcnt=v.cnt;
				if(ans[i-1]==va)
					Error();
				else{
					ans[i]=va;
					if(vcnt-1>0)
						Q.push(Node(va,vcnt-1));
				}
				Q.push(u);
			}
			else{
				ans[i]=a;
				if(cnt-1>0)
					Q.push(Node(a,cnt-1));
			}
		}
	for(reg int i=1;i<n;++i)
		printf("%d ",ans[i]);
	printf("%d",ans[n]);
	return 0;
}
