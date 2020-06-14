#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=133333+5;
const int MAXM=133333+5;
const int MAXC=1000000+5;

int n,m;
int a[MAXN];

struct Querys{
	int l,r,t,id;
	inline Querys(reg int l=0,reg int r=0,reg int t=0,reg int id=0):l(l),r(r),t(t),id(id){
		return;
	}
};

struct Updates{
	int pos,suc,pre;
	inline Updates(reg int pos=0,reg int suc=0,reg int pre=0):pos(pos),suc(suc),pre(pre){
		return;
	}
};

Updates U[MAXM];
Querys Q[MAXM];

int BLOCK;
int Ucnt,Qcnt;

inline bool cmp(const Querys& a,const Querys& b){
	if(a.l/BLOCK!=b.l/BLOCK)
		return a.l/BLOCK<b.l/BLOCK;
	if(a.r/BLOCK!=b.r/BLOCK)
		return a.r/BLOCK<b.r/BLOCK;
	return a.t<b.t;
}

int T[MAXC];
int ans[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i){
		static char opt;
		static int fi,se;
		do
			opt=getchar();
		while(opt!='Q'&&opt!='R');
		fi=read(),se=read();
		switch(opt){
			case 'Q':{
				++Qcnt;
				Q[Qcnt]=Querys(fi,se,Ucnt,Qcnt);
				break;
			}
			case 'R':{
				U[++Ucnt]=Updates(fi,se,a[fi]);
				a[fi]=U[Ucnt].suc;
				break;
			}
			default:break;
		}
	}
	BLOCK=ceil(exp((log(n)+log(Ucnt))/3));
	for(reg int i=Ucnt;i>=1;--i)
		a[U[i].pos]=U[i].pre;
	sort(Q+1,Q+Qcnt+1,cmp);
	reg int l=1,r=0,t=0,num=0;
	for(reg int i=1;i<=m;++i){
		while(Q[i].l<l)
			num+=!T[a[--l]]++;
		while(Q[i].l>l)
			num-=!--T[a[l++]];
		while(Q[i].r>r)
			num+=!T[a[++r]]++;
		while(Q[i].r<r)
			num-=!--T[a[r--]];
		while(Q[i].t<t){
			reg int pos=U[t].pos;
			if(l<=pos&&pos<=r)
				num-=!--T[a[pos]];
			a[pos]=U[t--].pre;
			if(l<=pos&&pos<=r)
				num+=!T[a[pos]]++;
		}
		while(Q[i].t>t){
			reg int pos=U[++t].pos;
			if(l<=pos&&pos<=r)
				num-=!--T[a[pos]];
			a[pos]=U[t].suc;
			if(l<=pos&&pos<=r)
				num+=!T[a[pos]]++;
		}
		ans[Q[i].id]=num;
	}
	for(reg int i=1;i<=Qcnt;++i)
		printf("%d\n",ans[i]);
	return 0;
}