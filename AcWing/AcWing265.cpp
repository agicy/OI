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

const int MAXN=32767+5;

int n;
multiset<int> S;

int main(void){
	int ans=0;
	n=read()-1;
	S.insert(-INF),S.insert(INF);
	S.insert(ans=read());
	while(n--){
		static int a;
		static multiset<int>::iterator it,l,r;
		a=read();
		it=S.insert(a);
		l=--it;
		++it;
		r=++it;
		ans+=min(a-*l,*r-a);
	}
	printf("%d\n",ans);
	return 0;
}