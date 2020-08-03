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

inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Read();
		Work();
	}
	return 0;
}

struct Node{
	ll x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
};

int n;
Node a[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i].Read();
	return;
}

inline ll GetLen(const Node& a,const Node& b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

inline ll GetAng(const Node& a,const Node& b,const Node& c){
	return (a.x-b.x)*(c.y-b.y)-(c.x-b.x)*(a.y-b.y);
}

ll s[MAXN<<2];
int len[MAXN<<2];

inline void Work(void){
	for(reg int i=0;i<n;++i){
		s[i<<1]=GetAng(a[(i-1+n)%n],a[i],a[(i+1)%n]);
		s[i<<1|1]=GetLen(a[i],a[(i+1)%n]);
	}
	for(reg int i=0;i<n;++i)
		s[i+(n<<1)]=s[i];
	reg int r=0,mid=0;
	for(reg int i=0;i<(n<<2);++i){
		if(i<r)
			len[i]=min(r-i,len[(mid<<1)-i]);
		else
			len[i]=1;
		while(i-len[i]>=0&&i+len[i]<(n<<2)&&s[i+len[i]]==s[i-len[i]])
			++len[i];
		if(i+len[i]>r){
			r=i+len[i];
			mid=i;
		}
	}
	reg int ans=0;
	for(reg int i=0;i<(n<<2);++i)
		if(len[i]>=n+1)
			++ans;
	printf("%d\n",ans);
	return;
}