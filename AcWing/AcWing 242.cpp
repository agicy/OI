#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

int n,m;
int a[MAXN];
TreeArray T;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	T.Init(n);
	while(m--){
		static char ch;
		do
			ch=getchar();
		while(ch!='Q'&&ch!='C');
		if(ch=='Q'){
			static int x;
			x=read();
			printf("%d\n",a[x]+T.Query(x));
		}
		if(ch=='C'){
			static int l,r,d;
			l=read(),r=read(),d=read();
			T.Update(l,d);
			T.Update(r+1,-d);
		}
	}
	return 0;
}