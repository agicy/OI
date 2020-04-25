#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXN=100000+5;

	inline int max(const int& a,const int& b,const int& c){
		return max(a,max(b,c));
	}
	
struct SegmentTree{
	#define lson ( ( k ) << 1 )
	#define rson ( ( k ) << 1 | 1 )
	struct Node{
		int l,r;
		int sum,Max[2],lMax[2],rMax[2];
		int lazy;
		bool rev;
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		unit[k].l=unit[lson].l,unit[k].r=unit[rson].r;
		unit[k].sum=unit[lson].sum+unit[rson].sum;
		if(unit[lson].Max[1])
			unit[k].lMax[0]=unit[lson].lMax[0];
		else
			unit[k].lMax[0]=unit[lson].Max[0]+unit[rson].lMax[0];
		if(unit[rson].Max[1])
			unit[k].rMax[0]=unit[rson].rMax[0];
		else
			unit[k].rMax[0]=unit[rson].Max[0]+unit[lson].rMax[0];
		if(unit[lson].Max[0])
			unit[k].lMax[1]=unit[lson].lMax[1];
		else
			unit[k].lMax[1]=unit[lson].Max[1]+unit[rson].lMax[1];
		if(unit[rson].Max[0])
			unit[k].rMax[1]=unit[rson].rMax[1];
		else
			unit[k].rMax[1]=unit[rson].Max[1]+unit[lson].rMax[1];
		unit[k].Max[0]=max(unit[lson].Max[0],unit[rson].Max[0],
			unit[lson].rMax[0]+unit[rson].lMax[0]);
		unit[k].Max[1]=max(unit[lson].Max[1],unit[rson].Max[1],
			unit[lson].rMax[1]+unit[rson].lMax[1]);
		return;
	}
	inline void maintain(reg int k){
		unit[k].rev=false;
		if(unit[k].lazy==0){
			unit[k].sum=unit[k].Max[1]=unit[k].lMax[1]=unit[k].rMax[1]=0;
			unit[k].Max[0]=unit[k].lMax[0]=unit[k].rMax[0]=unit[k].r-unit[k].l+1;
		}
		if(unit[k].lazy==1){
			unit[k].sum=unit[k].Max[1]=unit[k].lMax[1]=unit[k].rMax[1]=unit[k].r-unit[k].l+1;
			unit[k].Max[0]=unit[k].lMax[0]=unit[k].rMax[0]=0;
		}
		return;
	}
	inline void maintainrev(reg int k){
		unit[k].sum=unit[k].r-unit[k].l+1-unit[k].sum;
		swap(unit[k].Max[0],unit[k].Max[1]);
		swap(unit[k].lMax[0],unit[k].lMax[1]);
		swap(unit[k].rMax[0],unit[k].rMax[1]);
		return;
	}
	inline void pushdown(reg int k){
		if(unit[k].lazy!=-1){
			unit[lson].lazy=unit[rson].lazy=unit[k].lazy;
			maintain(lson),maintain(rson);
			unit[k].lazy=-1;
		}
		if(unit[k].rev){
			unit[lson].rev=!unit[lson].rev;
			unit[rson].rev=!unit[rson].rev;
			maintainrev(lson),maintainrev(rson);
			unit[k].rev=false;
		}
		return;
	}
	inline void Build(reg int k,reg int l,reg int r,reg int a[]){
		unit[k].l=l,unit[k].r=r;
		if(l==r){
			unit[k].sum=a[l];
			unit[k].Max[a[l]]=unit[k].lMax[a[l]]=unit[k].rMax[a[l]]=1;
			unit[k].Max[!a[l]]=unit[k].lMax[!a[l]]=unit[k].rMax[!a[l]]=0;
			unit[k].lazy=-1;
			unit[k].rev=false;
			return;
		}
		unit[k].lazy=-1;
		reg int mid=(l+r)>>1;
		Build(lson,l,mid,a);
		Build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int L,reg int R){
		if(L==unit[k].l&&unit[k].r==R)
			return unit[k].sum;
		pushdown(k);
		if(R<=unit[lson].r)
			return Query(lson,L,R);
		if(L>=unit[rson].l)
			return Query(rson,L,R);
		else
			return Query(lson,L,unit[lson].r)+Query(rson,unit[rson].l,R);
	}
	inline Node QueryMax(reg int k,reg int L,reg int R){
		if(L==unit[k].l&&unit[k].r==R)
			return unit[k];
		pushdown(k);
		if(R<=unit[lson].r)
			return QueryMax(lson,L,R);
		if(L>=unit[rson].l)
			return QueryMax(rson,L,R);
		else{
			Node lT=QueryMax(lson,L,unit[lson].r);
			Node rT=QueryMax(rson,unit[rson].l,R);
			Node res;
			res.l=lT.l;
			res.r=rT.r;
			if(lT.sum==lT.r-lT.l+1)
				res.lMax[1]=lT.r-lT.l+1+rT.lMax[1];
			else
				res.lMax[1]=lT.lMax[1];
			if(rT.sum==rT.r-rT.l+1)
				res.rMax[1]=rT.r-rT.l+1+lT.rMax[1];
			else
				res.rMax[1]=rT.rMax[1];
			res.Max[1]=max(lT.Max[1],rT.Max[1],lT.rMax[1]+rT.lMax[1]);
			return res;
		}
	}
	inline void change0(reg int k,reg int L,reg int R){
		if(L==unit[k].l&&unit[k].r==R){
			unit[k].lazy=0;
			maintain(k);
			return;
		}
		pushdown(k);
		if(R<=unit[lson].r)
			change0(lson,L,R);
		else if(L>=unit[rson].l)
			change0(rson,L,R);
		else
			change0(lson,L,unit[lson].r),change0(rson,unit[rson].l,R);
		pushup(k);
		return;
	}
	inline void change1(reg int k,reg int L,reg int R){
		if(L==unit[k].l&&unit[k].r==R){
			unit[k].lazy=1;
			maintain(k);
			return;
		}
		pushdown(k);
		if(R<=unit[lson].r)
			change1(lson,L,R);
		else if(L>=unit[rson].l)
			change1(rson,L,R);
		else
			change1(lson,L,unit[lson].r),change1(rson,unit[rson].l,R);
		pushup(k);
		return;
	}
	inline void reverse(reg int k,reg int L,reg int R){
		if(L==unit[k].l&&unit[k].r==R){
			unit[k].rev=!unit[k].rev;
			maintainrev(k);
			return;
		}
		pushdown(k);
		if(R<=unit[lson].r)
			reverse(lson,L,R);
		else if(L>=unit[rson].l)
			reverse(rson,L,R);
		else
			reverse(lson,L,unit[lson].r),reverse(rson,unit[rson].l,R);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
};

int n,m;
int a[MAXN];
SegmentTree T;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	T.Build(1,1,n,a);
	while(m--){
		static int opt,l,r;
		opt=read(),l=read()+1,r=read()+1;
		switch(opt){
			case 0:T.change0(1,l,r);break;
			case 1:T.change1(1,l,r);break;
			case 2:T.reverse(1,l,r);break;
			case 3:printf("%d\n",T.Query(1,l,r));break;
			case 4:printf("%d\n",T.QueryMax(1,l,r).Max[1]);break;
			default:break;
		}
	}
	return 0;
}
