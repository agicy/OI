#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e5+5;

int n,m;
int a[MAXN];
int pos[MAXN];
int ans[MAXN],Max[MAXN],p[MAXN];
int top,S[MAXN];

struct querys{
	int l,r,id;
	inline querys(reg int l=0,reg int r=0,reg int id=0):l(l),r(r),id(id){
		return;
	}
	inline bool operator<(const querys &a)const{
		return pos[l]!=pos[a.l]?pos[l]<pos[a.l]:r<a.r;
	}
};

querys Q[MAXN];

inline int calc(reg int l,reg int r){
	static int last[MAXN];
	int res=0;
	for(reg int i=l;i<=r;i++)
		last[a[i]]=0;
	for(reg int i=l;i<=r;i++)
		if(!last[a[i]])
			last[a[i]]=i;
		else
			res=max(res,i-last[a[i]]);
	return res;
}

vector<int> V;

int main(void){
	n=read();
	reg int len=sqrt(n);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		pos[i]=(i-1)/len+1;
		V.push_back(a[i]);
	}
	reg int tot=pos[n];
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	m=read();
	for(reg int i=1;i<=m;++i){
		static int l,r;
		l=read(),r=read();
		Q[i]=querys(l,r,i);
	}
	sort(Q+1,Q+m+1);
	for(reg int i=1,j=1;j<=tot;j++){
		reg int R=min(n,j*len),l=R+1,r=l-1,top=0;
		int Ans=0;
		for(;pos[Q[i].l]==j;i++){
			if(pos[Q[i].r]==j){
				ans[Q[i].id]=calc(Q[i].l,Q[i].r);
				continue;
			}
			while(r<Q[i].r){
				++r;
				Max[a[r]]=r;
				if(!p[a[r]])
					p[a[r]]=r,S[++top]=a[r];
				Ans=max(Ans,r-p[a[r]]);
			}
			reg int tmp=Ans;
			while(l>Q[i].l){
				--l;
				if(Max[a[l]])
					Ans=max(Ans,Max[a[l]]-l);
				else
					Max[a[l]]=l;
			}
			ans[Q[i].id]=Ans;
			while(l<=R){
				if(Max[a[l]]==l)
					Max[a[l]]=0;
				++l;
			}
			Ans=tmp;
		}
		for(reg int i=1;i<=top;++i)
			Max[S[i]]=p[S[i]]=0;
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}