#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=500000+5;

int n,m;
ll T;
int a[MAXN];
int lastl,lastr;

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	int K=read();
	while(K--){
		Init();
		Read();
		Work();
	}
	return 0;
}

inline void Init(void){
	lastl=lastr=0;
	return;
}

inline void Read(void){
	n=read(),m=read(),T=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

int temp[MAXN];

inline void Merge(reg int a[],reg int l,reg int mid,reg int r){
	reg int i=l,j=mid,k=l;
	while(i<mid&&j<=r)
		if(a[i]<a[j])
			temp[k++]=a[i++];
		else
			temp[k++]=a[j++];
	while(i<mid)
		temp[k++]=a[i++];
	while(j<=r)
		temp[k++]=a[j++];
	return;
}

int b[MAXN];

inline bool check(reg int l,reg int lastr,reg int r){
	for(reg int i=lastr;i<=r;++i)
		b[i]=a[i];
	sort(b+lastr,b+r+1);
	Merge(b,l,lastr,r);
	reg ll res=0;
	for(reg int i=1;i<=((r-l+1)>>1)&&i<=m;++i)
		res+=(ll)(temp[l+i-1]-temp[r-i+1])*(temp[l+i-1]-temp[r-i+1]);
	if(res<=T){
		for(reg int i=l;i<=r;++i)
			b[i]=temp[i];
		return true;
	}
	else
		return false;
}

inline void Work(void){
	reg int ans=0;
	reg int l=1,len=1,r=1;
	b[l]=a[l];
	while(r<=n){
		if(!len){
			++ans;
			len=1;
			l=++r;
			b[l]=a[l];
		}
		else if(r+len<=n&&check(l,r+1,r+len)){
			r+=len;
			len<<=1;
			if(r==n)
				break;
		}
		else
			len>>=1;
	}
	if(r==n)
		++ans;
	printf("%d\n",ans);
	return;
}
