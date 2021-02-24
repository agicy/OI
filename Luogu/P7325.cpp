#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef pair<pair<int,int>,int> triple;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

inline void exgcd(reg int a,reg int b,reg int& x,reg int &y){
	if(!b){
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
	return;
}

inline int getInv(reg int a,reg int p){
	int x,y;
	exgcd(a,p,x,y);
	return(x%p+p)%p;
}

struct Node{
	int a,b,id;
	inline Node(reg int a=0,reg int b=0,reg int id=0):a(a),b(b),id(id){
		return;
	}
};

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m;
int ans[MAXN];
vector<Node> Q[MAXM];

inline triple calc(reg int i,reg int a,reg int b){
	reg int m1=gcd(a,i),m2=gcd(b,i),m3=i/m1/m2;
	return make_pair(make_pair(m1,m2),1ll*a/m1*getInv(b/m2,m3)%m3);
};

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int A,B;
		A=read(),B=read();
		if(!A)
			ans[i]=0;
		else if(!B)
			ans[i]=1;
		else{
			reg int k=gcd(gcd(A,B),m);
			Q[m/k].push_back(Node(A/k,B/k,i));
			ans[i]=-1;
		}
	}
	for(reg int i=2;i<=m;++i)
		if(!Q[i].empty()){
			static int f[MAXM*6],len;
			f[0]=0,f[1]=1;
			for(len=2;len<=6*i;++len){
				f[len]=(f[len-1]+f[len-2])%i;
				if(!f[len])
					break;
			}
			map<triple,int> M;
			for(reg int j=1;j<=len;++j){
				triple tmp=calc(i,f[j],f[j-1]);
				if(M.find(tmp)==M.end())
					M[tmp]=j;
			}
			for(Node q:Q[i]){
				triple tmp=calc(i,q.a,i-q.b);
				if(M[tmp]>=2)
					ans[q.id]=M[tmp];
			}
		}
	for(reg int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
	return 0;
}