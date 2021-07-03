#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int inf=0x3f3f3f3f;

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

int n,k,l;
int a[MAXN],b[MAXN];
bool visa[MAXN],visb[MAXN];
priority_queue<Node,vector<Node>,less<Node>> Q,Qa,Qb,Qap,Qbp;

inline void setA(reg int p){
	visa[p]=true;
	if(!visb[p])
		Qbp.push(Node(p,b[p]));
	return;
}

inline void setB(reg int p){
	visb[p]=true;
	if(!visa[p])
		Qap.push(Node(p,a[p]));
	return;
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read(),k=read(),l=k-read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			b[i]=read();
		for(reg int i=1;i<=n;++i){
			visa[i]=visb[i]=false;
			Q.push(Node(i,a[i]+b[i])),Qa.push(Node(i,a[i])),Qb.push(Node(i,b[i]));
		}
		Q.push(Node(0,-inf)),Qa.push(Node(0,-inf)),Qb.push(Node(0,-inf)),Qap.push(Node(0,-inf)),Qbp.push(Node(0,-inf));
		reg ll res=0;
		for(reg int i=1;i<=k;++i){
			while(visa[Q.top().id]||visb[Q.top().id])
				Q.pop();
			while(visa[Qa.top().id])
				Qa.pop();
			while(visb[Qb.top().id])
				Qb.pop();
			while(visa[Qap.top().id])
				Qap.pop();
			while(visb[Qbp.top().id])
				Qbp.pop();
			static Node p,pa,pb,pap,pbp;
			p=Q.top(),pa=Qa.top(),pb=Qb.top(),pap=Qap.top(),pbp=Qbp.top();
			reg int opt=1,Max=p.val;
			if(Max<pap.val+pbp.val)
				opt=3,Max=pap.val+pbp.val;
			if(Max<pap.val+pb.val)
				opt=4,Max=pap.val+pb.val;
			if(Max<pa.val+pbp.val)
				opt=5,Max=pa.val+pbp.val;
			if(pa.id!=pb.id&&l&&Max<pa.val+pb.val)
				opt=2,Max=pa.val+pb.val;
			res+=Max;
			switch(opt){
				case 1:setA(p.id),setB(p.id);break;
				case 2:setA(pa.id),setB(pb.id),--l;break;
				case 3:setA(pap.id),setB(pbp.id),++l;break;
				case 4:setA(pap.id),setB(pb.id);break;
				case 5:setA(pa.id),setB(pbp.id);break;
			}
		}
		printf("%lld\n",res);
		while(!Q.empty())
			Q.pop();
		while(!Qa.empty())
			Qa.pop();
		while(!Qb.empty())
			Qb.pop();
		while(!Qap.empty())
			Qap.pop();
		while(!Qbp.empty())
			Qbp.pop();
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}