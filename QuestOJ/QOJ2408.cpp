#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=500+5;
const int MAXM=500+5;
const int MAXQ=6e5+5;

struct querys{
	int x1,y1,x2,y2;
};

int n,m,q;
char M[MAXN][MAXM];
querys Q[MAXQ];
bool ans[MAXQ];
int id[MAXQ];
bitset<MAXM> lef[MAXN][MAXM],rig[MAXN][MAXM];

inline void solve(reg int l,reg int r,reg int L,reg int R){
	if(l>r||L>R)
		return;
	reg int mid=(l+r)>>1;
	for(reg int i=mid;i>=l;--i)
		for(reg int j=m;j>=1;--j){
			lef[i][j]=false;
			if(M[i][j]=='0'){
				if(i==mid)
					lef[i][j][j]=true;
				else
					lef[i][j]|=lef[i+1][j];
				if(j!=m)
					lef[i][j]|=lef[i][j+1];
			}
		}
	for(reg int i=mid;i<=r;++i)
		for(reg int j=1;j<=m;++j){
			rig[i][j]=false;
			if(M[i][j]=='0'){
				if(i==mid)
					rig[i][j][j]=true;
				else
					rig[i][j]|=rig[i-1][j];
				if(j!=1)
					rig[i][j]|=rig[i][j-1];
			}
		}
	reg int cntl=0,cntr=0;
	static int idl[MAXQ],idr[MAXQ];
	for(reg int i=L;i<=R;++i)
		if(Q[id[i]].x2<mid)
			idl[++cntl]=id[i];
		else if(Q[id[i]].x1>mid)
			idr[++cntr]=id[i];
		else
			ans[id[i]]=(lef[Q[id[i]].x1][Q[id[i]].y1]&rig[Q[id[i]].x2][Q[id[i]].y2]).any();
	for(reg int i=1;i<=cntl;++i)
		id[L+i-1]=idl[i];
	for(reg int i=1;i<=cntr;++i)
		id[R-i+1]=idr[i];
	solve(l,mid-1,L,L+cntl-1),solve(mid+1,r,R-cntr+1,R);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	q=read();
	for(reg int i=1;i<=q;++i)
		id[i]=i,Q[i].x1=read(),Q[i].y1=read(),Q[i].x2=read(),Q[i].y2=read();
	solve(1,n,1,q);
	for(reg int i=1;i<=q;++i)
		writeln(ans[i]?"Safe":"Dangerous");
	flush();
	return 0;
}