# 深度优先搜索

## DFS重要的点

 - 边界条件
 - 搜索的状态表示(dfs的参数)
 - 搜索的状态转移(如果从一种状态过渡到另一种的状态的)
 - **状态:**能唯一表明事物所处的一种形态


## 回溯大法

**如果不行,就返上一步重新尝试**

## DFS框架


// 状态小的时候,
可以用参数来表示状态

```c

void dfs( state arguments){
    
    for(i=0;i<=max;i++){
        
        state_next = opt
        //

        dfs(state_next)
                        
    }
}
```

// 状态大的时候,
用全局变量来表示状态,每次操作都修改这个全局变量,但是在回溯的时候又把这个全局变量重置回来.

```
 state arguments
void dfs(){
    
    for(i=0;i<=max;i++){
        
        state_next = opt
        //
        dfs()
        unset state_next
                        
    }
}
```
