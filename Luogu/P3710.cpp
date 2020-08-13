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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1.5e5+5;
const int MAXM=1.5e5+5;
const int p=998244353;

namespace SegmentTree{
	#define mid1 ( ( (l1) + (r1) ) >> 1 )
	#define mid2 ( ( (l2) + (r2) ) >> 1 )
	const int MAXSIZE=30*MAXN;
	struct Node{
		int son[2][2];
		int tagA,tagM;
		#define son(x) unit[(x)].son
		#define tagA(x) unit[(x)].tagA
		#define tagM(x) unit[(x)].tagM
	};
	Node unit[MAXSIZE];
	int tot;
	inline void build(reg int &k,const int& l1,const int& r1,const int& l2,const int& r2,const int& u,const int& v){
		if(l1>r1||l2>r2)
			return;
		if(!k)
			tagM(k=++tot)=1;
		if(l1==r1&&l2==r2)
			return;
		if(u<=mid1)
			if(v<=mid2)
				build(son(k)[0][0],l1,mid1,l2,mid2,u,v);
			else
				build(son(k)[0][1],l1,mid1,mid2+1,r2,u,v);
		else
			if(v<=mid2)
				build(son(k)[1][0],mid1+1,r1,l2,mid2,u,v);
			else
				build(son(k)[1][1],mid1+1,r1,mid2+1,r2,u,v);
		return;
	}
	inline int add(reg int a,reg int b){
		reg int sum=a+b;
		return sum>=p?sum-p:sum;
	}
	inline void Add(const int& k,const int& Val){
		tagA(k)=add(tagA(k),Val);
		return;
	}
	inline int mul(reg int a,reg int b){
		return 1ll*a*b%p;
	}
	inline void Mul(const int& k,const int& Val){
		tagA(k)=mul(tagA(k),Val);
		tagM(k)=mul(tagM(k),Val);
		return;
	}
	inline void pushdown(reg int k){
		if(tagM(k)!=1){
			if(son(k)[0][0])Mul(son(k)[0][0],tagM(k));
			if(son(k)[0][1])Mul(son(k)[0][1],tagM(k));
			if(son(k)[1][0])Mul(son(k)[1][0],tagM(k));
			if(son(k)[1][1])Mul(son(k)[1][1],tagM(k));
			tagM(k)=1;
		}
		if(tagA(k)){
			if(son(k)[0][0])Add(son(k)[0][0],tagA(k));
			if(son(k)[0][1])Add(son(k)[0][1],tagA(k));
			if(son(k)[1][0])Add(son(k)[1][0],tagA(k));
			if(son(k)[1][1])Add(son(k)[1][1],tagA(k));
			tagA(k)=0;
		}
		return;
	}
	inline void updateAdd(const int& k,const int& l1,const int& r1,const int& l2,const int& r2,const int& L1,const int& R1,const int& L2,const int& R2,const int& Val){
		if(!k)
			return;
		if(L1<=l1&&r1<=R1&&L2<=l2&&r2<=R2){
			Add(k,Val);
			return;
		}
		pushdown(k);
		if(L1<=mid1){
			if(L2<=mid2)
				updateAdd(son(k)[0][0],l1,mid1,l2,mid2,L1,R1,L2,R2,Val);
			if(R2>mid2)
				updateAdd(son(k)[0][1],l1,mid1,mid2+1,r2,L1,R1,L2,R2,Val);
		}
		if(R1>mid1){
			if(L2<=mid2)
				updateAdd(son(k)[1][0],mid1+1,r1,l2,mid2,L1,R1,L2,R2,Val);
			if(R2>mid2)
				updateAdd(son(k)[1][1],mid1+1,r1,mid2+1,r2,L1,R1,L2,R2,Val);
		}
		return;
	}
	inline void updateMul(const int& k,const int& l1,const int& r1,const int& l2,const int& r2,const int& L1,const int& R1,const int& L2,const int& R2,const int& Val){
		if(!k)
			return;
		if(L1<=l1&&r1<=R1&&L2<=l2&&r2<=R2){
			Mul(k,Val);
			return;
		}
		pushdown(k);
		if(L1<=mid1){
			if(L2<=mid2)
				updateMul(son(k)[0][0],l1,mid1,l2,mid2,L1,R1,L2,R2,Val);
			if(R2>mid2)
				updateMul(son(k)[0][1],l1,mid1,mid2+1,r2,L1,R1,L2,R2,Val);
		}
		if(R1>mid1){
			if(L2<=mid2)
				updateMul(son(k)[1][0],mid1+1,r1,l2,mid2,L1,R1,L2,R2,Val);
			if(R2>mid2)
				updateMul(son(k)[1][1],mid1+1,r1,mid2+1,r2,L1,R1,L2,R2,Val);
		}
		return;
	}
	inline int query(reg int k,reg int l1,reg int r1,reg int l2,reg int r2,reg int u,reg int v){
		while(true){
			if(!k)
				return 0;
			if(l1==r1&&l2==r2)
				return tagA(k);
			pushdown(k);
			if(u<=mid1)
				if(v<=mid2)
					k=son(k)[0][0],r1=mid1,r2=mid2;
				else
					k=son(k)[0][1],r1=mid1,l2=mid2+1;
			else
				if(v<=mid2)
					k=son(k)[1][0],l1=mid1+1,r2=mid2;
				else
					k=son(k)[1][1],l1=mid1+1,l2=mid2+1;
		}
	}
}

int n,m;
int t[MAXM];

struct updates{
	int opt,l,r,d,st,ed;
};

struct querys{
	int u,v;
};

updates U[MAXM];
querys Q[MAXM];
int id[MAXM];

int main(void){
	n=read(),m=read();
	reg int cntU=0,cntQ=0;
	reg int tim=0;
	reg bool flag=false;
	for(reg int i=1;i<=m;++i){
		static int opt,u;
		opt=read();
		switch(opt){
			case 1:case 2:{
				flag=false;
				id[i]=++cntU;
				U[cntU].opt=opt;
				U[cntU].l=read(),U[cntU].r=read(),U[cntU].d=read();
				U[cntU].st=tim+1,U[cntU].ed=m;
				break;
			}
			case 3:{
				if(!flag)
					++tim;
				Q[++cntQ].v=tim;
				Q[cntQ].u=read();
				flag=true;
				break;
			}
			case 4:{
				flag=false;
				u=read();
				U[id[u]].ed=tim;
				break;
			}
		}
	}
	for(reg int i=1;i<=cntU;++i)
		if(U[i].ed>tim)
			U[i].ed=tim;
	int root=0;
	for(reg int i=1;i<=cntQ;++i)
		SegmentTree::build(root,1,n,1,tim,Q[i].u,Q[i].v);
	reg int ptr=1;
	for(reg int i=1;i<=cntQ;++i){
		while(ptr<=cntU&&U[ptr].st<=Q[i].v){
			if(U[ptr].st<=U[ptr].ed){
				if(U[ptr].opt==1)
					SegmentTree::updateAdd(root,1,n,1,tim,U[ptr].l,U[ptr].r,U[ptr].st,U[ptr].ed,U[ptr].d);
				else
					SegmentTree::updateMul(root,1,n,1,tim,U[ptr].l,U[ptr].r,U[ptr].st,U[ptr].ed,U[ptr].d);
			}
			++ptr;
		}
		printf("%d\n",SegmentTree::query(root,1,n,1,tim,Q[i].u,Q[i].v));
	}
	return 0;
}