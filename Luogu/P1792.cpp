#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

int n,m;
int a[MAXN];
int lef[MAXN],rig[MAXN];
bool vis[MAXN];
priority_queue<Node,vector<Node>,less<Node>/**/> Q;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	if(m>(n>>1))
		puts("Error!");
	else{
		lef[1]=n,rig[n]=1;
		for(reg int i=2;i<=n;++i)
			lef[i]=i-1;
		for(reg int i=1;i<n;++i)
			rig[i]=i+1;
		for(reg int i=1;i<=n;++i)
			Q.push(Node(i,a[i]));
		reg int ans=0;
		while(m--){
			static Node s;
			reg int id;
			do{
				s=Q.top();
				Q.pop();
				id=s.id;
			}while(vis[id]);
			ans+=a[id];
			reg int l=lef[id],r=rig[id];
			a[id]=a[l]+a[r]-a[id];
			vis[l]=vis[r]=true;
			lef[id]=lef[l],rig[id]=rig[r];
			rig[lef[id]]=id,lef[rig[id]]=id;
			Q.push(Node(id,a[id]));
		}
		printf("%d\n",ans);
	}
	return 0;
}