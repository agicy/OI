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

const int MAXN=1000000000+5;
const int MAXM=10000+5;

struct UnionFind{
	int ID[MAXM<<1],dis[MAXM<<1];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else{
			reg int root=find(ID[x]);
			dis[x]^=dis[ID[x]];
			return ID[x]=root;
		}
	}
};

int n,m;
int l[MAXM],r[MAXM],Ans[MAXM];
vector<int> V;
UnionFind S;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static char ch;
		l[i]=read(),r[i]=read();
		V.push_back(l[i]-1),V.push_back(r[i]);
		ch='\0';
		do
			ch=getchar();
		while(ch!='e'&&ch!='o');
		Ans[i]=(ch=='o');
	}
	return;
}

inline void Work(void){
	reg int ans=m;
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	n=V.size();
	S.Init(n);
	for(reg int i=1;i<=m;++i)
		l[i]=lower_bound(V.begin(),V.end(),l[i]-1)-V.begin()+1,
		r[i]=lower_bound(V.begin(),V.end(),r[i])-V.begin()+1;
	for(reg int i=1;i<=m;++i){
		reg int ra=S.find(l[i]),rb=S.find(r[i]);
		if(ra==rb&&(S.dis[l[i]]^S.dis[r[i]])!=Ans[i]){
			ans=i-1;
			break;
		}
		else{
			S.ID[ra]=rb;
			S.dis[ra]=S.dis[l[i]]^S.dis[r[i]]^Ans[i];
		}
	}
	printf("%d\n",ans);
	return;
}
