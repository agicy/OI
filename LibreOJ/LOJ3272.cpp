#include<bits/stdc++.h>
using namespace std;
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

const int MAXN=200000+5;
const int MAXK=4+5;

int n,k;

struct Node{
	int x1,y1,x2,y2;
	inline Node(reg int x1=0,reg int y1=0,reg int x2=0,reg int y2=0):x1(x1),y1(y1),x2(x2),y2(y2){
		return;
	}
	inline void Read(void){
		x1=read(),y1=read(),x2=read(),y2=read();
		return;
	}
};

Node a[MAXN];

inline ll Query(const Node& a){
	if(a.x1>a.x2||a.y1>a.y2)
		return 0;
	else
		return 1ll*(a.x2-a.x1+1)*(a.y2-a.y1+1);
}

inline Node merge(const Node& a,const Node& base){
	return Node(max(a.x1,base.x1),max(a.y1,base.y1),min(a.x2,base.x2),min(a.y2,base.y2));
}

Node base[MAXK];

inline double Calc(const Node& a,const Node &base){
	reg double S=Query(a),s=Query(merge(a,base));
	return 1.0*(S-s)/S;
}

int main(void){
	srand(time(NULL));
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	k=min(k,n);
	while(true){
		reg bool flag=true;
		random_shuffle(a+1,a+n+1);
		for(reg int i=1;i<=k;++i)
			base[i]=a[i];
		for(reg int i=k+1;i<=n;++i){
			reg int pos=1;
			reg double Max=1e9;
			for(reg int j=1;j<=k;++j){
				reg double val=Calc(base[j],a[i]);
				if(val<Max)
					pos=j,Max=val;
			}
			base[pos]=merge(base[pos],a[i]);
			if(Query(base[pos])==0){
				flag=false;
				break;
			}
		}
		if(flag){
			for(reg int i=1;i<=k;++i)
				printf("%d %d\n",base[i].x1,base[i].y1);
			return 0;
		}
	}
	return 0;
}