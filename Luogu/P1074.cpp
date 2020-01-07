#pragma GCC optimize (2)
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ( (x) & ( - (x) ) )
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

const int SIZE=9;
const int CSIZE=3;

int cnt[1<<SIZE];
int GetLog[1<<SIZE];

inline void Init(void){
    for(reg int i=0;i<(1<<SIZE);++i)
        for(reg int j=i;j;j-=lowbit(j))
            ++cnt[i];
    for(reg int i=0;i<SIZE;++i)
        GetLog[1<<i]=i;
    return;
}

struct Node{
    int num[SIZE][SIZE];
    int l[SIZE],r[SIZE],ch[SIZE];
    inline int GetID(reg int a,reg int b){
        return a/CSIZE*CSIZE+b/CSIZE;
    }
    inline void Change(reg int i,reg int j,reg int x){
        l[i]^=(1<<x);
        r[j]^=(1<<x);
        ch[GetID(i,j)]^=(1<<x);
        return;
    }
    inline int GetC(reg int i,reg int j){
        return l[i]&r[j]&ch[GetID(i,j)];
    }
    inline int Get(reg int i,reg int j){
        if(num[i][j]!=-1)
            return SIZE;
        else
            return cnt[GetC(i,j)];
    }
    inline int Read(void){
        reg int res=0;
        for(reg int i=0;i<SIZE;++i)
            l[i]=r[i]=ch[i]=(1<<SIZE)-1;
        for(reg int i=0;i<SIZE;++i){
            for(reg int j=0;j<SIZE;++j){
                num[i][j]=read()-1;
                if(num[i][j]!=-1)
                    Change(i,j,num[i][j]);
                else
                    ++res;
            }
        }
        return res;
    }
    inline int GetScore(void){
        reg int res=0;
        static const int G[9][9]={
            6,6,6,6,6,6,6,6,6,
            6,7,7,7,7,7,7,7,6,
            6,7,8,8,8,8,8,7,6,
            6,7,8,9,9,9,8,7,6,
            6,7,8,9,10,9,8,7,6,
            6,7,8,9,9,9,8,7,6,
            6,7,8,8,8,8,8,7,6,
            6,7,7,7,7,7,7,7,6,
            6,6,6,6,6,6,6,6,6};
        for(reg int i=0;i<SIZE;++i)
            for(reg int j=0;j<SIZE;++j)
                res+=(num[i][j]+1)*G[i][j];
        return res;
    }
};

int n;
int ans=-1;
Node a;

inline void DFS(reg int dep,Node &a){
    if(dep==0){
        ans=max(ans,a.GetScore());
        return;
    }
    reg int Min=SIZE,posx=-1,posy=-1;
    for(reg int i=0;i<SIZE;++i)
        for(reg int j=0;j<SIZE;++j){
            if(a.Get(i,j)==0)
                return;
            if(Min>a.Get(i,j)){
                Min=a.Get(i,j);
                posx=i,posy=j;
            }
        }
    if(posx==-1&&posy==-1)
        return;
    reg int k=a.GetC(posx,posy);
    while(k){
        a.Change(posx,posy,GetLog[lowbit(k)]);
        a.num[posx][posy]=GetLog[lowbit(k)];
        DFS(dep-1,a);
        a.num[posx][posy]=-1;
        a.Change(posx,posy,GetLog[lowbit(k)]);
        k-=lowbit(k);
    }
    return;
}

int main(void){
    Init();
    n=a.Read();
    DFS(n,a);
    printf("%d\n",ans);
    return 0;
}
