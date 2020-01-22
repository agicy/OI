#include<cstdio>
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

const int MAXN=100000+5;

struct Node{
	int lson,rson;
	inline Node(void){
		lson=rson=0;
		return;
	}
};

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN];
	inline void Update(reg int ID,reg int val){
		while(ID<=n){
			unit[ID]+=val;
			ID+=lowbit(ID);
		}
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		while(ID){
			res+=unit[ID];
			ID-=lowbit(ID);
		}
		return res;
	}
	#undef lowbit
};

int n,root;
Node P[MAXN];
TreeArray T;

inline int find(reg int);
inline void Print(reg int);

int main(void){
	reg int i,Min,x,val,pos;
	n=read(),root=read();
	T.n=n;
	T.Update(root,1);
	Min=root;
	for(i=2;i<=n;++i){
		x=read(),val=T.Query(x),pos=find(val);
		if(x<Min)
			pos=Min,Min=x;
		if(pos<x)
			if(!P[pos].rson)
				P[pos].rson=x;
			else
				P[find(val+1)].lson=x;
		else
			if(!P[pos].lson)
				P[pos].lson=x;
			else
				P[find(val-1)].rson=x;
		T.Update(x,1);
	}
	Print(root);
	putchar('\n');
	return 0;
}

inline int find(reg int val){
	reg int l=1,r=n+1,mid;
	while(l+1<r){
		mid=(l+r)>>1;
		if(T.Query(mid)>=val)
			r=mid;
		else
			l=mid;
	}
	if(T.Query(l)!=val)
		return r;
	else
		return l;
}

inline void Print(reg int ID){
	printf("%d ",ID);
	if(P[ID].lson)
		Print(P[ID].lson);
	if(P[ID].rson)
		Print(P[ID].rson);
	return;
}
