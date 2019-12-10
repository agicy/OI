#include<cstdio>
#include<algorithm>
using std::sort;
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

struct Cow{
	int l,r;
	inline void Read(void){
		l=read(),r=read();
		return;
	}
	inline bool operator<(const Cow& a)const{
		return r<a.r;
	}
};

struct Lotion{
	int cnt,L;
	inline void Read(void){
		L=read(),cnt=read();
		return;
	}
	inline bool operator<(const Lotion& a)const{
		return L<a.L;
	}
};

const int MAXC=2500+5;
const int MAXL=2500+5;

int C,L;
Cow cow[MAXC];
Lotion lotion[MAXL];

int main(void){
	reg int i,j,ans=0;
	C=read(),L=read();
	for(i=1;i<=C;++i)
		cow[i].Read();
	for(i=1;i<=L;++i)
		lotion[i].Read();
	sort(cow+1,cow+C+1);
	sort(lotion+1,lotion+L+1);
	for(i=1;i<=C;++i)
		for(j=1;j<=L;++j)
			if(cow[i].l<=lotion[j].L&&lotion[j].L<=cow[i].r&&lotion[j].cnt){
				--lotion[j].cnt;
				++ans;
				break;
			}
	printf("%d\n",ans);
	return 0;
}
