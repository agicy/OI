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

const int MAXN=10+5;
const int MAXM=10+5;
const int MAXA=1e3+5;

int n,m;
int a[MAXN],b[MAXM];
int sg[MAXA];
bool vis[MAXM];

inline void Init(void){
	for(reg int i=1;i<=1e3;++i){
		memset(vis,false,sizeof(vis));
		for(reg int j=1;j<=m;++j)
		   if(i-b[j]>=0)
			vis[sg[i-b[j]]]=true;
		for(reg int j=0;j<=10;++j)
			if(!vis[j]){
				sg[i]=j;
				break;
			}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	m=read();
	for(reg int i=1;i<=m;++i)
		b[i]=read();
	Init();
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans^=sg[a[i]];
	if(!ans)
		puts("NO");
	else{
		puts("YES");
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				if(sg[a[i]-b[j]]==(ans^sg[a[i]])){
					printf("%d %d\n",i,b[j]);
					return 0;
				}
	}
	return 0;
}