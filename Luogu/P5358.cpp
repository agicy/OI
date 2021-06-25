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

const int MAXQ=5e5+5;
const int mod=1e7+19;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

struct querys{
	int opt,i,val;
};

int n,q;
querys qu[MAXQ];
int inv[mod];
bool vis[MAXQ];
int top,S[MAXQ];
int bas[MAXQ];

int main(void){
	inv[mod-1]=mod-1;
	for(reg int i=mod-2;i>=0;--i)
		inv[i]=1ll*inv[i+1]*(i+1)%mod;
	inv[0]=0;
	for(reg int i=1,fac=1;i<mod;fac=1ll*fac*i%mod,++i)
		inv[i]=1ll*inv[i]*fac%mod;
	n=read()%mod,q=read();
	vector<int> V;
	for(reg int i=1;i<=q;++i){
		qu[i].opt=read();
		switch(qu[i].opt){
			case 1:{qu[i].i=read(),qu[i].val=(read()%mod+mod)%mod;V.push_back(qu[i].i);break;}
			case 2:{qu[i].val=(read()%mod+mod)%mod;break;}
			case 3:{qu[i].val=(read()%mod+mod)%mod;break;}
			case 4:{qu[i].val=(read()%mod+mod)%mod;break;}
			case 5:{qu[i].i=read();V.push_back(qu[i].i);break;}
			case 6:{break;}
		}
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=q;++i)
		if(qu[i].opt==1||qu[i].opt==5)
			qu[i].i=lower_bound(V.begin(),V.end(),qu[i].i)-V.begin()+1;
	reg int ans=0;
	reg int tMul=1,tAdd=0,sum=0;
	reg int t=read();
	while(t--){
		static int a,b;
		a=read()%q,b=read()%q;
		for(reg int i=1;i<=q;++i){
			reg int id=(a+1ll*b*i%q)%q+1;
			switch(qu[id].opt){
				case 1:{
					reg int pos=qu[id].i;
					sum=sub(sum,add(1ll*bas[pos]*tMul%mod,tAdd));
					bas[pos]=1ll*sub(qu[id].val,tAdd)*inv[tMul]%mod;
					if(!vis[pos]) vis[pos]=true,S[++top]=pos;
					sum=add(sum,qu[id].val);
					break;
				}
				case 2:{
					tAdd=add(tAdd,qu[id].val);
					sum=add(sum,1ll*n*qu[id].val%mod);
					break;
				}
				case 3:{
					if(!qu[id].val){
						tMul=1,tAdd=0,sum=0;
						while(top){
							reg int pos=S[top--];
							vis[pos]=false,bas[pos]=0;
						}
					}
					else{
						tMul=1ll*tMul*qu[id].val%mod;
						tAdd=1ll*tAdd*qu[id].val%mod;
						sum=1ll*sum*qu[id].val%mod;
					}
					break;
				}
				case 4:{
					tMul=1,tAdd=qu[id].val,sum=1ll*n*qu[id].val%mod;
					while(top){
						reg int pos=S[top--];
						vis[pos]=false,bas[pos]=0;
					}
					break;
				}
				case 5:{
					reg int pos=qu[id].i;
					ans=add(ans,add(1ll*bas[pos]*tMul%mod,tAdd));
					break;
				}
				case 6:{
					ans=add(ans,sum);
					break;
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}