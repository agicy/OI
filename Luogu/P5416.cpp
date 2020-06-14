#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

int n,m;
ll c0;

namespace SegmentTree{
    #define lson ( (k) << 1 )
    #define rson ( (k) << 1 | 1 )
    #define mid ( ( (l) + (r) ) >> 1 )
    inline void Update(reg int k,reg int l,reg int,reg int L,reg int R,){
        if(l==r){
            return;
        }

        return;
    }
    #undef lson
    #undef rson
    #undef mid
}

int main(void){
    n=read(),m=read(),c0=read();
    for(reg int i=1;i<n;++i){
        static int opt,fr,id,x,y,z,c;
        opt=read(),fr=read(),id=read();
        switch(opt){
            case 0:{
                x=read(),y=read(),z=read(),c=read();

                break;
            }
            case 1:{

                break;
            }
            default:break;
        }
    }
	return 0;
}