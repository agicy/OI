#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=3e5+5;
LL sumt[N], sumc[N], f[N];
int q[N];
int n, s;

int main(){
	cin>>n>>s;
	int t, c;
	for(int i=1; i<=n; ++i){
		cin>>t>>c;
		sumt[i]=sumt[i-1]+t;
		sumc[i]=sumc[i-1]+c;
	}
	int hh=0, tt=0;
	q[hh]=0;
	function<int(int)> bs=[&](int k){
		int l=hh, r=tt;
		if(l==r) return q[l];
		while(l<r){
			int mid=l+(r-l)/2;
			if(f[q[mid+1]]-f[q[mid]]<=k*(sumc[q[mid+1]]-sumc[q[mid]])) l=mid+1;
			else r=mid;
		}
		return q[r];
	};

	for(int i=1; i<=n; ++i){
		int pos=bs(s+sumt[i]);
		f[i]=f[pos]-(s+sumt[i])*sumc[pos]+sumt[i]*sumc[i]+s*sumc[n];
		// LL整型相乘的溢出问题
		while(hh<tt && (double)(f[q[tt]]-f[q[tt-1]])*(sumc[i]-sumc[q[tt]])>=(double)(f[i]-f[q[tt]])*(sumc[q[tt]]-sumc[q[tt-1]])) tt--;
		q[++tt]=i;
	}
	cout<<f[n]<<endl;
	return 0;
}