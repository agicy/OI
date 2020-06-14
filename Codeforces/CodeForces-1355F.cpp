#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const ll p[17]={19634730635520000ll,67665248476907597ll,877779077635511999ll,15031861979012587ll,239868713978954299ll,8100049778130103ll,32826117705688133ll,96265407405451883ll,260006624961107813ll,707992818804600227ll,3676594834162829ll,6402204344683229ll,9797084445859807ll,15916020492768661ll,27616086651273059ll,41286304414422503ll,229580147ll};

int T;

int main(void){
	scanf("%d",&T);
	while(T--){
		reg ll x=1;
		for(reg int i=0;i<17;++i){
			static ll y;
			cout<<"? "<<p[i]<<endl;
			cin>>y;
			x*=y;
		}
		reg ll ans=1;
		for(reg int i=2;i<=800;++i){
			reg int c=0;
			while(x%i==0){
				x/=i;
				++c;
			}
			ans*=c+1;
		}
		cout<<"! "<<max(8ll,ans<<1)<<endl;
	}
	return 0;
}