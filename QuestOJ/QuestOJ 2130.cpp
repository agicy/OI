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

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN][2];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i][0]=read(),a[i][1]=read();
	return;
}

struct SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	bool unit[MAXN<<2][2][2];
	inline void pushup(reg int k,reg int l,reg int r){
		unit[k][0][0]=unit[k][0][1]=unit[k][1][0]=unit[k][1][1]=false;
		if(r-l>1)
			for(reg int i=0,j;i<2;++i)
				for(j=0;j<2;++j){
					if(a[mid][0]<=a[mid+1][0])
						unit[k][i][j]|=unit[lson][i][0]&&unit[rson][0][j];
					if(a[mid][0]<=a[mid+1][1])
						unit[k][i][j]|=unit[lson][i][0]&&unit[rson][1][j];
					if(a[mid][1]<=a[mid+1][0])
						unit[k][i][j]|=unit[lson][i][1]&&unit[rson][0][j];
					if(a[mid][1]<=a[mid+1][1])
						unit[k][i][j]|=unit[lson][i][1]&&unit[rson][1][j];
				}
		else{
			unit[k][0][0]=a[mid][0]<=a[mid+1][0];
			unit[k][0][1]=a[mid][0]<=a[mid+1][1];
			unit[k][1][0]=a[mid][1]<=a[mid+1][0];
			unit[k][1][1]=a[mid][1]<=a[mid+1][1];
		}
		return;
	}

	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			unit[k][0][0]=true;
			unit[k][1][1]=true;
			unit[k][0][1]=a[l][0]<=a[l][1];
			unit[k][1][0]=a[l][1]<=a[l][0];
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k,l,r);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos){
		if(l==r&&l==pos){
			unit[k][0][0]=true;
			unit[k][1][1]=true;
			unit[k][0][1]=a[l][0]<=a[l][1];
			unit[k][1][0]=a[l][1]<=a[l][0];
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos);
		if(pos>mid)
			Update(rson,mid+1,r,pos);
		pushup(k,l,r);
		return;
	}
	inline bool Query(reg int k){
		reg bool res=false;
		for(reg int i=0,j;i<2;++i)
			for(j=0;j<2;++j)
				res|=unit[k][i][j];
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
};

SegmentTree T;

inline void Work(void){
	T.Build(1,1,n);
	while(m--){
		static int u,v;
		u=read(),v=read();
		swap(a[u][0],a[v][0]),swap(a[u][1],a[v][1]);
		T.Update(1,1,n,u),T.Update(1,1,n,v);
		puts(T.Query(1)?"SDFZHAPPY":"SDFZSAD");
	}
	return;
}
