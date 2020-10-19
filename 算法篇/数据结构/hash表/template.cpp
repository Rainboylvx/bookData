struct hashMap {
    static int size = 1e5+5;
    typedef pair<int,int> pii;
    vector<vecotr<pii> > hash(size);
    void init(){
        for(int i =0;i < hash.size();i++) hash[i].clear();
    }
    void insert(int n,int val){
        int p = n % size;
        for(int i = 0 ;i< hash[p].size();i++){
            if( hash[p][i].first == val){
                hash[p][i].second++;
                return;
            }
        }
        hash[p].push_back(make_pair(val,1));
    }
}
