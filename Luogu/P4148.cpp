#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=500000+5;
const int MAXOPT=200000+5;

inline double pow2(reg double x){
	return x*x;
}

struct Node{
	int x,y,a;
};

struct KD_Tree{
	#define mid ( ( (l) + (r) ) >> 1 )
	
	int cnt;
	int lson[MAXOPT],rson[MAXOPT];
	int sum[MAXOPT];
	int U[MAXOPT],D[MAXOPT],L[MAXOPT],R[MAXOPT];
	int tot,rub[MAXOPT];
	inline bool cmp1(const Node& a,const Node& b)const{
		return a.x<b.x;
	}
	inline bool cmp2(const Node& a,const Node& b)const{
		return a.y<b.y;
	}
	inline int GetNew(reg int cnt){
		if(tot)
			return rub[tot--];
		else
			return ++cnt;
	}
	inline void maintain(reg int x){
		
		return;
	}
	inline int Build(reg int l,reg int r,reg Node a[]){
		reg int root=GetNew(cnt);
		if(r<l)
			return 0;
		else{
			reg double bar1=0,bar2=0;
			for(reg int i=l;i<=r;++i)
				bar1+=a[i].x,bar2+=a[i].y;
			bar1/=(r-l+1),bar2/=(r-l+1);
			reg double s1=0,s2;
			for(reg int i=l;i<=r;++i)
				s1+=pow2(a[i].x-bar1),s2+=pow2(a[i].y-bar2);
			if(s1>s2){
				nth_element(a+l,a+mid,a+r+1,cmp1);
				lson[root]=Build(l,mid-1,a);
				rson[root]=Build(mid+1,r,a);
			}
			else{
				nth_element(a+l,a+mid,a+r+1,cmp2);
			}
			lson[root]=Build(l,mid-1,a);
			rson[root]=Build(mid+1,r,a);
			maintain(root);
		}
		return root;
	}
	inline void insert(reg int& root,reg int val){
		if(!x){
			x=v;
			pushup
			return;
		}
	}
	
	#undef mid
};

KD_Tree T;

int n;

int main(void){
	reg int lastans=0;
	n=read();
	while(true){
		static int opt;
		opt=read();
		if(opt==1){
			static int x,y,a;
			x=read()^lastans,y=read()^lastans,a=read()^lastans;
			T.Update(x,y,a);
		}
		else if(opt==2){
			static int x1,y1,x2,y2;
			x1=read()^lastans,y1=read()^lastans,x2=read()^lastans,y2=read()^lastans;
			T.Query()
		}
		else
			exit(0);
	}
	return 0;
}
