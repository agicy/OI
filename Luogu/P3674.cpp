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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void hana(void){
	putchar('h'),putchar('a'),putchar('n'),putchar('a'),putchar('\n');
	return;
}

inline void bi(void){
	putchar('b'),putchar('i'),putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXC=1e5+5;
const int C=1e5;

struct querys{
	int id,opt,l,r,x;
};

int n,m;
int a[MAXN];
querys q[MAXM];
int id[MAXN];

inline bool cmp(const querys& a,const querys& b){
	return id[a.l]==id[b.l]?((id[a.l]&1)?a.r>b.r:a.r<b.r):a.l<b.l;
}

int T[MAXC];
bitset<MAXC> A,B;

inline void add(reg int x){
	++T[x];
	A[x]=T[x],B[C-x]=T[x];
	return;
}

inline void del(reg int x){
	--T[x];
	A[x]=T[x],B[C-x]=T[x];
	return;
}

bool ans[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int S=sqrt(n);
	for(reg int i=1;i<=n;++i)
		id[i]=(i-1)/S+1;
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].opt=read(),q[i].l=read(),q[i].r=read(),q[i].x=read();
	sort(q+1,q+m+1,cmp);
	reg int l=1,r=0;
	for(reg int i=1;i<=m;++i){
		while(l>q[i].l)
			add(a[--l]);
		while(l<q[i].l)
			del(a[l++]);
		while(r>q[i].r)
			del(a[r--]);
		while(r<q[i].r)
			add(a[++r]);
		switch(q[i].opt){
			case 1:{
				ans[q[i].id]=((A<<q[i].x)&A).any();
				break;
			}
			case 2:{
				ans[q[i].id]=((B>>(C-q[i].x))&A).any();
				break;
			}
			case 3:{
				for(reg int j=1;1ll*j*j<=q[i].x;++j)
					if(!(q[i].x%j)){
						ans[q[i].id]=A[j]&&A[q[i].x/j];
						if(ans[q[i].id])
							break;
					}
				break;
			}
		}
	}
	for(reg int i=1;i<=m;++i)
		if(ans[i])
			hana();
		else
			bi();
	flush();
	return 0;
}