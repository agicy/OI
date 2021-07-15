#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char* s){
	*s=getchar();
	while(!isdigit(*s)) *s=getchar();
	while(isdigit(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXN=100;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod,exp>>=1;
	}
	return res;
}

inline int getId(reg int tagEq,reg int ptr,reg int cnt){
	return (cnt<<2)+(tagEq<<1)+ptr;
}

int n;
int G[((MAXN-1)<<2)][((MAXN-1)<<2)+1];
int val[((MAXN-1)<<2)];

inline void init(reg int n){
	reg int tot=(n-1)<<2;
	reg int p=fpow(n,mod-2);
	for(reg int S=0;S<tot;++S){
		memset(G[S],0,sizeof(int)*(tot+1));
		reg int cnt=S>>2,tagEq=(S&2)>>1,ptr=S&1;
		G[S][S]=1;
		if(cnt==n-1&&tagEq)
			continue;
		if(cnt==0&&tagEq)
			continue;
		G[S][getId(!tagEq,1,n-1-cnt)]=sub(G[S][getId(!tagEq,1,n-1-cnt)],p);
		if(tagEq)
			G[S][getId(!tagEq,0,cnt-1)]=sub(G[S][getId(!tagEq,0,cnt-1)],p);
		else
			G[S][getId(!tagEq,0,cnt+1)]=sub(G[S][getId(!tagEq,0,cnt+1)],p);
		if(ptr==1)
			G[S][tot]=add(G[S][tot],p);
		if(cnt<n-1)
			G[S][getId(tagEq,0,cnt+1)]=sub(G[S][getId(tagEq,0,cnt+1)],1ll*(n-2-(cnt-tagEq))*p%mod);
		if(cnt>0)
			G[S][getId(tagEq,0,cnt-1)]=sub(G[S][getId(tagEq,0,cnt-1)],1ll*(cnt-tagEq)*p%mod);
	}
	for(reg int i=0;i<tot;++i){
		reg int ptr=-1;
		for(reg int j=i;j<tot;++j)
			if(G[j][i]){
				ptr=j;
				break;
			}
		for(reg int j=0;j<=tot;++j)
			swap(G[ptr][j],G[i][j]);
		for(reg int j=0;j<tot;++j)
			if(G[j][i]&&i!=j){
				reg int d=1ll*G[j][i]*fpow(G[i][i],mod-2)%mod;
				for(reg int k=i;k<=tot;++k)
					G[j][k]=sub(G[j][k],1ll*d*G[i][k]%mod);
			}
	}
	for(reg int i=0;i<tot;++i)
		val[i]=1ll*G[i][tot]*fpow(G[i][i],mod-2)%mod;
	return;
}

bool ed;

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		init(n);
		reg int m=read();
		while(m--){
			static char s[MAXN+1];
			static int p;
			read(s),p=read()-1;
			reg int tot=0;
			for(reg int j=0;j<n;++j)
				tot+=s[j]-'0';
			reg int ans=0;
			for(reg int i=0;i<n;++i)
				for(reg int j=0;j<n;++j)
					if(i!=j)
						ans=add(ans,1ll*abs(i-j)*val[getId(s[i]==s[j],i==p,(s[i]=='1')?tot-1:n-1-tot)]%mod);
			printf("%d\n",ans);
		}
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}