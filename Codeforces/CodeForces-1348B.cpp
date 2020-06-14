#include<bits/stdc++.h>
using namespace std;
#define reg register
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

int a[MAXN];
int cnt[MAXN];
int p[MAXN];

int main(void){
	reg int T=read();
	while(T--){
		reg int n=read(),K=read();
		for(reg int i=1;i<=n;++i)
			cnt[i]=0;
		reg int tot=0;
		for(reg int i=1;i<=n;++i){
			a[i]=read();
			if(!cnt[a[i]])
				++tot;
			++cnt[a[i]];
		}
		if(tot>K)
			puts("-1");
		else{
			reg int T=0;
			for(reg int i=1;i<=n;++i)
				if(cnt[i])
					p[T++]=i;
			for(reg int i=1;i<=n&&tot!=K;++i)
				if(!cnt[i]){
					p[T++]=i;
					++tot;
				}
			vector<int> ans;
			for(reg int ptr=1,i=0;ptr<=n;++ptr){
				while(p[i]!=a[ptr]){
					ans.push_back(p[i]);
					i=(i+1)%T;
				}
				ans.push_back(p[i]);
				i=(i+1)%T;
			}
			printf("%llu\n",ans.size());
			for(reg int i=0,size=ans.size();i<size;++i)
				printf("%d%c",ans[i],i==size-1?'\n':' ');
		}
	}
	return 0;
}