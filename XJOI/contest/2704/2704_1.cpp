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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];
int lef[MAXN],rig[MAXN];
int cnt[3];
set<int> S[3];

inline bool check(reg int x){
	reg int l=lef[x],r=rig[x];
	if(a[l]!=a[x]&&a[x]!=a[r]&&a[r]!=a[l])
		return true;
	else
		return false;
}

inline void del(int x){
	int l=lef[x],r=rig[x];
	write(l+1),putchar(' '),write(r+1),putchar('\n');
	if(check(l)) S[a[l]].erase(l);
	if(check(r)) S[a[r]].erase(r);

	rig[l]=r,lef[r]=l;
	--cnt[a[x]];
	S[a[x]].erase(x);

	if(check(l)) S[a[l]].insert(l);
	if(check(r)) S[a[r]].insert(r);
	lef[x]=rig[x]=-1;
	return;
}

bool ed;

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i]=read(),++cnt[a[i]];
	reg bool flag=true;
	for(reg int i=0;i<n;++i)
		if(a[i]==a[(i+1)%n]){
			flag=false;
			break;
		}
	if(!cnt[0]||!cnt[1]||!cnt[2])
		flag=false;
	if(flag){
		writeln("yes");
		for(reg int i=0;i<n;++i)
			lef[i]=(i-1+n)%n,rig[i]=(i+1)%n;
		for(int i=0;i<n;++i)
			if(check(i))
				S[a[i]].insert(i);
		for(reg int i=1;i<=n-3;++i){
			reg int p=-1;
			if(cnt[0]>1&&S[0].size()) p=*S[0].begin();
			if(cnt[1]>1&&S[1].size()) p=*S[1].begin();
			if(cnt[2]>1&&S[2].size()) p=*S[2].begin();
			del(p);
		}
	}
	else
		writeln("no");
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}