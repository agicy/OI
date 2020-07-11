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

const int MAXN=1000000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int a[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

struct Node{
	int l,r;
	double val;
	inline Node(reg int l=0,reg int r=0,reg double val=0):l(l),r(r),val(val){
		return;
	}
};

ll sum[MAXN];
double ans[MAXN];
stack<Node> S;

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	for(reg int i=1;i<=n;++i){
		S.push(Node(i,i,a[i]));
		while(S.size()>=2){
			static Node t1,t2;
			t1=S.top(),S.pop();
			t2=S.top(),S.pop();
			if(t1.val<t2.val){
				reg int l=t2.l,r=t1.r;
				S.push(Node(l,r,(double)(sum[r]-sum[l-1])/(r-l+1)));
			}
			else{
				S.push(t2),S.push(t1);
				break;
			}
		}
	}
	while(!S.empty()){
		static Node N;
		N=S.top();
		S.pop();
		for(reg int i=N.l;i<=N.r;++i)
			ans[i]=N.val;
	}
	for(reg int i=1;i<=n;++i)
		printf("%.9lf\n",ans[i]);
	return;
}
