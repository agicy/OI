// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution{
public:
	vector<int> specialSort(int N){
		#define reg register
		vector<int> res;
		res.push_back(1);
		for(reg int i=2;i<=N;++i){
			reg int l=0,r=res.size()-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(compare(res[mid],i))
					l=mid+1;
				else
					r=mid-1;
			}
			res.push_back(i);
			for(reg int j=res.size()-2;j>r;--j)
				swap(res[j],res[j+1]);
		}
		return res;
		#undef reg
	}
};