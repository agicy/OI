#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(isspace(*s))*s=getchar();
	while(!isspace(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=5e4+5;
const int MAXM=10;

struct Vector{
	int unit[MAXM];
	inline int& operator[](int i){
		return unit[i];
	}
};

struct Node{
	int unit[2];
	inline Node(reg int a=0,reg int b=0){
		unit[0]=a,unit[1]=b;
		return;
	}
	inline int operator[](reg int i)const{
		return unit[i];
	}
};

inline Node Min(const Node& a,const Node& b){
	return Node(add(1ll*a[0]*b[0]%mod,add(1ll*a[0]*b[1]%mod,1ll*a[1]*b[0]%mod)),1ll*a[1]*b[1]%mod);
}

inline Node Max(const Node& a,const Node& b){
	return Node(1ll*a[0]*b[0]%mod,add(1ll*a[1]*b[1]%mod,add(1ll*a[0]*b[1]%mod,1ll*a[1]*b[0]%mod)));
}

inline Node operator +(const Node& a,const Node& b){
	return Node(add(a[0],b[0]),add(a[1],b[1]));
}

int n,m;
int len;
Vector a[MAXN];
char s[MAXN];
char op[MAXN];
int topO,topS;
char str[MAXN];
int g[1<<MAXM];

inline void solve(reg int S){
	reg int top=0;
	static Node stk[MAXN];
	for(reg int i=1;i<=len;++i)
		if(isdigit(str[i])){
			Node tmp;
			tmp.unit[(S>>(str[i]-'0'))&1]=1;
			stk[++top]=tmp;
			continue;
		}
		else{
			static Node x,y;
			x=stk[top--],y=stk[top--];
			if(str[i]=='<')
				stk[++top]=Min(x,y);
			if(str[i]=='>')
				stk[++top]=Max(x,y);
			if(str[i]=='?')
				stk[++top]=Min(x,y)+Max(x,y);
		}
	g[S]=stk[1].unit[1];
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<m;++i)
		for(reg int j=1;j<=n;++j)
			a[j][i]=read();
	read(s+1);
	len=strlen(s+1);
	for(reg int i=1;i<=len;++i)
		if(isdigit(s[i]))
			str[++topS]=s[i];
		else if(s[i]=='(')
			op[++topO]='(';
		else{
			while(topO&&op[topO]!='(')
				str[++topS]=op[topO--];
			if(s[i]!=')')
				op[++topO]=s[i];
			else
				--topO;
		}
	while(topO)
		str[++topS]=op[topO--];
	len=topS;
	for(reg int S=0;S<(1<<m);++S)
		solve(S);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		static int V[MAXM],G[MAXM];
		for(reg int j=0;j<m;++j)
			V[j]=a[i][j];
		sort(V,V+m);
		reg int topO=unique(V,V+m)-V;
		for(reg int j=0;j<topO;++j){
			reg int S=0;
			for(reg int k=0;k<m;++k)
				if(V[j]<=a[i][k])
					S|=(1<<k);
			G[j]=g[S];
		}
		for(reg int j=0;j<topO-1;++j)
			G[j]=sub(G[j],G[j+1]);
		for(reg int j=0;j<topO;++j)
			ans=add(ans,1ll*G[j]*V[j]%mod);
	}
	printf("%d\n",ans);
	return 0;
}