#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int long long
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAX=1e6+5;

int m,n;
bool key[MAX],vis[MAX];
int tot,ans[MAX];
int Max,las[MAX];

signed main(void){
	m=read();
	for(reg int i=1;i<=m;++i)
		key[read()]=true;
	n=read();
	Max=1e6;
	vis[0]=1;
	reg int id=0;
	while(n--){
		reg int x=read();
		reg int &ptr=las[x];
		reg int cnt=x;
		for(;cnt;cnt--){
			while(ptr<=Max&&vis[ptr])
				ptr+=x;
			if(ptr>Max)
				break;
			vis[ptr]=true;
			++id;
			if(key[ptr])
				ans[++tot]=id;
		}
		id+=cnt;
	}
	printf("%lld\n",tot);
	for(reg int i=1;i<=tot;++i)
		printf("%lld\n",ans[i]);
	return 0;
}