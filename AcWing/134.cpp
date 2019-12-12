#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=200000+5;

struct Node{
	int ID,val;
	inline void Read(reg int i){
		ID=i;
		val=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

int n;
Node d[MAXN];

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
		d[i].Read(i);
	return;
}

inline void Work(void){
	sort(d+1,d+n+1);
	reg int last=INF;
	reg int flag=-1;
	reg int ans=0,r;
	for(reg int i=1;i<=n;i=r+1){
		r=i;
		int Max=-INF,Min=INF;
		while(r+1<=n&&d[r].val==d[r+1].val)
			Min=min(Min,d[r].ID),Max=max(Max,d[r].ID),++r;
		Min=min(Min,d[r].ID),Max=max(Max,d[r].ID);
		if(flag==-1)
			if(Max<last)
				last=Min;
			else
				flag=1,last=Max;
		else
			if(last<Min)
				last=Max;
			else
				++ans,last=Min,flag=-1;
	}
	printf("%d\n",ans+1);
	return;
}
