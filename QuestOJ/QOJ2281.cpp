#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;

int n;

struct Option{
	int type,x,a,b,c;
};

Option O[MAXN];

struct Point{
	int x[3],id;
};

Point p[MAXN];
int pos[MAXN];

namespace kD_Tree{
	inline void cMax(reg int &a,reg int b){
		if(a<b)
			a=b;
		return;
	}
	inline void cMin(reg int &a,reg int b){
		if(a>b)
			a=b;
		return;
	}
	const int trans[]={1,2,0};
	inline int add3(reg int a){
		return trans[a];
	}
	struct Node{
		int fa,lson,rson;
		int Max[3],Min[3];
		int sum;
		bool cnt;
		Point ptr;
		#define fa(x) unit[(x)].fa
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define sum(x) unit[(x)].sum
		#define cnt(x) unit[(x)].cnt
		#define ptr(x) unit[(x)].ptr
	};
	int tot;
	Node unit[MAXN];
	int WD;
	inline bool cmp(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	inline void pushup(reg int k){
		reg int l=lson(k),r=rson(k);
		Max(k)[0]=Min(k)[0]=ptr(k).x[0];
		Max(k)[1]=Min(k)[1]=ptr(k).x[1];
		Max(k)[2]=Min(k)[2]=ptr(k).x[2];
		if(l){
			cMax(Max(k)[0],Max(l)[0]),
			cMax(Max(k)[1],Max(l)[1]),
			cMax(Max(k)[2],Max(l)[2]),

			cMin(Min(k)[0],Min(l)[0]),
			cMin(Min(k)[1],Min(l)[1]),
			cMin(Min(k)[2],Min(l)[2]);
		}
		if(r){
			cMax(Max(k)[0],Max(r)[0]),
			cMax(Max(k)[1],Max(r)[1]),
			cMax(Max(k)[2],Max(r)[2]),

			cMin(Min(k)[0],Min(r)[0]),
			cMin(Min(k)[1],Min(r)[1]),
			cMin(Min(k)[2],Min(r)[2]);
		}
		return;
	}
	inline int build(reg int l,reg int r,reg int father,reg int wd){
		if(l>r)
			return 0;
		reg int k=++tot;
		reg int mid=(l+r)>>1;

		WD=wd;
		nth_element(p+l,p+mid,p+r+1,cmp);

		fa(k)=father;
		ptr(k)=p[mid];

		pos[p[mid].id]=k;

		lson(k)=build(l,mid-1,k,add3(wd));
		rson(k)=build(mid+1,r,k,add3(wd));

		pushup(k);
		return k;
	}

	inline bool in(reg int k,reg int L,reg int R,reg int x1,reg int x2){
		return L<=Min(k)[0]&&Max(k)[0]<=R&&Max(k)[1]<=x1&&Min(k)[2]>=x2;
	}

	inline bool check(reg int k,const int& L,const int& R,const int& x1,const int& x2){
		return L<=ptr(k).x[0]&&ptr(k).x[0]<=R&&ptr(k).x[1]<=x1&&ptr(k).x[2]>=x2;
	}

	inline bool out(reg int k,const int& L,const int& R,const int& x1,const int& x2){
		return R<Min(k)[0]||Max(k)[0]<L||x1<Min(k)[1]||x2>Max(k)[2];
	}
	inline int query(reg int k,const int& L,const int& R,const int& x1,const int& x2){
		if(!k)
			return 0;
		if(in(k,L,R,x1,x2))
			return sum(k);
		if(out(k,L,R,x1,x2))
			return 0;
		reg int res=0;
		if(cnt(k)&&check(k,L,R,x1,x2))
			++res;
		if(lson(k))
			res+=query(lson(k),L,R,x1,x2);
		if(rson(k))
			res+=query(rson(k),L,R,x1,x2);
		return res;
	}
	inline void access(reg int k){
		cnt(k)=true;
		do{
			++sum(k);
			k=fa(k);
		}while(k);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static char opt;
		static int x,s,l,r,t;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'G':{
				x=read(),l=read(),r=read(),t=read();
				O[i].type=0,O[i].x=x,O[i].a=l,O[i].b=r,O[i].c=t;
				break;
			}
			case 'T':{
				x=read(),s=read();
				O[i].type=1,O[i].x=x,O[i].a=s;
				break;
			}
		}
	}
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		if(O[i].type){
			++tot;
			p[tot].x[0]=O[i].x, //x
			p[tot].x[1]=O[i].x-O[i].a, //x-s
			p[tot].x[2]=O[i].x+O[i].a, //x+s
			p[tot].id=i;
		}
	reg int rt=kD_Tree::build(1,tot,0,0);
	for(reg int i=1;i<=n;++i)
		if(O[i].type)
			kD_Tree::access(pos[i]);
		else{
			reg int ans=kD_Tree::query(
				rt,
				O[i].a, //l
				O[i].b, //r
				O[i].x+O[i].c, //x+t
				O[i].x-O[i].c //x-t
			);
			printf("%d\n",ans);
		}
	return 0;
}