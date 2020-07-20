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

const int MAXN=100000+5;

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
		while(ID<=n){
			unit[ID]+=val;
			ID+=lowbit(ID);
		}
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		while(ID){
			res+=unit[ID];
			ID-=lowbit(ID);
		}
		return res;
	}
	#undef lowbit
};

int n;
int a[MAXN];
int ans[MAXN];
TreeArray T;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	for(reg int i=2;i<=n;++i)
		a[i]=read();
	return;
}

inline void Work(void){
	reg int l,r,mid;
	T.Init(n);
	for(reg int i=1;i<=n;++i)
		T.Update(i,1);
	for(reg int i=n;i>=1;--i){
		l=1,r=n;
		while(l<r){
			mid=(l+r)>>1;
			if(T.Query(mid)<a[i]+1)
				l=mid+1;
			else
				r=mid;
		}
		ans[i]=r;
		T.Update(r,-1);
	}
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return;
}
