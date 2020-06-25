#include <bits/stdc++.h>
using namespace std;

namespace FastIO        //使用命名空间
{
    char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
    int p, p3 = -1;
    inline int getc()
    {
        // *p1++
        //return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
        if( p1 == p2){ //指向buf的位置相同
            p1 = buf;   //p1 指向buf的开头

            //一次读入 1<<21个字符
            p2 = p1+ fread(buf,1,1<<21,stdin); //p2 = p1 + 读取字符的数量
            if( p1 == p2) // 相同表示没有读取
                return EOF; //返回EOF
       }
       else {
           p1++;   //p1 指向下一个位置
           return *(p1-1); //返回第一个位置的值
       }
    }
    inline int read()
    {
        int ret = 0, f = 0;
        char ch = getc();
        while (!isdigit(ch)) //不是数字
        {
            if (ch == '-')
                f = 1; // flag 置1,表示为负数
            ch = getc();
        }
        while (isdigit(ch))
        {
            //ret = ret * 10 + ch - 48;
            ret = (ret<<1) + (ret << 3) +ch-48;
            ch = getc();
        }
        return f ? -ret : ret;
    }
    inline void flush() // 清空缓存,程序结束要调用一次
    {
        fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
    }
    inline void print(int x) //解释todo
    {
        if (p3 > 1 << 20)
            flush();
        if (x < 0)
            buf2[++p3] = 45, x = -x;
        do
        {
            a[++p] = x % 10 + 48;
        } while (x /= 10);
        do
        {
            buf2[++p3] = a[p];
        } while (--p);
        buf2[++p3] = hh;
    }
}
#define read() FastIO::read()
#define print(x) FastIO::print(x)
