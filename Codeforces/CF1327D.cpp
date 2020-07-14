#include <bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=200000+5;

bool vis[MAXN],Ans[MAXN];
int n;
int p[MAXN],c[MAXN];
int V[MAXN];

inline bool check(reg int x,reg int len){
    reg bool flag=false;
    for(reg int i=0;i<x;++i){
        reg bool temp=true;
        reg int ID=i;
        for(reg int j=0;j<len/x;++j){
            if(c[V[ID]]!=c[V[(ID+x)%len]]){
				temp=0;
				break;
			}
            ID+=x;
        }
        if(temp){
			flag=true;
			break;
		}
    }
    return flag;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			vis[i]=Ans[i]=false;
		for(reg int i=1;i<=n;++i)
			p[i]=read();
		for(reg int i=1;i<=n;++i)
			c[i]=read();
		for(reg int i=1;i<=n;++i){
            if(!vis[i]){
                reg int ID=i,len=0;
                while(!vis[ID]){
                    vis[ID]=true;
                    V[len++]=ID;
                    ID=p[ID];
                }
                for(reg int j=1;j*j<=len;++j){
                    if(len%j==0){
						Ans[j]|=check(j,len);
						Ans[len/j]|=check(len/j,len);
					}
                }
            }
        }
        for(reg int i=1;i<=n;++i)
			if(Ans[i]){
				printf("%d\n",i);
				break;
			}
    }
    return 0;
}
