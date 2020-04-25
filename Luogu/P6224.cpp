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

const int MAXN=500000+5;

int n;

namespace KDTree{
	const double alpha=0.75;
	const int MAXWD=2;

	struct Point{
		int x[MAXWD];
		inline void Read(void){
			for(reg int i=0;i<MAXWD;++i)
				x[i]=read();
			return;
		}
	};

	int WD,tot;
	Point p[MAXN];
	int Max[MAXN][MAXWD],Min[MAXN][MAXWD];
	int root,lson[MAXN],rson[MAXN];
	int size[MAXN];
	int ans;
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
			if(l){
				Max[k][i]=max(Max[k][i],Max[l][i]);
				Min[k][i]=min(Min[k][i],Min[l][i]);
			}
			if(r){
				Max[k][i]=max(Max[k][i],Max[r][i]);
				Min[k][i]=min(Min[k][i],Min[r][i]);
			}
		}
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
	inline int GetDis(const Point& a,const Point& b){
		reg int res=0;
		for(reg int i=0;i<MAXWD;++i)
			res+=abs(a.x[i]-b.x[i]);
		return res;
	}
	inline int GetMaxDist(reg int k,const Point& p){
		reg int res=0;
		for(reg int i=0;i<MAXWD;++i)
			res+=max(abs(p.x[i]-Min[k][i]),abs(p.x[i]-Max[k][i]));
		return res;
	}
	inline void QueryMax(reg int k,const Point& p){
		ans=max(ans,GetDis(val[k],p));
		reg int dl=-INF,dr=-INF;
		if(lson[k])
			dl=GetMaxDist(lson[k],p);
		if(rson[k])
			dr=GetMaxDist(rson[k],p);
		if(dl>dr){
			if(dl>ans)
				QueryMax(lson[k],p);
			if(dr>ans)
				QueryMax(rson[k],p);
		}
		else{
			if(dr>ans)
				QueryMax(rson[k],p);
			if(dl>ans)
				QueryMax(lson[k],p);
		}
		return;
	}
	inline int GetMinDist(reg int k,const Point& p){
		reg int res=0;
		for(reg int i=0;i<MAXWD;++i)
			res+=max(p.x[i]-Max[k][i],0)+max(Min[k][i]-p.x[i],0);
		return res;
	}
	inline void QueryMin(reg int k,const Point& p){
		ans=min(ans,GetDis(val[k],p));
		reg int dl=INF,dr=INF;
		if(lson[k])
			dl=GetMinDist(lson[k],p);
		if(rson[k])
			dr=GetMinDist(rson[k],p);
		if(dl<dr){
			if(dl<ans)
				QueryMin(lson[k],p);
			if(dr<ans)
				QueryMin(rson[k],p);
		}
		else{
			if(dr<ans)
				QueryMin(rson[k],p);
			if(dl<ans)
				QueryMin(lson[k],p);
		}
		return;
	}
	inline int Query(const Point& p){
		ans=-INF;
		QueryMax(root,p);
		reg int ans1=ans;
		ans=INF;
		QueryMin(root,p);
		reg int ans2=ans;
		return ans1-ans2;
	}
}

using namespace KDTree;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i].Read();
	root=Build(1,n,0);
	reg int Q=read();
	while(Q--){
		static int opt;
		static Point P;
		opt=read(),P.Read();
		switch(opt){
			case 0:{
				Insert(root,P,0);
				break;
			}
			case 1:{
				ans=INF;
				QueryMin(root,P);
				printf("%d\n",ans);
				break;
			}
			case 2:{
				ans=-INF;
				QueryMax(root,P);
				printf("%d\n",ans);
				break;
			}
			default:break;
		}
	}
	return 0;
}
