#define reg register

extern "C" int Seniorious(int);

extern "C" int Chtholly(int n, int c){
	reg int l=1,r=n,mid;
	while(l<=r){
		mid=(l+r)>>1;
		reg int res=Seniorious(mid);
		switch(res){
			case 0:{
				return mid;
				break;
			}
			case -1:{
				l=mid+1;
				break;
			}
			case 1:{
				r=mid-1;
				break;
			}
		}
	}
	return l;
}