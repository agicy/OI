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
const int P=99991;

int n;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int a[6];
	inline void Read(void){
		for(reg int i=0;i<6;++i)
			a[i]=read();
		return;
	}
	inline int H(void)const{
		reg int sum1=0,sum2=1;
		for(reg int i=0;i<6;++i)
			sum1=(sum1+a[i])%P,sum2=(ll)sum2*a[i]%P;
		return (sum1+sum2)%P;
	}
	inline bool operator==(const Node& x)const{
		for(reg int i=0;i<6;++i){
			for(reg int j=0;j<6;++j){
				reg bool flag1=true,flag2=true;
				for(reg int k=0;k<6;++k)
					flag1&=(a[(i+k)%6]==x.a[(j+k)%6]),
					flag2&=(a[(i+k)%6]==x.a[(j-k+6)%6]);
				if(flag1||flag2)
					return true;
			}
		}
		return false;
	}
};

struct HashList{
	int cnt;
	int head[MAXN],Next[MAXN];
	Node snow[MAXN];
	inline HashList(void){
		cnt=0;
		memset(head,0,sizeof(head));
		return;
	}
	inline bool Insert(const Node& a){
		reg int val=a.H();
		for(reg int i=head[val];i;i=Next[i])
			if(a==snow[i])
				return true;
		Next[++cnt]=head[val];
		snow[cnt]=a;
		head[val]=cnt;
		return false;
	}
};

Node a[MAXN];
HashList L;

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		if(L.Insert(a[i])){
			puts("Twin snowflakes found.");
			return;
		}
	puts("No two snowflakes are alike.");
	return;
}
