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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e6+5;
const int MAXM=1e6+5;

struct Node{
	int type,a,b;
	inline Node(reg int type=0,reg int a=0,reg int b=0):type(type),a(a),b(b){
		return;
	}
};

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
};

int n,m;
Node op[MAXM];
vector<int> V;
int a[MAXN];
BIT T1,T2;

int main(void){
	freopen("book.in","r",stdin);
	freopen("book.out","w",stdout);

	n=read(),m=read();
	V.push_back(0);
	for(reg int i=1;i<=m;++i){
		static char opt;
		static int a,b;
		do
			opt=getchar();
		while(!isalpha(opt));
		a=read(),b=read();
		V.push_back(b);
		op[i]=Node(opt=='U'?0:1,a,b);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	T1.Init(V.size()),T2.Init(V.size());
	T1.update(1,n);
	for(reg int i=1;i<=n;++i)
		a[i]=1;
	for(reg int i=1;i<=m;++i){
		op[i].b=lower_bound(V.begin(),V.end(),op[i].b)-V.begin()+1;
		if(!op[i].type){
			reg int k=op[i].a;
			T1.update(a[k],-1),T2.update(a[k],-V[a[k]-1]);
			a[k]=op[i].b;
			T1.update(a[k],+1),T2.update(a[k],V[a[k]-1]);
		}
		else{
			reg int cnt=n-T1.query(op[i].b-1);
			if(cnt>=op[i].a)
				puts("TAK");
			else{
				reg ll sum=T2.query(op[i].b-1);
				if(sum>=1ll*(op[i].a-cnt)*V[op[i].b-1])
					puts("TAK");
				else
					puts("NIE");
			}
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}