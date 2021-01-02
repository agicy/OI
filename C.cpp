#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=5e5+5;
const int MAXS=1e7+5;

char s[MAXN];
int cnt;
char T[MAXS];

namespace SAM{
	struct Node{
		int ch[26];
		int dep,fa,siz;
		#define ch(x) unit[(x)].ch
		#define dep(x) unit[(x)].dep
		#define fa(x) unit[(x)].fa
		#define siz(x) unit[(x)].siz
	};
	int tot,last;
	Node unit[MAXN<<1];
	inline void Init(void){
		tot=last=1;
		return;
	}
	inline void insert(reg int ch){
		reg int np=++tot,p=last;
		dep(np)=dep(p)+1;
		siz(np)=1;
		while(p&&ch(p)[ch]==0){
			ch(p)[ch]=np;
			p=fa(p);
		}
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[ch];
			if(dep(p)+1==dep(q))
				fa(np)=q;
			else{
				reg int nq=++tot;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q);
				dep(nq)=dep(p)+1;
				while(p&&ch(p)[ch]==q){
					ch(p)[ch]=nq;
					p=fa(p);
				}
				fa(np)=fa(q)=nq;
			}
		}
		last=np;
		return;
	}
	int t[MAXN<<1],A[MAXN<<1];
	ll sum[MAXN<<1];
	inline void build(void){
		for(reg int i=1;i<=tot;++i)
			++t[dep(i)];
		for(reg int i=1;i<=tot;++i)
			t[i]+=t[i-1];
		for(reg int i=1;i<=tot;++i)
			A[t[dep(i)]--]=i;
		for(reg int i=tot;i>=1;--i)
			siz(fa(A[i]))+=siz(A[i]);
		for(reg int i=1;i<=tot;++i)
			sum[i]=siz(i)=1;
		siz(1)=sum[1]=0;
		for(reg int i=tot;i>=1;--i)
			for(reg int j=0;j<26;++j)
				if(ch(A[i])[j])
					sum[A[i]]+=sum[ch(A[i])[j]];
		return;
	}
	inline void Print(reg int p,reg int k){
		if(k<=siz(p))
			return;
		k-=siz(p);
		for(reg int i=0;i<26;++i)
			if(ch(p)[i]){
				if(k>sum[ch(p)[i]])
					k-=sum[ch(p)[i]];
				else{
					if(cnt<MAXS)
						T[cnt++]=i+'a';
					Print(ch(p)[i],k);
					break;
				}
			}
		return;
	}
}

int main(void){
	read(s+1);
	reg int len=strlen(s+1);
	SAM::Init();
	for(reg int i=1;i<=len;++i)
		SAM::insert(s[i]-'a');
	SAM::build();
	for(reg int i=1;i<=min(SAM::sum[1],100000ll);++i)
		SAM::Print(1,i);
	reg int q=read();
	while(q--){
		reg int k=read();
		putchar(T[k-1]);
		putchar('\n');
	}
	flush();
	return 0;
}