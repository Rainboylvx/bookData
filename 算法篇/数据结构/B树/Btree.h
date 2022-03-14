
//靜态化动态
template<typename T,size_t size = 100>
struct MeM {
    size_t idx{0};
    //std::vector<T> mem(1000);
    std::array<T,size> mem;
    T* get() {return &mem[idx++];}
};

template<typename T,size_t deg>
struct BTreeNode
{
    static constexpr int maxKeySize{deg*2-1}; //最多key大小
    static constexpr int maxChildSize{deg*2}; //最多child大小
    static constexpr int degree{deg};
    static constexpr int half{deg-1}; //full之后的的一半
    //static constexpr Father * father;

    int n{0}; //当前key的数量
    bool leaf{true};
    T keys[maxKeySize];
    BTreeNode * child[maxChildSize];

    //二分查找 第一个 >= k的位置
    int bsearch(int k){
        int l = 0,r=n;
        while( l < r){
            int mid = (l+r) >> 1;
            if( keys[mid] < k) l = mid+1;
            else r = mid;
        }
        return l;
    }

    inline bool isFull() { return n == maxKeySize;}
    // 下标i的key的左边孩子
    inline auto& left(int i){ return child[i]; }
    // 下标i的key的右边孩子
    inline auto& right(int i){ return child[i+1]; }

    void traverse(); //遍历

    static BTreeNode* getNewNode() {
        static MeM<BTreeNode, 100000> mem;
        return mem.get();
    }

    /**
     * 插入一个k值,保证当前点是notFull的
     */
    void insertNonFull(int k);

    //分裂孩子,保证y是full的
    // i keys[i] 要空出来
    // y 指向孩子的
    void splitChild(int i,BTreeNode * y);
    // 从当前点开始search k
    BTreeNode* search(int k); 

/* ===================== 删除 =====================*/
    // 分成8个函数来使用
    //1) remove
    //2) removeFromLeaf
    //3) removeFromNonLeaf
    //4) getPred
    //5) getSucc
    //6) borrowFromPrev
    //7) borrowFromNext
    //8) merge
    //9) findKey

    /**
     * 删除值k
     */
    void remove(int k);

    /**
     * 从leaf上删除下标为idx的点
     */
    void removeFromLeaf(int idx);

    /**
     * 从一个内部点上删除下标为idx的点
     */
    void removeFromNonLeaf(int idx);

    // 得到下标为idx这个key的前趋
    T getPred(int idx);

    // 得到下标为idx这个key的后趋
    T getSucc(int idx);

    // 填充 idx下标的孩子,如果这个孩子少于t-1keys
    void fill(int idx);

    // 借idx的左兄弟借一个key,放到idx上
    void borrowFromPrev(int idx);

    // 借idx的右兄弟借一个key,放到idx上
    void borrowFromNext(int idx);

    // 合并 idx的左右孩子
    void merge(int idx);
/* ===================== 删除 END =====================*/

    //点移动
    //从 src的下标为src_pos点开始到dst的下标dst_pos的点 移size个点
    //只移动每个点的右孩子
    void moveBettwenTwo(BTreeNode* src,BTreeNode* dst,int src_pos,int dst_pos,int size){
        if(src == dst) { //两都不能一样
            std::cout << "error at"; // TODO 
        }
        for(int i = size-1; i>=0; --i){
            dst->keys[dst_pos+i] = std::move(src->keys[src_pos+i]);
        }
    }
    //每个点从i开始向左移动1格
    //   
    //   
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  |   | 1 | 2 | 3 | 4 |   |
    //  +---+---+---+---+---+---+
    //          |   |   |   |   |    
    //          v   v   v   v   v    
    //          x   y   z
    //
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  | 1 | 2 | 3 | 4 |   |   |
    //  +---+---+---+---+---+---+
    //      |   |   |   |   |   |    
    //      v   v   v   v   v   v    
    //      x   y   z
    //
    //
    void moveLeftOne(int pos){
        for(int i = pos ; i< n;i++){
            keys[i-1] = std::move(keys[i]);
            right(i-1) = right(i);
        }
        n-=1;
    }

    //   
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  |   | 1 | 2 | 3 | 4 |   |
    //  +---+---+---+---+---+---+
    //          |   |   |   |   |    
    //          v   v   v   v   v    
    //          x   y   z
    //
    //       pos +1  +2  +3
    //  +---+---+---+---+---+---+
    //  |   |   | 1 | 2 | 3 | 4 |
    //  +---+---+---+---+---+---+
    //          |   |   |   |   |    
    //          v   v   v   v   v    
    //              x   y   z
    void moveRightOne(int pos){
        for(int i = n ; i > pos ;i--){
            keys[i] = std::move(keys[i-1]);
            right(i) = right(i-1);
        }
        n+=1;
    }
};
