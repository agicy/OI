#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 39989
#define eps 1e-8
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
const int MAXSIZE=(MOD+5)<<3;

double K[MAXN],b[MAXN];

struct SegmentTree{
	int cnt;
	int l[MAXSIZE],r[MAXSIZE];
	int lson[MAXSIZE],rson[MAXSIZE];
	int data[MAXSIZE];
	inline double f(reg int x,reg int p){
		return K[x]*p+b[x];
	}
	inline void Build(reg int k,reg int ll,reg int rr){
		l[k]=ll,r[k]=rr;
		if(ll==rr){
			return;
		}
		reg int mid=(ll+rr)>>1;
		Build(lson[k]=++cnt,ll,mid);
		Build(rson[k]=++cnt,mid+1,rr);
		return;
	}
	inline int dcmp(reg double x){
		return fabs(x)<=eps?0:x<0?-1:1;
	}
	inline bool judge(reg int x,reg int y,reg int pos){
		reg double fx=f(x,pos),fy=f(y,pos);
		return dcmp(fx-fy)?fx<fy:x>y;
	}
	inline void Update(reg int k,reg int ll,reg int rr,int val){
		if(r[k]<ll||rr<l[k])
			return;
		if(ll<=l[k]&&r[k]<=rr){
			if(judge(val,data[k],l[k])&&judge(val,data[k],r[k])){
				return;
			}
			if(judge(data[k],val,l[k])&&judge(data[k],val,r[k])){
				data[k]=val;
				return;
			}
			reg int mid=(l[k]+r[k])>>1;
			if(judge(data[k],val,mid))
				swap(data[k],val);
			if(judge(data[k],val,l[k]))
				Update(lson[k],l[k],r[k],val);
			else
				Update(rson[k],l[k],r[k],val);
			return;
		}
		Update(lson[k],ll,rr,val);
		Update(rson[k],ll,rr,val);
		return;
	}
	inline int Query(reg int k,reg int x){
		if(x<l[k]||r[k]<x)
			return 0;
		if(l[k]==r[k]&&l[k]==x)
			return data[k];
		reg int mid=(l[k]+r[k])>>1;
		reg int res=(x<=mid)?Query(lson[k],x):Query(rson[k],x);
		if(judge(res,data[k],x))
			res=data[k];
		return res;
	}
};

int n;
SegmentTree T;

int main(void){
	n=read();
	reg int cnt=0;
	T.Build(T.cnt=1,1,40000);
	reg int lastans=0;
	while(n--){
		static int opt,k,x0,y0,x1,y1;
		opt=read();
		switch(opt){
			case 0:{
				k=read();
				k=(k+lastans+MOD-1)%MOD+1;
				lastans=T.Query(1,k);
				printf("%d\n",lastans);
				break;
			}
			case 1:{
				++cnt;
				x0=read(),y0=read(),x1=read(),y1=read();
				x0=(x0+lastans+MOD-1)%MOD+1;
				y0=((ll)y0+lastans-1+1000000000)%1000000000+1;
				x1=(x1+lastans+MOD-1)%MOD+1;
				y1=((ll)y1+lastans-1+1000000000)%1000000000+1;
				if(x1<x0)
					swap(x1,x0),swap(y1,y0);
				if(x0==x1)
					K[cnt]=0,b[cnt]=max(y0,y1);
				else
					K[cnt]=(double)(y0-y1)/(x0-x1),b[cnt]=y0-K[cnt]*x0;
				T.Update(1,x0,x1,cnt);
				break;
			}
			default:break;
		}
	}
	return 0;
}
