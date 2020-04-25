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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000+5;

struct Node{
	int fa,size;
	int val;
    double w;
};

int n,root;
Node a[MAXN];

inline int find(void);

int main(void){
	reg int ans=0;
	n=read(),root=read();
	for(reg int i=1;i<=n;++i){
		a[i].val=read();
		ans+=a[i].val;
		a[i].w=a[i].val;
		a[i].size=1;
	}
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		a[y].fa=x;
	}
	for(reg int i=1;i<n;++i){
		reg int pos=find();
		reg int f=a[pos].fa;
		a[pos].w=0;
		ans+=a[pos].val*a[f].size;
		for(reg int j=1;j<=n;++j)
			if(a[j].fa==pos)
				a[j].fa=f;
		a[f].val+=a[pos].val;
		a[f].size+=a[pos].size;
		a[f].w=(double)(a[f].val)/a[f].size;
	}
	printf("%d\n",ans);
    return 0;
}

inline int find(void){
    reg int pos=0;
    reg double Max=0;
    for(reg int i=1;i<=n;++i)
        if(i!=root&&Max<a[i].w){
            Max=a[i].w;
            pos=i;
        }
    return pos;
}
