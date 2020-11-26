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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e6+5;

int n;
int a[MAXN<<1];
deque<int> Q;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=a[n+i]=read();
	int ans=0;
	Q.push_back(1);
	for(int i=2;i<=(n<<1);++i){
		while(!Q.empty()&&Q.front()<i-(n>>1))Q.pop_front();
		if(!Q.empty())
			ans=max(ans,a[i]+a[Q.front()]+i-Q.front());
		while(!Q.empty()&&a[Q.back()]-Q.back()<a[i]-i)Q.pop_back();
		Q.push_back(i);
	}
	printf("%d\n",ans);
	return 0;
}