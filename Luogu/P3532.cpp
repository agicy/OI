#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXA=1e6+5;
const int inf=0x3f3f3f3f;

bool vis[MAXA];
int tot,prime[MAXA];
int w[MAXA];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			w[i]=1;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			w[i*prime[j]]=w[i]+1;
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

int n;
int a[MAXN];
int Min[MAXA],cMin[MAXA];

inline void update(reg int d,reg int pos){
	if(w[a[Min[d]]]>w[a[pos]]){
		cMin[d]=Min[d];
		Min[d]=pos;
	}
	else if(w[a[cMin[d]]]>w[a[pos]]&&pos!=Min[d])
		cMin[d]=pos;
	return;
}

int val,ans;

inline void check(reg int d,reg int pos){
	reg int x=(Min[d]==pos)?cMin[d]:Min[d];
	reg int dis=w[a[pos]]+w[a[x]]-2*w[d];
	if(dis<val||(dis==val&&x<ans))
		val=dis,ans=x;
	return;
}

int main(void){
	w[0]=inf;
	Init(1e6);
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j*j<=a[i];++j)
			if(a[i]%j==0){
				update(j,i),update(a[i]/j,i);
			}
	for(reg int i=1;i<=n;++i){
		val=inf;
		for(reg int j=1;j*j<=a[i];++j)
			if(a[i]%j==0)
				check(j,i),check(a[i]/j,i);
		printf("%d\n",ans);
	}
	return 0;
}