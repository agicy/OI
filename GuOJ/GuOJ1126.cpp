#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 998244353

const int MAXN=30000+5;
const int MAXSIZE=20;
const int MAXS=20+5;

struct Matrix{
	int n,m;
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(reg int n=0,reg int m=0):n(n),m(m){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res(n,a.m);
		reg int r;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k){
				r=unit[i][k];
				for(reg int j=0;j<a.m;++j)
					res.unit[i][j]=(res.unit[i][j]+(ll)r*a.unit[k][j]%MOD)%MOD;
			}
		return res;
	}
};

Matrix I[3];
int a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	Matrix val[MAXN<<2];
	inline void pushup(reg int k){
		val[k]=val[lson]*val[rson];
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			val[k]=I[a[l]];
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int pos,reg int Val){
		if(l==r){
			val[k]=I[a[l]=Val];
			return;
		}
		if(pos<=mid)
			Update(lson,l,mid,pos,Val);
		if(pos>mid)
			Update(rson,mid+1,r,pos,Val);
		pushup(k);
		return;
	}
	inline Matrix Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val[k];
		if(L<=mid&&mid<R)
			return Query(lson,l,mid,L,R)*Query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return Query(lson,l,mid,L,R);
		else
			return Query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

namespace AC{
	const int MAXSIZE=(20+5)*2;
	int tot;
	bool tag[MAXSIZE];
	int ch[MAXSIZE][2];
	inline void insert(char str[]){
		reg int len=strlen(str+1),ID=0;
		for(reg int i=1;i<=len;++i){
			if(!ch[ID][str[i]-'0'])
				ch[ID][str[i]-'0']=++tot;
			ID=ch[ID][str[i]-'0'];
		}
		tag[ID]=true;
		return;
	}
	int fail[MAXSIZE];
	queue<int> Q;
	inline void build(void){
		for(reg int i=0;i<2;++i)
			if(ch[0][i])
				Q.push(ch[0][i]);
		while(!Q.empty()){
			reg int ID=Q.front();
			Q.pop();
			for(reg int i=0;i<2;++i)
				if(!ch[ID][i])
					ch[ID][i]=ch[fail[ID]][i];
				else{
					fail[ch[ID][i]]=ch[fail[ID]][i];
					tag[ch[ID][i]]|=tag[fail[ch[ID][i]]];
					Q.push(ch[ID][i]);
				}
		}
		return;
	}
}

using namespace AC;

int n,m,q;
int id[AC::MAXSIZE],rnk[AC::MAXSIZE];

int main(void){
	scanf("%d%d%d",&n,&m,&q);
	for(reg int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]==-1)
			a[i]=2;
	}
	for(reg int i=1;i<=m;++i){
		static char str[MAXS];
		scanf("%s",str+1);
		insert(str);
	}
	build();
	reg int cnt=0;
	for(reg int i=0;i<=tot;++i)
		if(!tag[i]){
			id[++cnt]=i;
			rnk[i]=cnt;
		}
	I[0].n=I[1].n=I[2].n=cnt+1;
	I[0].m=I[1].m=I[2].m=cnt+1;
	for(reg int i=0;i<=cnt;++i){
		reg int ID=id[i],lson=rnk[ch[ID][0]],rson=rnk[ch[ID][1]];
		if(tag[ID])
			continue;
		if(!tag[ch[ID][0]])
			++I[2][i][lson],++I[0][i][lson];
		if(!tag[ch[ID][1]])
			++I[2][i][rson],++I[1][i][rson];
	}
	Build(1,1,n);
	while(q--){
		static char opt[8];
		static int a,b;
		scanf("%s%d%d",opt+1,&a,&b);
		switch(opt[1]){
			case 'C':{
				if(b==-1)
					b=2;
				Update(1,1,n,a,b);
				break;
			}
			case 'Q':{
				Matrix x=Query(1,1,n,a,b);
				reg int ans=0;
				for(reg int i=0;i<=cnt;++i)
					ans=(ans+x[0][i])%MOD;
				printf("%d\n",ans);
				break;
			}
			default:break;
		}
	}
	return 0;
}