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

const int MAXN=300000+5;
const int MAXM=1000000+5;

struct Node{
	int ID,l,r;
	inline void Read(reg int i){
		ID=i;
		l=read(),r=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return r<a.r;
	}
};

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	int unit[MAXN];
	inline void Init(reg int size){
		n=size;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,reg int val){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

int n,m;
int c[MAXN],pre[MAXN],last[MAXN];
int ans[MAXM];
Node S[MAXM];
TreeArray T;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		c[i]=read();
		pre[i]=last[c[i]];
		last[c[i]]=i;
	}
	m=read();
	for(reg int i=1;i<=m;++i)
		S[i].Read(i);
	sort(S+1,S+m+1);
	T.Init(n);
	for(reg int i=1,cnt=1;i<=n;++i){
		T.Update(i,1);
		if(pre[i])
			T.Update(pre[i],-1);
		while(cnt<=m&&S[cnt].r==i){
			ans[S[cnt].ID]=T.Query(S[cnt].r)-T.Query(S[cnt].l-1);
			++cnt;
		}
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
