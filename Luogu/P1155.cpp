#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
#define INF 0X3F3F3F3F
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000+5;

int n;
int a[MAXN];
stack<int> SA,SB;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int cnt;
char ans[MAXN<<1];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline bool check(reg int p){
	if(SB.size()==1)
		return true;
	reg int i;
	for(i=p+1;i<=n;++i)
		if(a[i]>a[p]&&a[i]>SB.top())
			break;
	for(reg int j=i+1;j<=n;++j)
		if(a[j]<a[p])
			return false;
	return true;
}

inline void Work(void){
	reg int num=1,p=1;
	SA.push(INF),SB.push(INF);
	for(reg int i=1;i<=(n<<1);++i){
		if(SA.top()==num){
			SA.pop();
			++num;
			ans[++cnt]='b';
		}
		else if(SB.top()==num){
			SB.pop();
			++num;
			ans[++cnt]='d';
		}
		else if(p<=n&&a[p]<SA.top()&&check(p)){
			SA.push(a[p++]);
			ans[++cnt]='a';
		}
		else if(p<=n&&a[p]<SB.top()){
			SB.push(a[p++]);
			ans[++cnt]='c';
		}
		else{
			puts("0");
			return;
		}
	}
	for(reg int i=1;i<=(n<<1);++i)
		printf("%c%c",ans[i],i==(n<<1)?'\n':' ');
	return;
}
