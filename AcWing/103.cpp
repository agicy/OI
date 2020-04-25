#include<bits/stdc++.h>
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
const int MAXM=200000+5;

int n,m;
int a[MAXN],b[MAXM],c[MAXM];
int T[MAXN+(MAXM<<1)];
vector<int> V;

inline void Read(void);
inline void Work(void);

int main(void){
    Read();
    Work();
    return 0;
}

inline void Read(void){
    n=read();
    for(reg int i=1;i<=n;++i)
        a[i]=read();
    m=read();
    for(reg int i=1;i<=m;++i)
        b[i]=read();
    for(reg int i=1;i<=m;++i)
        c[i]=read();
    return;
}

inline void Work(void){
    for(reg int i=1;i<=n;++i)
        V.push_back(a[i]);
    for(reg int i=1;i<=m;++i)
        V.push_back(b[i]),V.push_back(c[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    for(reg int i=1;i<=n;++i)
        a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
    for(reg int i=1;i<=m;++i)
        b[i]=lower_bound(V.begin(),V.end(),b[i])-V.begin()+1;
    for(reg int i=1;i<=m;++i)
        c[i]=lower_bound(V.begin(),V.end(),c[i])-V.begin()+1;
    for(reg int i=1;i<=n;++i)
        ++T[a[i]];
    reg int Max1=0,Max2=0,pos=0;
    for(reg int i=1;i<=m;++i){
        if(Max1<T[b[i]]){
            Max1=T[b[i]];
            Max2=T[c[i]];
            pos=i;
        }
        else if(Max1==T[b[i]]&&Max2<T[c[i]]){
            Max2=T[c[i]];
            pos=i;
        }
    }
    printf("%d\n",pos);
    return;
}