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

const int MAXN=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n;
int a[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

int sum[MAXN];
vector<int> V;

inline void Work(void){
	for(reg int i=1;i<=n;++i){
		sum[i]=sum[i-1]+a[i];
		V.push_back(sum[i]);
	}
	sort(V.begin(),V.end());
	if(V[0]<=0){
		puts("-1");
		return;
	}
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		sum[i]=lower_bound(V.begin(),V.end(),sum[i])-V.begin()+1;
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		while(sum[i]!=i){
			++ans;
			swap(sum[i],sum[sum[i]]);
		}
	printf("%d\n",ans);
	return;
}
