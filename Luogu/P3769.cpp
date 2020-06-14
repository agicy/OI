#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=50000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Node{
	int id,x[3];
	inline void Read(void){
		id=read(),x[0]=read(),x[1]=read(),x[2]=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return id==a.id?(x[0]==a.x[0]?(x[1]==a.x[1]?(x[2]<a.x[2]):x[1]<a.x[1]):x[0]<a.x[0]):id<a.id;
	}
};

int n;
Node a[MAXN];

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	return;
}

namespace kD_Tree{
	const double alpha=0.75;
	#define cMax(x,y) ( (x) < (y) ? ( (x) = (y) ) : 0 )
	#define cMin(x,y) ( (x) > (y) ? ( (x) = (y) ) : 0 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Point{
		int x[3],val;
	};
	int root,tot;
	int WD;
	inline bool cmp(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	Point p[MAXN];
	struct Node{
		int lson,rson;
		int Max[3],Min[3];
		int MaxVal;
		int size;
		Point val;
	};
	Node T[MAXN];
	inline void pushup(reg int k){
		reg int l=T[k].lson,r=T[k].rson;
		if(l){
			cMax(T[k].MaxVal,T[l].MaxVal);
			cMax(T[k].Max[0],T[l].Max[0]),cMax(T[k].Max[1],T[l].Max[1]),cMax(T[k].Max[2],T[l].Max[2]);
			cMin(T[k].Min[0],T[l].Min[0]),cMin(T[k].Min[1],T[l].Min[1]),cMin(T[k].Min[2],T[l].Min[2]);
		}
		if(r){
			cMax(T[k].MaxVal,T[r].MaxVal);
			cMax(T[k].Max[0],T[r].Max[0]),cMax(T[k].Max[1],T[r].Max[1]),cMax(T[k].Max[2],T[r].Max[2]);
			cMin(T[k].Min[0],T[r].Min[0]),cMin(T[k].Min[1],T[r].Min[1]),cMin(T[k].Min[2],T[r].Min[2]);
		}
		T[k].size=T[l].size+T[r].size+1;
		return;
	}
	int top,S[MAXN];
	inline int NewNode(void){
		return top?S[top--]:++tot;
	}
	inline void ReBuild(reg int k,reg int num){
		reg int l=T[k].lson,r=T[k].rson;
		if(l)
			ReBuild(l,num);
		p[T[l].size+num+1]=T[k].val;
		S[++top]=k;
		if(r)
			ReBuild(r,num+T[l].size+1);
		return;
	}
	inline int Build(reg int l,reg int r,reg int wd){
		if(l>r)
			return 0;
		reg int k=NewNode();
		WD=wd;
		nth_element(p+l,p+mid,p+r+1,cmp);
		T[k].val=p[mid];
		T[k].MaxVal=T[k].val.val;
		T[k].Max[0]=T[k].Min[0]=T[k].val.x[0];
		T[k].Max[1]=T[k].Min[1]=T[k].val.x[1];
		T[k].Max[2]=T[k].Min[2]=T[k].val.x[2];
		T[k].lson=Build(l,mid-1,(wd+1)%3);
		T[k].rson=Build(mid+1,r,(wd+1)%3);
		pushup(k);
		return k;
	}
	inline void check(reg int& k,reg int wd){
		if(alpha*T[k].size<max(T[T[k].lson].size,T[T[k].rson].size)){
			ReBuild(k,0);
			k=Build(1,T[k].size,wd);
		}
		return;
	}
	inline void Insert(reg int &k,const Point& P,reg int wd){
		if(!k){
			k=NewNode();
			T[k].lson=T[k].rson=0;
			T[k].val=P;
			T[k].MaxVal=T[k].val.val;
			T[k].Max[0]=T[k].Min[0]=T[k].val.x[0];
			T[k].Max[1]=T[k].Min[1]=T[k].val.x[1];
			T[k].Max[2]=T[k].Min[2]=T[k].val.x[2];
			pushup(k);
			return;
		}
		if(P.x[wd]<=T[k].val.x[wd])
			Insert(T[k].lson,P,(wd+1)%3);
		else
			Insert(T[k].rson,P,(wd+1)%3);
		pushup(k);
		check(k,wd);
		return;
	}
	inline bool in(reg int k,const Point& a){
		return T[k].Max[0]<=a.x[0]&&T[k].Max[1]<=a.x[1]&&T[k].Max[2]<=a.x[2];
	}
	inline bool out(reg int k,const Point& a){
		return a.x[0]<T[k].Min[0]||a.x[1]<T[k].Min[1]||a.x[2]<T[k].Min[2];
	}
	inline bool at(reg int k,const Point& a){
		return T[k].val.x[0]<=a.x[0]&&T[k].val.x[1]<=a.x[1]&&T[k].val.x[2]<=a.x[2];
	}
	inline void Query(reg int k,Point& a){
		if(T[k].MaxVal<=a.val)
			return;
		if(out(k,a))
			return;
		if(in(k,a)){
			cMax(a.val,T[k].MaxVal);
			return;
		}
		if(at(k,a))
			cMax(a.val,T[k].val.val);
		if(T[k].lson)
			Query(T[k].lson,a);
		if(T[k].rson)
			Query(T[k].rson,a);
		return;
	}
	#undef mid
}

int f[MAXN];

inline void Work(void){
	sort(a+1,a+n+1);
	int ans=0;
	for(reg int i=1;i<=n;++i){
		static kD_Tree::Point p;
		p.x[0]=a[i].x[0];
		p.x[1]=a[i].x[1];
		p.x[2]=a[i].x[2];
		p.val=0;
		kD_Tree::Query(kD_Tree::root,p);
		f[i]=++p.val;
		kD_Tree::Insert(kD_Tree::root,p,0);
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return;
}