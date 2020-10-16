#include<bits/stdc++.h>
using namespace std;
#define reg register
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=2048+5;
const int MAXM=2048+5;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,m;
	int unit[4][MAXN][MAXM];
	inline void Init(reg int s1,reg int s2){
		n=s1,m=s2;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int x,reg int y,reg int val){
		for(reg int i=x;i<=n;i+=lowbit(i))
			for(reg int j=y;j<=m;j+=lowbit(j)){
				unit[0][i][j]+=val;
				unit[1][i][j]+=1ll*val*x;
				unit[2][i][j]+=1ll*val*y;
				unit[3][i][j]+=1ll*val*x*y;
			}
		return;
	}
	inline int query(reg int x,reg int y){
		reg int res=0;
		for(reg int i=x;i;i^=lowbit(i))
			for(reg int j=y;j;j^=lowbit(j))
				res+=1ll*(x+1)*(y+1)*unit[0][i][j]-1ll*(y+1)*unit[1][i][j]-1ll*(x+1)*unit[2][i][j]+1ll*unit[3][i][j];
		return res;
	}
	inline int query(reg int a,reg int b,reg int c,reg int d){
		return query(c,d)-query(a-1,d)-query(c,b-1)+query(a-1,b-1);
	}
};

int n,m;
char ch;

int main(void){
	n=read(),m=read();
	BIT::Init(n,m);
	while(cin>>ch){
		static int a,b,c,d,x;
		switch(ch){
			case 'L':{
				a=read(),b=read(),c=read(),d=read(),x=read();
				BIT::update(a,b,x);
				BIT::update(c+1,b,-x);
				BIT::update(a,d+1,-x);
				BIT::update(c+1,d+1,x);
				break;
			}
			case 'k':{
				a=read(),b=read(),c=read(),d=read();
				printf("%d\n",BIT::query(a,b,c,d));
				break;
			}
		}
	}
	return 0;
}