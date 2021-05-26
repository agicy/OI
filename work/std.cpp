
//std:
#include<algorithm>
#include<cstdio>
#include<vector>
#define pb push_back
#define ll long long
#define MaxN 405
using namespace std;
const int mod=998244353;
ll powM(ll a,int t=mod-2){
  ll ret=1;
  while(t){
    if (t&1)ret=ret*a%mod;
    a=a*a%mod;t>>=1;
  }return ret;
}
ll c[MaxN][MaxN][2];
void Init(int n)
{
  ll buf=1;
  for (int i=0;i<=n;i++){
    c[i][0][0]=c[i][0][1]=1;
    for (int j=1;j<=n;j++){
      c[i][j][1]=c[i][j-1][1]*buf%mod;
      c[i][j][0]=c[i][j-1][0]*(buf-1)%mod;
    }buf=buf*2%mod;
  }
}
vector<int> g[MaxN];
int siz[MaxN],len[MaxN];
ll f[MaxN][MaxN][2];
void dfs(int u)
{
  if (!u)return ;
  f[u][0][1]=1;
  for (int i=0,v;i<g[u].size();i++){
    dfs(v=g[u][i]);
    siz[u]+=siz[v];
    for (int k=siz[u];k>=0;k--){
      ll sav0=0,sav1=0;
      for (int j=0;j<=min(siz[v],k);j++){
        ll buf=(f[v][j][0]+f[v][j][1])*(f[u][k-j][0]+f[u][k-j][1])%mod,
           buf2=f[v][j][1]*f[u][k-j][1]%mod;
        sav0+=buf-buf2;sav1+=buf2;
      }f[u][k][0]=sav0%mod;
      f[u][k][1]=sav1%mod;
    }
  }for (int p=0;p<=siz[u];p++){
    f[u][p][0]=f[u][p][0]*c[siz[u]-p][len[u]][0]%mod;
    f[u][p][1]=f[u][p][1]*c[siz[u]-p][len[u]][1]%mod;
  }
}
int n,h[MaxN],tn;
int build(int l,int r,int pre)
{
  int mx=*min_element(h+l,h+r+1),
      u=++tn,p=l;
  len[u]=mx-pre;
  for (int i=l;i<=r;i++)
    if (h[i]==mx){
      g[u].pb(0);
      if (p<i)g[u].pb(build(p,i-1,mx));
      p=i+1;
    }
  if (p<=r)g[u].pb(build(p,r,mx));
  return u;
}
int main()
{
  scanf("%d",&n);Init(n);
  for (int i=1;i<=n;i++)
    scanf("%d",&h[i]);
  siz[0]=1;f[0][1][1]=mod-1;f[0][0][1]=f[0][1][0]=1;
  //0节点代表空行 
  int rt=build(1,n,0);
  dfs(rt);
  ll ans=0;
  for (int p=0;p<=n;p++)
    ans+=f[rt][p][0]+f[rt][p][1];
  printf("%lld",(ans%mod+mod)%mod);
  return 0;
}