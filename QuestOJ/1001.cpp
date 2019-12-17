#include<cstdio>
#include<algorithm>
using std::sort;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	register char ch=getchar();
	register int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=30000+5;
const int MAXH=5000+5;

struct Node{
	int b,e,t;
	void Read(void){
		b=read(),e=read(),t=read();
		//scanf("%d%d%d",&b,&e,&t);
		return;
	}
	bool operator<(const Node &a)const{
		return e<a.e;
	}
};

bool vis[MAXN];
int n,h;
Node I[MAXH];

int main(void){
	register int i,j,sum;
	n=read(),h=read();
	//scanf("%d%d",&n,&h);
	for(i=1;i<=h;++i)
		I[i].Read();
	sort(I+1,I+h+1);
	for(i=1;i<=h;++i){
		sum=0;
		for(j=I[i].b;j<=I[i].e;++j)
			sum+=(int)vis[j];
		if(sum<I[i].t){
			sum-=I[i].t;
			for(j=I[i].e;j>=I[i].b;--j){
				if(!vis[j]){
					vis[j]=true;
					++sum;
					if(!sum)
						break;
				}
			}
		}
	}
	sum=0;
	for(i=1;i<=n;++i)
		sum+=(int)vis[i];
	printf("%d\n",sum);
	return 0;
}
