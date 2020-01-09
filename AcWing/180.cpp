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

const int MAXN=15+5;

inline void Read(void);
inline void Work(void);

int main(void){
	int T=read();
	while(T--){
		Read();
		Work();
	}
	return 0;
}

struct Node{
	int n;
	int a[MAXN];
	inline Node(void){
		n=0;
		memset(a,0,sizeof(a));
		return;
	}
	inline void Read(reg int size){
		n=size;
		for(reg int i=0;i<n;++i)
			a[i]=read();
		GetVal();
		return;
	}
	inline int GetVal(void){
		reg int res=0;
		for(reg int i=0;i<n-1;++i)
			if(a[i+1]!=a[i]+1)
				++res;
		return res;
	}
	inline bool check(void){
		return GetVal()==0;
	}
};

int n;
Node a;
int id;

inline void Read(void){
	n=read();
	a.Read(n);
	return;
}

inline bool DFS(reg int dep,Node a){
	if((a.GetVal()+2)/3+dep-1>id)
		return false;
	if(dep>id+1)
		return false;
	if(dep==id+1){
		if(a.check())
			return true;
		return false;
	}
	for(reg int l=0;l<n;++l)
		for(reg int len=1;l+len-1<n;++len){
			for(reg int j=0;j<l;++j){
				reg int r=l+len-1;
				Node temp=a;
				for(reg int k=r;k-len>=j;--k)
					temp.a[k]=temp.a[k-len];
				int T[len];
				for(reg int k=0;k<len;++k)
					T[k]=a.a[l+k];
				for(reg int k=0;k<len;++k)
					temp.a[j+k]=T[k];
				if(DFS(dep+1,temp))
					return true;
			}
		}
	return false;
}

inline void Work(void){
	if(a.check()){
		puts("0");
		return;
	}
	for(reg int i=1;i<=4;++i){
		id=i;
		if(DFS(1,a)){
			printf("%d\n",i);
			return;
		}
	}
	puts("5 or more");
	return;
}
