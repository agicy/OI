#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=4e5+5;
const int MAXQ=4e5+5;

struct querys{
	int l,r;
};

int n,Q;
char s[MAXN];
querys q[MAXQ];

namespace Subtask1{
	const int MAXN=300+5;
	const ull p=1331;
	ull basep[MAXN];
	ull Hash[MAXN];
	unordered_map<ull,bool> M;
	inline ull getHash(reg int l,reg int r){
		return Hash[r]-Hash[l-1]*basep[r-l+1];
	}
	int kmp[MAXN];
	char T[MAXN];
	inline void Solve(void){
		basep[0]=1;
		for(reg int i=1;i<=n;++i){
			basep[i]=basep[i-1]*p;
			Hash[i]=Hash[i-1]*p+(s[i]-'a'+1);
		}
		for(reg int i=1;i<=Q;++i){
			for(reg int j=q[i].l;j<=q[i].r;++j)
				T[j-q[i].l+1]=s[j];
			reg int len=q[i].r-q[i].l+1;
			for(reg int j=2,k=0;j<=len;++j){
				while(k&&T[k+1]!=T[j])
					k=kmp[k];
				if(T[k+1]==T[i])
					++k;
				kmp[j]=k;
			}
			reg int cnt=0;
			M.clear();
			for(reg int l=1;l<=n;++l)
				for(reg int r=l;r<=n;++r){
					if(!M[getHash(l,r)]){
						M[getHash(l,r)]=true;
						for(reg int ptr=l,j=0;ptr<=r;++ptr){
							while(j&&T[j+1]!=s[ptr])
								j=kmp[j];
							if(T[j+1]==s[ptr])
								++j;
							if(j==len){
								++cnt,j=kmp[j];
							}
						}
					}
				}
			printf("%d\n",cnt);
		}
		return;
	}
}

int main(void){
	n=read(),Q=read();
	read(s+1);
	for(reg int i=1;i<=Q;++i)
		q[i].l=read(),q[i].r=read();
	Subtask1::Solve();
	flush();
	return 0;
}