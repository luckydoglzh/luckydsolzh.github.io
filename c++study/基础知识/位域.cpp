#include <iostream>
using namespace std;

struct stuff {
  unsigned int field1 : 30;
  unsigned int : 2;       // 空白位域，不能初始化
  unsigned int field2 : 4;
  unsigned int : 0;       // 强制对齐位域，不能初始化
  unsigned int field3 : 3;
};

int main() {
  struct stuff s = {1, 5};  // 初始化 field1 = 1, field2 = 5，field3 默认为 0
  cout << s.field1 << endl;  // 输出 field1
  cout << s.field2 << endl;  // 输出 field2
  cout << s.field3 << endl;  // 输出 field3
  cout << sizeof(s) << endl; // 输出结构体的大小
  return 0;
}
