#include<cstdio>
#include<algorithm>
using std::max;
using std::sort;
using std::lower_bound;
using std::upper_bound;
#define reg register
#define abs(x) ( (x) < 0 ? ( - (x) ) : (x) )
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

const int MAXN=2000+5;

int n;
int l[MAXN];

int main(void){
	reg int i,j,k,ans=0;
	n=read();
	for(i=1;i<=n;++i)
		l[i]=read();
	sort(l+1,l+n+1);
	for(i=1;i<=n-2;++i)
		for(j=i+1;j<n;++j)
			for(k=j+1;k<=n;++k)
				if(l[i]+l[j]>l[k])
					++ans;
				else
					break;
	printf("%d\n",ans);
	return 0;
}
