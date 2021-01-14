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

const int MAXN=2e5+5;
const int mod=998244353;
const int inv[]={0,828542813,658841273,489139733,319438193,149736653,978279466,808577926,638876386,469174846,299473306,129771766,958314579,788613039,618911499,449209959,279508419,109806879,938349692,768648152,598946612,429245072,259543532,89841992,918384805,748683265,578981725,409280185,239578645,69877105,898419918,728718378,559016838,389315298,219613758,49912218,878455031,708753491,539051951,369350411,199648871,29947331,858490144,688788604,519087064,349385524,179683984,9982444,838525257,668823717,499122177,329420637,159719097,988261910,818560370,648858830,479157290,309455750,139754210,968297023,798595483,628893943,459192403,289490863,119789323,948332136,778630596,608929056,439227516,269525976,99824436,928367249,758665709,588964169,419262629,249561089,79859549,908402362,738700822,568999282,399297742,229596202,59894662,888437475,718735935,549034395,379332855,209631315,39929775,868472588,698771048,529069508,359367968,189666428,19964888,848507701,678806161,509104621,339403081,169701541,1};

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

int n,q;
int mul[MAXN],sum[MAXN];
set<int> S;

inline int calc(reg int l,reg int r){
	return 1ll*add(add(mul[l-1],sum[r-2]),mod-sum[l-1])*fpow(mul[r-1],mod-2)%mod;
}

int main(void){
	n=read(),q=read();
	mul[0]=1;
	for(reg int i=1;i<=n;++i){
		mul[i]=1ll*mul[i-1]*inv[read()]%mod;
		sum[i]=add(sum[i-1],mul[i]);
	}
	S.insert(1),S.insert(n+1);
	reg int ans=calc(1,n+1);
	while(q--){
		static int u;
		u=read();
		reg int l=*(--S.lower_bound(u)),r=*(S.upper_bound(u));
		reg int val=add(add(calc(l,u),calc(u,r)),mod-calc(l,r));
		if(S.count(u))
			ans=add(ans,mod-val),S.erase(u);
		else
			ans=add(ans,val),S.insert(u);
		printf("%d\n",ans);
	}
	return 0;
}