#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]^=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res^=unit[i];
		return res;
	}
	inline int query(reg int l,reg int r){
		return query(r)^query(l-1);
	}
};

int n,q;
int a[MAXN];
BIT T[2];

int main(void){
	n=read(),q=read();
	T[0].Init(n),T[1].Init(n);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		T[i&1].update(i,a[i]);
	}
	while(q--){
		static int opt,x,y;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 1:{
				reg int val=a[x]^y;
				a[x]^=val;
				T[x&1].update(x,val);
				break;
			}
			case 2:{
				if((x&1)==(y&1))
					printf("%d\n",T[x&1].query(x,y));
				else
					puts("0");
				break;
			}
		}
	}
	return 0;
}