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
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

const int MAXK=2.5e3+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int k,cr,cb;
int cnt,head[MAXK],to[MAXK],nxt[MAXK];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXK],dep[MAXK];
int f[MAXK][MAXK][2][3];

inline void dfs(reg int u){
	reg int cntl=max(0,dep[u]-cb),cntr=min(dep[u],cr);
	if(cntl>cntr)
		return;
	for(reg int i=cntl;i<=cntr;++i)
		f[u][i][0][0]=1;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		dfs(v);
		for(reg int j=cntl;j<=cntr;++j){
			static int tmp[2][3];
			memset(tmp,0,sizeof(tmp));
			for(reg int r1=0;r1<2;++r1)
				for(reg int b1=0;b1<3;++b1)
					for(reg int r2=0;r1+r2<2;++r2)
						for(reg int b2=0;b1+b2<3;++b2)
							tmp[r1+r2][b1+b2]=add(tmp[r1+r2][b1+b2],((b1&&b2)+1ll)*f[u][j][r1][b1]*f[v][j][r2][b2]%mod);
			memcpy(f[u][j],tmp,sizeof(tmp));
		}
	}
	if(u){
		for(reg int i=cntl;i<=cntr;++i){
			if(i)
				for(reg int j=0;j<2;++j)
					for(reg int k=0;k<3;++k){
						f[u][i-1][j][k]=add(f[u][i-1][j][k],f[u][i][j][k]);
						if(!j)
							f[u][i-1][j+1][k]=add(f[u][i-1][j+1][k],f[u][i][j][k]);
					}
			if(i==dep[u])
				memset(f[u][i],0,sizeof(f[u][i]));
			else{
				for(reg int j=0;j<2;++j)
					for(reg int k=1;k>=0;--k)
						for(reg int l=k+1;l<3;++l)
							f[u][i][j][l]=add(f[u][i][j][l],(k+1ll)*f[u][i][j][k]%mod);
			}
		}
	}
	return;
}

bool ed;

int main(void){
	k=read(),cr=read(),cb=read();
	for(reg int i=1,tot=0,ptr=0;i<=(k<<1);++i){
		static char s[8];
		read(s);
		switch(s[1]){
			case 'u':{
				reg int np=++tot;
				fa[np]=ptr,dep[np]=dep[ptr]+1;
				Add_Edge(ptr,np);
				ptr=np;
				break;
			}
			case 'o':{
				ptr=fa[ptr];
				break;
			}
			default:assert(false);
		}
	}
	dfs(0);
	printf("%d\n",f[0][0][1][2]);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}