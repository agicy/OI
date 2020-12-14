#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXK=1e6;
const int MAXS=2*MAXK+5;
const int Delta=1e6+1;
const int MAXN=1e5+5;

int n;

namespace BIT_greater{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n=Delta+MAXK,unit[MAXS];
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

namespace BIT_less{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n=Delta+MAXK,unit[MAXS];
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

bool del[MAXN];
int col[MAXN],val[MAXN];

int main(void){
	n=read();
	reg int tot=0;
	reg int cnt=0;
	for(reg int i=1;i<=n;++i){
		static char opt;
		static int a,b,c,k;
		do
			opt=getchar();
		while(!isalpha(opt));
		switch(opt){
			case 'A':{
				a=read(),b=read(),c=read();
				++tot;
				if(!a)
					if(b>c)
						++cnt,col[tot]=3;
					else
						col[tot]=0;
				else if(a>0){
					val[tot]=floor(1.0*(c-b)/a);
					if(val[tot]>1e6)
						col[tot]=0;
					else if(val[tot]<-1e6)
						col[tot]=3,++cnt;
					else
						col[tot]=1,BIT_greater::update(val[tot]+Delta,1);
				}
				else{
					val[tot]=ceil(1.0*(c-b)/a);
					if(val[tot]<-1e6)
						col[tot]=0;
					else if(val[tot]>1e6)
						++cnt,col[tot]=3;
					else
						col[tot]=2,BIT_less::update(val[tot]+Delta,1);
				}
				break;
			}
			case 'D':{
				k=read();
				if(del[k])
					continue;
				del[k]=true;
				switch(col[k]){
					case 1:{
						BIT_greater::update(val[k]+Delta,-1);
						break;
					}
					case 2:{
						BIT_less::update(val[k]+Delta,-1);
						break;
					}
					case 3:{
						--cnt;
						break;
					}
				}
				break;
			}
			case 'Q':{
				k=read();
				printf("%d\n",BIT_greater::query(k-1+Delta)+BIT_less::query(1e6+Delta)-BIT_less::query(k+Delta)+cnt);
				break;
			}
		}
	}
	return 0;
}