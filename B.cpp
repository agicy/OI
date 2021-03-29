#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=3e3+5;

int n;
char s[MAXN],t[MAXN];

namespace Subtask1{
	inline void Solve(void){
		printf("%d\n",n);
		return;
	}
}

namespace Subtask2{
	const int MAXN=100+5;
	const ull base=1331;
	ull basep[MAXN];
	ull Hash[MAXN];
	inline ull getHash(reg int l,reg int r){
		return Hash[r]-Hash[l-1]*basep[r-l+1];
	}
	set<ull> M;
	inline void Solve(void){
		basep[0]=1;
		for(reg int i=1;i<=n;++i){
			basep[i]=basep[i-1]*base;
			Hash[i]=Hash[i-1]*base+(t[i]-'a'+1);
		}
		reg int ans=0;
		for(reg int l=1;l<=n;++l)
			for(reg int r=l;r<=n;++r){
				if(M.find(getHash(l,r))==M.end()){
					M.insert(getHash(l,r));
					reg int ptr=l;
					for(reg int i=1;i<=n;++i)
						if(ptr<=r&&s[i]==t[ptr])
							++ptr;
					if(ptr==r+1)
						++ans;
				}
			}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask4{
	const int MAXN=3e3+5;
	const ull base=1331;
	ull basep[MAXN];
	ull Hash[MAXN];
	inline ull getHash(reg int l,reg int r){
		return Hash[r]-Hash[l-1]*basep[r-l+1];
	}
	set<ull> M;
	inline void Solve(void){
		basep[0]=1;
		for(reg int i=1;i<=n;++i){
			basep[i]=basep[i-1]*base;
			Hash[i]=Hash[i-1]*base+(t[i]-'a'+1);
		}
		reg int ans=0;
		for(reg int l=1;l<=n;++l){
			reg int ptr=l-1;
			for(reg int i=1;i<=n;++i){
				if(ptr<n&&s[i]==t[ptr+1]){
					++ptr;
					if(M.find(getHash(l,ptr))==M.end()){
						M.insert(getHash(l,ptr));
						++ans;
					}
					if(ptr==n)
						break;
				}
			}
		}
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	n=read();
	read(s+1),read(t+1);
	Subtask4::Solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}