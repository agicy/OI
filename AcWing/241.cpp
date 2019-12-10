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

const int MAXN=200000+5;

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
int y[MAXN];
int l[MAXN],r[MAXN];
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
	for(reg int i=1;i<=n;++i)
		y[i]=read();
	return;
}

inline void Work(void){
	reg ll Ans1=0,Ans2=0;
	T.Init(n);
	for(reg int i=n;i>=1;--i){
		r[i]=n-i-T.Query(y[i]);
		T.Update(y[i],1);
	}
	T.Init(n);
	for(reg int i=1;i<=n;++i){
		l[i]=i-1-T.Query(y[i]);
		T.Update(y[i],1);
	}
	for(reg int i=1;i<=n;++i)
		Ans1+=(ll)l[i]*r[i];
	T.Init(n);
	for(reg int i=n;i>=1;--i){
		r[i]=T.Query(y[i]);
		T.Update(y[i],1);
	}
	T.Init(n);
	for(reg int i=1;i<=n;++i){
		l[i]=T.Query(y[i]);
		T.Update(y[i],1);
	}
	for(reg int i=1;i<=n;++i)
		Ans2+=(ll)l[i]*r[i];
	printf("%lld %lld\n",Ans1,Ans2);
	return;
}
