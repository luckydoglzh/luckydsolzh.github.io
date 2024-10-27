//问题：打印生成n个括号的所有方法

#include <cassert>
#include <iostream>
#include <vector>    
namespace backtracking {
class generate_parentheses {
 private:
    std::vector<std::string> res;  ///< Contains all possible valid patterns

    void makeStrings(std::string str, int n, int closed, int open);

 public:
    std::vector<std::string> generate(int n);
};

void generate_parentheses::makeStrings(std::string str, int n,
                                                     int closed, int open) {
    if (closed > open) 
        return;

    if ((str.length() == 2 * n) &&
        (closed != open)) {  
        return;
    }

    if (str.length() == 2 * n) {
        res.push_back(str);
        return;
    }

    makeStrings(str + ')', n, closed + 1, open);
    makeStrings(str + '(', n, closed, open + 1);
}

std::vector<std::string> generate_parentheses::generate(int n) {
    backtracking::generate_parentheses::res.clear();
    std::string str = "(";
    generate_parentheses::makeStrings(str, n, 0, 1);
    return res;
}
}  

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    int n = 0;
    std::vector<std::string> patterns;
    backtracking::generate_parentheses p;

    n = 1;
    patterns = {{"()"}};
    assert(p.generate(n) == patterns);

    n = 3;
    patterns = {{"()()()"}, {"()(())"}, {"(())()"}, {"(()())"}, {"((()))"}};

    assert(p.generate(n) == patterns);

    n = 4;
    patterns = {{"()()()()"}, {"()()(())"}, {"()(())()"}, {"()(()())"},
                {"()((()))"}, {"(())()()"}, {"(())(())"}, {"(()())()"},
                {"(()()())"}, {"(()(()))"}, {"((()))()"}, {"((())())"},
                {"((()()))"}, {"(((())))"}};
    assert(p.generate(n) == patterns);

    std::cout << "All tests passed\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
