#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e5;
const int LG = 19;
int n,m,lg2[N + 5];
char a[N + 5];
int sa[N + 5],rk[(N << 1) + 5],tpr[(N << 1) + 5],c[N + 5],height[N + 5];
int st[LG + 5][N + 5];
void build_SA()
{
    static int m = 127;
    memset(c,0,sizeof c);
    for(register int i = 1;i <= n;++i)
        ++c[rk[i] = a[i]];
    for(register int i = 1;i <= m;++i)
        c[i] += c[i - 1];
    for(register int i = n;i;--i)
        sa[c[rk[i]]--] = i;
    for(register int w = 1,p = 0;p < n;w <<= 1,m = p)
    {
        p = 0;
        for(register int i = 1;i <= w;++i)
            tpr[++p] = n - w + i;
        for(register int i = 1;i <= n;++i)
            sa[i] > w && (tpr[++p] = sa[i] - w);
        memset(c,0,sizeof c);
        for(register int i = 1;i <= n;++i)
            ++c[rk[i]];
        for(register int i = 1;i <= m;++i)
            c[i] += c[i - 1];
        for(register int i = n;i;--i)
            sa[c[rk[tpr[i]]]--] = tpr[i];
        swap(rk,tpr),rk[sa[1]] = p = 1;
        for(register int i = 2;i <= n;++i)
            rk[sa[i]] = tpr[sa[i]] == tpr[sa[i - 1]] && tpr[sa[i] + w] == tpr[sa[i - 1] + w] ? p : ++p;
    }
    for(register int i = 1,k = 0;i <= n;++i)
    {
        k -= (bool)k;
        for(;a[i + k] == a[sa[rk[i] - 1] + k];++k);
        height[rk[i]] = k;
    }
}
int query(int l,int r)
{
    if(l == r)
        return n - sa[l] + 1;
    ++l;
    int lg = lg2[r - l + 1];
    return min(st[lg][l],st[lg][r - (1 << lg) + 1]);
}
struct node
{
    int sum;
    int ls,rs;
} seg[(N << 5) + 10];
int rt[N + 5];
void insert(int x,int &p,int tl,int tr)
{
    static int tot = 0;
    seg[++tot] = seg[p],++seg[p = tot].sum;
    if(tl == tr)
        return ;
    int mid = tl + tr >> 1;
    x <= mid ? insert(x,seg[p].ls,tl,mid) : insert(x,seg[p].rs,mid + 1,tr);
}
int query(int l,int r,int p,int q,int tl,int tr)
{
    if(l > r)
        return 0;
    if(l <= tl && tr <= r)
        return seg[q].sum - seg[p].sum;
    int mid = tl + tr >> 1;
    int ret = 0;
    l <= mid && (ret += query(l,r,seg[p].ls,seg[q].ls,tl,mid));
    r > mid && (ret += query(l,r,seg[p].rs,seg[q].rs,mid + 1,tr));
    return ret;
}
int query(int k,int p,int q,int tl,int tr)
{
    if(tl == tr)
        return tl;
    int mid = tl + tr >> 1;
    int sum = seg[seg[q].ls].sum - seg[seg[p].ls].sum;
    return k <= sum ? query(k,seg[p].ls,seg[q].ls,tl,mid) : query(k - sum,seg[p].rs,seg[q].rs,mid + 1,tr);
}
int main()
{
    scanf("%s%d",a + 1,&m),n = strlen(a + 1);
    for(register int i = 2;i <= n;++i)
        lg2[i] = lg2[i >> 1] + 1;
    build_SA();
    for(register int i = 1;i <= n;++i)
        st[0][i] = height[i];
    for(register int i = 1;i <= LG;++i)
        for(register int j = 1;j + (1 << i) - 1 <= n;++j)
            st[i][j] = min(st[i - 1][j],st[i - 1][j + (1 << i - 1)]);
    for(register int i = 1;i <= n;++i)
        insert(rk[i],rt[i] = rt[i - 1],1,n);
    for(int i,l,r,sum,L,R,Ls,Rs,mid,ans;m;--m)
    {
        scanf("%d%d%d",&i,&l,&r),i = rk[i];
        sum = query(1,i - 1,rt[l - 1],rt[r],1,n),
        sum < seg[rt[r]].sum - seg[rt[l - 1]].sum ? (R = query(sum + 1,rt[l - 1],rt[r],1,n),Rs = query(i,R)) : (Rs = -1),
        sum ? (L = query(sum,rt[l - 1],rt[r],1,n),Ls = query(L,i)) : (Ls = -1);
        if(Ls >= Rs)
        {
            printf("%d ",Ls),L = 1,R = i - 1,ans = i;
            while(L <= R)
                mid = L + R >> 1,query(mid,i) >= Ls ? (R = mid - 1,ans = mid) : (L = mid + 1);
            printf("%d\n",sa[query(query(1,ans - 1,rt[l - 1],rt[r],1,n) + 1,rt[l - 1],rt[r],1,n)]);
        }
        else
            printf("%d %d\n",Rs,sa[R]);
    }
}