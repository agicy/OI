#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=8e5+5;

namespace SAM{
	struct Node{
		int ch[26];
		int dep,fa;
		#define ch(x) unit[(x)].ch
		#define dep(x) unit[(x)].dep
		#define fa(x) unit[(x)].fa
	};
	int tot,las;
	Node unit[MAXN<<1];
	inline int getId(void){
		reg int p=++tot;
		memset(&unit[p],0,sizeof(Node));
		return p;
	}
	inline void Init(void){
		tot=0;
		las=getId();
		return;
	}
	inline void insert(const int& c){
		reg int p=las,np=getId();
		dep(np)=dep(p)+1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(dep(q)==dep(p)+1)
				fa(np)=q;
			else{
				reg int nq=getId();
				dep(nq)=dep(p)+1;
				memcpy(ch(nq),ch(q),sizeof(ch(q)));
				fa(nq)=fa(q),fa(q)=fa(np)=nq;
				while(ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return;
	}
	inline void dfs(const int& n,const char s[],reg int val[]){
		reg int p=1,cnt=0;
		for(reg int i=1;i<=n;++i){
			val[i]=0;
			reg int c=s[i]-'a';
			while(p&&!ch(p)[c])
				p=fa(p);
			if(!p)
				p=1;
			else{
				cnt=min(cnt,dep(p))+1;
				p=ch(p)[c];
				val[i]=cnt;
			}
		}
		return;
	}
}

inline void manacher(const int& n,const char str[],reg int val[]){
	static char s[MAXN<<1];
	reg int m=0;
	s[0]='$',s[++m]='#';
	for(reg int i=1;i<=n;++i)
		s[++m]=str[i],s[++m]='#';
	s[m+1]='\0';
	static int p[MAXN<<1],tag[MAXN<<1];
	fill(tag+1,tag+m+1,0);
	for(reg int i=1,r=0,mid=0;i<=m;++i){
		if(i<=r)
			p[i]=min(p[(mid<<1)-i],r-i+1);
		else
			p[i]=1;
		while(s[i-p[i]]==s[i+p[i]])
			++p[i];
		if(i+p[i]-1>r)
			r=i+p[i]-1,mid=i;
		tag[i-p[i]+1]=i;
	}
	for(reg int i=1;i<=m;++i)
		tag[i]=max(tag[i-1],tag[i]);
	for(reg int i=1;i<=n;++i)
		if(tag[i<<1])
			val[i]=(tag[i<<1]-(i<<1)+1);
	val[n+1]=0;
	return;
}

inline int solve(const int n,const char a[],const char b[]){
	SAM::Init();
	for(reg int i=n;i>=1;--i)
		SAM::insert(b[i]-'a');
	static int val1[MAXN],val2[MAXN];
	SAM::dfs(n,a,val1);
	manacher(n,a,val2);
	reg int res=-1;
	for(reg int i=1;i<=n;++i)
		if(val1[i])
			res=max(res,val1[i]*2+val2[i+1]);
	return res;
}

int n;
char a[MAXN],b[MAXN];

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read(a+1)-(a+1),read(b+1);
		reg int ans1=solve(n,a,b);
		reverse(a+1,a+n+1),reverse(b+1,b+n+1);
		reg int ans2=solve(n,b,a);
		writeln(max(ans1,ans2));
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}