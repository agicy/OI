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

const int MAXN=100+5;

int n;
int idt;
int ans[MAXN];

inline bool DFS(reg int dep){
	if(dep==idt+1)
		return ans[idt]==n;
	bool vis[MAXN];
	memset(vis,false,sizeof(vis));
	for(reg int i=dep-1;i>=1;--i){
		for(reg int j=i;j>=1;--j){
			if(ans[i]+ans[j]>n)
				continue;
			if(vis[ans[i]+ans[j]])
				continue;
			if(ans[i]+ans[j]<=ans[dep-1])
				return false;
			ans[dep]=ans[i]+ans[j];
			vis[ans[dep]]=true;
			if(DFS(dep+1))
				return true;
		}
	}
	return false;
}

int main(void){
	while(n=read(),n!=0){
		ans[1]=1,ans[2]=2;
		if(n==1)
			puts("1");
		else if(n==2)
			puts("1 2");
		else
			for(idt=3;;++idt){
				if(DFS(3)){
					for(reg int i=1;i<=idt;++i)
						printf("%d%c",ans[i],i==idt?'\n':' ');
					break;
				}
			}
	}
	return 0;
}
