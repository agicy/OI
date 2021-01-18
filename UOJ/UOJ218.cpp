#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
    reg char ch=getchar();
    reg int res=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
    return res;
}

namespace SegmentTree{
    #define lson ( (k) << 1 )
    #define rson ( (k) << 1 | 1 )
    #define mid ( ( (l) + (r) ) >> 1 )
    struct Node{
        int sum,tag;
        #define sum(x) unit[(x)].sum
        #define tag(x) unit[(x)].tag
    };
    int tot;
    Node unit[MAXN<<2];
    inline void pushup(reg int k){
        sum(k)=sum(lson)+sum(rson);
        return;
    }
    inline void add(reg int k,reg int l,reg int r,reg int val){
        tag(k)+=val;
        sum(k)+=(r-l+1)*val;
        return;
    }
    inline void pushdown(reg int k,reg int l,reg int r){
        if(tag(k)){
            add(lson,tag(k)),add(rson,tag(k));
            tag(k)=0;
        }
        return;
    }
    inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
        if(L<=l&&r<=R){
            add(k,val);
            return;
        }
        pushdown(k,l,r);
        if(L<=mid)
            update(lson,l,mid,L,R,val);
        if(R>mid)
            update(rson,mid+1,r,L,R,val);
        pushup(k);
        return;
    }
    inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
        if(L<=l&&r<=R)
            return sum(k);
        if(L<=mid&&mid<R)
            return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
        else if(L<=mid)
            return query(lson,l,mid,L,R);
        else
            return query(rson,mid+1,r,L,R);
    }
    #undef lson
    #undef rson
    #undef mid
}

int main(void){
    n=read(),m=read(),ty=read();
    for(reg int i=1;i<=m;++i){
        static int opt,l,r,x,l1,r1;
        opt=read();
        switch(opt){
            case 1:{
                l1=read(),r1=read();
                l2=(l1+lastans*ty)%n+1;
                r2=(r1+lastans*ty)%n+1;
                l=min(l2,r2),r=max(l2,r2);

                break;
            }
            case 2:{
                l1=read();
                l=(l1+lastans*ty)%n+1;
                
                break;
            }
            case 3:{
                l1=read(),r1=read(),x=read();
                l2=(l1+lastans*ty)%n+1;
                r2=(r1+lastans*ty)%n+1;
                l=min(l2,r2),r=max(l2,r2);

                break;
            }
        }
    }
    return 0;
}