#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define eps 1e-6
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXM=3e5+5;

struct Node{
	ll x,y;
	inline Node(reg ll x=0,reg ll y=0):x(x),y(y){
		return;
	}
	inline Node operator-(const Node& a)const{
		return Node(x-a.x,y-a.y);
	}
	inline double operator*(const Node& a){
		return 1.0*x*a.y-1.0*y*a.x;
	}
};

ll K,B;

inline ll Calc(const Node& a){
	return a.y+K*a.x+B;
}

ll n;
int m;
Node S[MAXM];

int main(void){
	n=read(),m=read();
	reg int top=0;
	S[top=1]=Node(0,0);
	while(m--){
		static int type;
		static ll k,b,s;
		type=read();
		switch(type){
			case 1:{
				k=read();
				n+=k;
				S[top=1]=Node(0,0);
				K=B=0;
				break;
			}
			case 2:{
				k=read();
				Node t(n,-(n*K+B));
				n+=k;
				while(top>1&&(t-S[top-1])*(S[top]-S[top-1])>-eps)
					--top;
				S[++top]=t;
				break;
			}
			case 3:{
				b=read(),s=read();
				B+=b,K+=s;
				break;
			}
		}
		while(top>1&&Calc(S[top])>=Calc(S[top-1]))
			--top;
		printf("%lld %lld\n",S[top].x+1,Calc(S[top]));
	}
	return 0;
}
