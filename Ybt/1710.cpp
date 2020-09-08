#include<cstdio>
#include<algorithm>
using std::sort;
#define reg register
typedef long long ll;
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

struct Edge{
	int f,t,len;
	inline Edge(void){
		f=t=len=0;
		return;
	}
	inline Edge(reg int a,reg int b,reg int c){
		f=a,t=b,len=c;
		return;
	}
	inline void Read(void){
		f=read(),t=read(),len=read();
		//scanf("%d%d%d",&f,&t,&len);
		return;
	}
	inline bool operator<(const Edge& a)const{
		return len<a.len;
	}
};

struct UnionFind{
	int ID[MAXN],size[MAXN];
	inline void Init(reg int n){
		reg int i;
		for(i=1;i<=n;++i)
			ID[i]=i,size[i]=1;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb){
			ID[rb]=ra;
			size[ra]+=size[rb];
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

int n;
int cnt;
Edge E[MAXN];
UnionFind S;

int main(void){
	reg int i;
	reg ll ans=0;
	n=read();
	//scanf("%d",&n);
	for(i=1;i<n;++i)
		E[i].Read();
	sort(E+1,E+n);
	S.Init(n);
	for(i=1;i<n&&cnt<n-1;++i)
		if(!S.search(E[i].f,E[i].t)){
			++cnt;
			ans+=(ll)(E[i].len+1)*((ll)S.size[S.find(E[i].f)]*S.size[S.find(E[i].t)]-1);
			S.merge(E[i].f,E[i].t);
		}
	for(i=1;i<n;++i)
		ans+=E[i].len;
	printf("%lld\n",ans);
	return 0;
}