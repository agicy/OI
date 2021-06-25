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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

bool vis[MAXN];
int n,k;
int a[MAXN];
int lef[MAXN],rig[MAXN];

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

int main(void){
	reg int t=read();
	while(t--){
		reg int las;
		n=read(),k=read(),las=read();
		fill(vis,vis+n+1,false);
		for(reg int i=1;i<n;++i){
			static int tmp;
			tmp=read();
			a[i]=tmp-las;
			las=tmp;
			lef[i]=i-1,rig[i]=i+1;
		}
		a[0]=a[n]=inf;
		priority_queue<Node,vector<Node>,greater<Node>/**/> Q;
		for(reg int i=1;i<n;++i)
			Q.push(Node(i,a[i]));
		reg ll ans=0;
		while(k--){
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
		printf("%lld\n",ans);
	}
	return 0;
}