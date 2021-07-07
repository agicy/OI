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

inline char* read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e6+5;
const int MAXQ=1e6+5;
const int inf=0x3f3f3f3f;

struct querys{
	int id,l,r;
	inline bool operator<(const querys& a)const{
		return l<a.l;
	}
};

inline void manacher(reg int n,reg char str[],reg int res[]){
	static char s[MAXN<<1];
	reg int m=0;
	s[0]='$',s[++m]='#';
	for(reg int i=1;i<=n;++i)
		s[++m]=str[i],s[++m]='#';
	s[m+1]='\0';
	static int p[MAXN<<1];
	for(reg int i=1,r=0,mid=0;i<=m;++i){
		if(i<=r)
			p[i]=min(p[(mid<<1)-i],r-i+1);
		else
			p[i]=1;
		while(s[i-p[i]]==s[i+p[i]])
			++p[i];
		if(i+p[i]-1>r)
			r=i+p[i]-1,mid=i;
	}
	p[0]=inf;
	reg int top=0;
	static int S[MAXN<<1];
	for(reg int i=1,ptr=0;i<=n;++i){
		while(ptr<(i<<1)){
			if(ptr+p[ptr]-1>=(i<<1))
				S[++top]=ptr;
			++ptr;
		}
		while(S[top]+p[S[top]]-1<(i<<1))
			--top;
		if(S[top])
			res[i]=(i<<1)-S[top]+1;
		else
			res[i]=inf;
	}
	return;
}

struct Event{
	int x,l,r,val;
	inline Event(void){
		return;
	}
	inline Event(reg int x,reg int l,reg int r,reg int val):x(x),l(l),r(r),val(val){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x;
	}
};

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void init(reg int s){
		n=s;
		//fill(unit+1,unit+n+1,0);
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline void update(const Event& e){
		update(e.l,e.val),update(e.r+1,-e.val);
		return;
	}
}

int n;
char s[MAXN];
int q;
int sum[MAXN];
querys qu[MAXQ];
bool ans[MAXQ];

bool ed;

int main(void){
	n=read(),read(s+1),q=read();
	for(reg int i=2;i<n;++i)
		sum[i]=sum[i-1]+(s[i-1]==s[i+1]);
	for(reg int i=1;i<=q;++i)
		qu[i].id=i,qu[i].l=read(),qu[i].r=read();
	sort(qu+1,qu+q+1);

	static int lef[MAXN],rig[MAXN];
	manacher(n,s,lef);
	reverse(s+1,s+n+1);
	manacher(n,s,rig);
	reverse(rig+1,rig+n+1);

	reg int tot=0;
	static Event e[MAXN<<1];
	for(reg int i=1;i<=n;++i){
		reg int lx=i-lef[i]+2,rx=i;
		reg int ly=i,ry=i+rig[i]-2;
		lx=max(lx,1),ry=min(ry,n);
		e[++tot]=Event(lx,ly,ry,1);
		e[++tot]=Event(rx+1,ly,ry,-1);
	}
	sort(e+1,e+tot+1);
	BIT::init(n);
	for(reg int i=1,j=1;i<=q;++i){
		while(j<=tot&&e[j].x<=qu[i].l)
			BIT::update(e[j++]);
		if(qu[i].l==qu[i].r)
			ans[qu[i].id]=false;
		else if(sum[qu[i].r-1]-sum[qu[i].l])
			ans[qu[i].id]=true;
		else
			ans[qu[i].id]=!BIT::query(qu[i].r);
	}
	for(reg int i=1;i<=q;++i)
		putchar(ans[i]+'0');
	putchar('\n');
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}