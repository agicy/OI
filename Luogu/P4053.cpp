#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=150000+5;

struct Node{
	int w,t;
	inline void Read(void){
		w=read(),t=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return t<a.t;
	}
	inline bool operator>(const Node& a)const{
		return t>a.t;
	}
};

int n,T;
Node a[MAXN];
priority_queue<int,vector<int>,less<int>/**/> Q;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	sort(a+1,a+n+1);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(T+a[i].w>a[i].t){
			if(a[i].w<Q.top()){
				T-=Q.top();
				Q.pop();
				T+=a[i].w;
				Q.push(a[i].w);
			}
		}
		else{
			++ans;
			T+=a[i].w;
			Q.push(a[i].w);
		}
	printf("%d\n",ans);
	return 0;
}
