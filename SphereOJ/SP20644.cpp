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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
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

const int MAXN=5e4+5;
const int MAXM=5e4+5;

int n,m;
int a[MAXN];
int Max[MAXN],p[MAXN];
int top,S[MAXN];
int pos[MAXN],lef[MAXN],rig[MAXN];

struct querys{
	int id,l,r;
	inline bool operator<(const querys &a)const{
		return pos[l]!=pos[a.l]?pos[l]<pos[a.l]:r<a.r;
	}
};

querys q[MAXM];
int ans[MAXM];

inline int calc(reg int l,reg int r){
	static int las[MAXN];
	reg int res=0;
	for(reg int i=l;i<=r;++i)
		las[a[i]]=0;
	for(reg int i=l;i<=r;++i)
		if(!las[a[i]])
			las[a[i]]=i;
		else
			res=max(res,i-las[a[i]]);
	return res;
}

vector<int> V;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i+1]=read()+a[i];
	++n;
	reg int B=sqrt(n),tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			pos[j]=i;
	}
	V.resize(n);
	for(reg int i=1;i<=n;++i)
		V[i-1]=a[i];
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].l=read(),q[i].r=read()+1;
	sort(q+1,q+m+1);
	for(reg int i=1,j=1;j<=tot;++j){
		reg int l=rig[j]+1,r=l-1,top=0;
		reg int Ans=0;
		while(pos[q[i].l]==j){
			if(pos[q[i].r]==j)
				ans[q[i].id]=calc(q[i].l,q[i].r);
			else{
				while(r<q[i].r){
					++r;
					Max[a[r]]=r;
					if(!p[a[r]])
						p[a[r]]=r,S[++top]=a[r];
					Ans=max(Ans,r-p[a[r]]);
				}
				reg int tmp=Ans;
				while(l>q[i].l){
					--l;
					if(Max[a[l]])
						Ans=max(Ans,Max[a[l]]-l);
					else
						Max[a[l]]=l;
				}
				ans[q[i].id]=Ans;
				while(l<=rig[j]){
					if(Max[a[l]]==l)
						Max[a[l]]=0;
					++l;
				}
				Ans=tmp;
			}
			++i;
		}
		for(reg int i=1;i<=top;++i)
			Max[S[i]]=p[S[i]]=0;
	}
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}