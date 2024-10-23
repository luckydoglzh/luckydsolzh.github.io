// 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

// '.' 匹配任意单个字符
// '*' 匹配零个或多个前面的那一个元素
// 所谓匹配，是要涵盖 整个 字符串 s 的，而不是部分字符串。

bool isMatch(char * s, char * p){
    //如果p是空的，s是非空的 g了
    //如果p是空的，s也是空的,匹了
    if(!*p) 
    {
       return !*s;
    }
    
    //判一把第一个数字，如果第一个数相等，继续判下一个数字，第一个数字不相等，g
    bool first = *s && (*s == *p || *p == '.');
    if(*(p+1) == '*')
    {
        return isMatch(s,p+2) || (first && isMatch(++s,p));
    }
    else
    {
        return first && isMatch(++s,++p);
    }
}