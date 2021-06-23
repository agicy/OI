#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
typedef long long ll;
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

const int MAXN=1e6+5;

int n,t1,t2,t3;
uint Inc[MAXN],Dec[MAXN];
set<int> S;

int main(void){
	n=read(),t1=read(),t2=read(),t3=read();
	for(reg int i=1;i<=n;++i){
		static int opt,a,b,k;
		opt=read();
		switch(opt){
			case 1:{
				a=read(),b=read();
				reg int p=b>>5,q=b&((1<<5)-1);
				if(a>0){
					reg uint val=(uint)a<<q,org=Inc[p],tAdd=((uint)a>>(31-q))>>1;
					Inc[p]+=val;
					tAdd+=(org>Inc[p]);
					if(Inc[p]!=Dec[p])
						S.insert(p);
					else if(S.count(p))
						S.erase(p);
					++p;
					while(tAdd!=0){
						org=Inc[p];
						Inc[p]+=tAdd;
						tAdd=(org>Inc[p]);
						if(Inc[p]!=Dec[p])
							S.insert(p);
						else if(S.count(p))
							S.erase(p);
						++p;
					}
				}
				else if(a<0){
					a=-a;
					reg uint val=(uint)a<<q,org=Dec[p],tAdd=((uint)a>>(31-q))>>1;
					Dec[p]+=val;
					tAdd+=(org>Dec[p]);
					if(Inc[p]!=Dec[p])
						S.insert(p);
					else if(S.count(p))
						S.erase(p);
					++p;
					while(tAdd!=0){
						org=Dec[p];
						Dec[p]+=tAdd;
						tAdd=(org>Dec[p]);
						if(Inc[p]!=Dec[p])
							S.insert(p);
						else if(S.count(p))
							S.erase(p);
						++p;
					}
				}
				break;
			}
			case 2:{
				k=read();
				reg int p=k>>5,q=k&((1<<5)-1);
				reg int ans=((Inc[p]>>q)^(Dec[p]>>q))&1;
				reg uint v1=Inc[p]%(1<<q),v2=Dec[p]%(1<<q);
				if(v1<v2)
					printf("%d\n",ans^1);
				else if(v1>v2||S.empty()||p<=*S.begin())
					printf("%d\n",ans);
				else{
					set<int>::iterator it=S.lower_bound(p);
					--it;
					if(Inc[*it]>Dec[*it])
						printf("%d\n",ans);
					else
						printf("%d\n",ans^1);
				}
				break;
			}
		}
	}
	return 0;
}