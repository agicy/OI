class MinStack {
public:
    /** initialize your data structure here. */
	stack<int> S,Smin;
    MinStack() {
		while(!S.empty())
			S.pop();
		while(!Smin.empty())
			Smin.pop();
		return;
    }
    
    void push(int x){
        S.push(x);
		if(!Smin.empty())
			Smin.push(min(Smin.top(),x));
		else
			Smin.push(x);
		return;
    }
    
    void pop() {
        S.pop();
		Smin.pop();
		return;
    }
    
    int top() {
        return S.top();
    }
    
    int getMin() {
        return Smin.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
