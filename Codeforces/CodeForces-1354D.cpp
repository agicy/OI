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

const int MAXN=2000000+5;

int n,q;

namespace TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN];
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
}

inline void Del(reg int k){
	reg int l=1,r=n,mid,res=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(k<=TreeArray::Query(mid)){
			res=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	TreeArray::Update(res,-1);
	return;
}

int main(void){
	n=read(),q=read();
	TreeArray::Init(n);
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		TreeArray::Update(a,1);
	}
	while(q--){
		static int k;
		k=read();
		if(k<0)
			Del(abs(k));
		else
			TreeArray::Update(k,1);
	}
	if(!TreeArray::Query(n))
		puts("0");
	else
		for(reg int i=1;i<=n;++i)
			if(TreeArray::Query(i)){
				printf("%d\n",i);
				break;
			}
	return 0;
}