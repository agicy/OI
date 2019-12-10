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

const int MAXN=1000000+5;

int n,b;
int a[MAXN];
priority_queue<int,vector<int>,greater<int>/**/> Q;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),b=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline void Work(void){
	reg int ans=0,dec;
	for(reg int i=1;i<=n;++i)
		Q.push(a[i]);
	ans=dec=Q.top();
	while(b){
		reg int temp;
		for(reg int i=1;i<=dec&&b;++i){
			temp=Q.top();
			Q.pop();
			Q.push(temp+1);
			--b;
		}
		temp=Q.top();
		if(temp==ans)
			break;
		dec=temp-ans;
		ans=temp;
	}
	printf("%d\n",ans);
	return;
}
