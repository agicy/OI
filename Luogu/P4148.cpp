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
const int MAXN=200000+5;

int n;

namespace KDTree{
	const double alpha=0.75;
	const int MAXWD=2;
	
	struct Point{
		int x[MAXWD];
		int w;
		inline Point(void){
			x[0]=x[1]=w=0;
			return;
		}
		inline Point(reg int a,reg int b,reg int c){
			x[0]=a,x[1]=b,w=c;
			return;
		}
	};

	int WD,tot;
	Point p[MAXN];
	
	int Max[MAXN][MAXWD],Min[MAXN][MAXWD];
	int root,lson[MAXN],rson[MAXN];
	int sum[MAXN],size[MAXN];
	Point val[MAXN];
	
	int top,S[MAXN];

	inline bool operator<(const Point& a,const Point& b){
		return a.x[WD]<b.x[WD];
	}
	inline int NewNode(void){
		return top?S[top--]:++tot;
	}
	inline void pushup(reg int k){
		reg int l=lson[k],r=rson[k];
		for(reg int i=0;i<MAXWD;++i){
			Max[k][i]=Min[k][i]=val[k].x[i];
			if(l)
				Max[k][i]=max(Max[k][i],Max[l][i]);
			if(r)
				Max[k][i]=max(Max[k][i],Max[r][i]);
			if(l)
				Min[k][i]=min(Min[k][i],Min[l][i]);
			if(r)
				Min[k][i]=min(Min[k][i],Min[r][i]);
		}
		sum[k]=sum[l]+sum[r]+val[k].w;
		size[k]=size[l]+size[r]+1;
		return;
	}
	inline int Build(reg int l,reg int r,reg int wd){
		if(l>r)
			return 0;
		reg int mid=(l+r)>>1;
		reg int k=NewNode();
		WD=wd;
		nth_element(p+l,p+mid,p+r+1);
		val[k]=p[mid];
		lson[k]=Build(l,mid-1,wd^1);
		rson[k]=Build(mid+1,r,wd^1);
		pushup(k);
		return k;
	}
	inline void ReBuild(reg int k,reg int num){
		if(lson[k])
			ReBuild(lson[k],num);
		p[size[lson[k]]+num+1]=val[k];
		S[++top]=k;
		if(rson[k])
			ReBuild(rson[k],num+size[lson[k]]+1);
		return;
	}
	inline void check(reg int &k,reg int wd){
		if(size[k]*alpha<max(size[lson[k]],size[rson[k]])){
			ReBuild(k,0);
			k=Build(1,size[k],wd);
		}
		return;
	}
	inline void Insert(reg int &k,const Point& P,reg int wd){
		if(!k){
			k=NewNode();
			lson[k]=rson[k]=0;
			val[k]=P;
			pushup(k);
			return;
		}
		if(P.x[wd]<=val[k].x[wd])
			Insert(lson[k],P,wd^1);
		else
			Insert(rson[k],P,wd^1);
		pushup(k);
		check(k,wd);
		return;
	}
	inline bool in(reg int x1,reg int y1,reg int x2,reg int y2,reg int X1,reg int Y1,reg int X2,reg int Y2) {
		return (X1>=x1&&X2<=x2&&Y1>=y1&&Y2<=y2);
	}
	inline bool out(reg int x1,reg int y1,reg int x2,reg int y2,reg int X1,reg int Y1,reg int X2,reg int Y2) {
		return (x1>X2||x2<X1||y1>Y2||y2<Y1);
	}
	inline int Query(reg int k,reg int x1,reg int y1,reg int x2,reg int y2){
		if(!k)
			return 0;
		reg int res=0;
		if(in(x1,y1,x2,y2,Min[k][0],Min[k][1],Max[k][0],Max[k][1]))
			return sum[k];
		if(out(x1,y1,x2,y2,Min[k][0],Min[k][1],Max[k][0],Max[k][1]))
			return 0;
		if(in(x1,y1,x2,y2,val[k].x[0],val[k].x[1],val[k].x[0],val[k].x[1]))
			res+=val[k].w;
		res+=Query(lson[k],x1,y1,x2,y2)+Query(rson[k],x1,y1,x2,y2);
		return res;
	}
}

using namespace KDTree;

int main(void){
	n=read();
	reg bool flag=true;
	reg int lastans=0;
	while(flag){
		static int opt,x,y,A,x1,y1,x2,y2;
		opt=read();
		switch(opt){
			case 1:{
				x=read()^lastans,y=read()^lastans,A=read()^lastans;
				Insert(root,Point(x,y,A),0);
				break;
			}
			case 2:{
				x1=read()^lastans,y1=read()^lastans,x2=read()^lastans,y2=read()^lastans;
				reg int ans=Query(root,x1,y1,x2,y2);
				printf("%d\n",ans);
				lastans=ans;
				break;
			}
			case 3:{
				flag=false;
				break;
			}
			default:break;
		}
	}
	return 0;
}
