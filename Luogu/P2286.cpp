#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 1000000
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

const int MAXN=1000000+5;

int n,ans;
set<int> S;

inline void find(int x){
	static set<int>::iterator l,r;
	l=--S.lower_bound(x),r=S.lower_bound(x);
	if(x-*l<=*r-x&&*l!=-INF){
		ans+=x-*l;
		S.erase(l);
	}
	else{
		ans+=*r-x;
		S.erase(r);
	}
	ans%=MOD;
	return;
}

int main(void){
	n=read();
	S.insert(-INF),S.insert(INF);
	reg int cur;
	while(n--){
		static int a,b;
		a=read(),b=read();
		if(S.size()==2){
			cur=a;
			S.insert(b);
		}
		else if(a==cur)
			S.insert(b);
		else
			find(b);
	}
	printf("%d\n",ans);
	return 0;
}
