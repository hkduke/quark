#include <iostream>


// test for inline asm
/*
 * asm(
 *  "汇编语句1;\n"
 *  "汇编语句2;\n"
 *  "汇编语句3;\n"
 *  :"输出列表"
 *  :"输入列表"
 *  :"破坏寄存器列表"
 * )
 *
 */
int AsmAdd0(int a, int b) {
asm(
  "movl %1,%%eax\n\t"
  "addl %0,%%eax\n\t"
  "movl %%eax,%0\n\t"
  :"+r"(b)
  :"r"(a)
  :"%eax"
  );
  return b;
}

void AsmAdd1(int a, int b, int* c) {
asm (
  "addl %1, %2\n\t"
  "movl %2, (%0)\n\t"
  :"=r"(c)
  :"r"(a), "r"(b) 
);
}

void AsmAdd2(int a, int b, int* c) {
asm (
  "addl %1, %2\n\t"
  "movl %2, %0\n\t"
  :"=m"(*c)
  :"r"(a), "r"(b) 
);
}

/// *b <----- a
///
void AsmSet(int a, int *b) {
    asm(
    "movl %1, %%eax\n\t"
    "movl %%eax, %0\n\t"
    :"=m"(*b)
    :"r"(a)   
    :"%eax"
    );
}



void testM() {
    int x;
    int a = 10;
    asm( "addl %1, %%ebx\n\t"
         "movl %1,%0\n\t"
         "addl %%eax, %%ebx"
         :"=m"(x):"r"(a):"%eax","%ebx"); //%0会被替换为`(x的偏移量)`
    std::cout << x << std::endl;
}

template<typename T>
void SwapByAsm(T* a, T* b) {
    asm(
      "movq (%0), %%rax\n\t"
      "movq (%1), %%rbx\n\t"
      "movq %%rbx, (%0)\n\t"
      "movq %%rax, (%1)\n\t"
      :"+r"(a), "+r"(b)
      :
      :"%rax","%rbx"
    );
}
template<>
void SwapByAsm(char* a, char* b) {
    asm(
      "movb (%0), %%al\n\t"
      "movb (%1), %%bl\n\t"
      "movb %%bl, (%0)\n\t"
      "movb %%al, (%1)\n\t"
      :"+r"(a), "+r"(b)
      :
      :"%al","%bl"
    );
}

int main() {
    int a = 20;
    int b = 10;
    int c = -1;
    testM();
    std::cout << "--------AsmAdd--------" << std::endl;

    c = AsmAdd0(a, b);
    std::cout << "c:" << c << std::endl;
    
    c = -1;
    AsmAdd1(a, b, &c);
    std::cout << "c:" << c << std::endl;

    c = -1;
    AsmAdd2(a, b, &c);
    std::cout << "c:" << c << std::endl;

    std::cout << "-------SwapByAsm---------" << std::endl;
    double x0 = 0.91, x1 = 10.24;
    char   c0 = 'X',  c1 = 'a';
    
    std::cout << "before: x0:" << x0 << ", x1: " << x1 << std::endl;
    SwapByAsm(&x0, &x1);
    std::cout << "after : x0:" << x0 << ", x1: " << x1 << std::endl;
    
    std::cout << "before: c0:" << c0 << ", c1:" << c1 << std::endl; 
    SwapByAsm(&c0, &c1);
    std::cout << "after : c0:" << c0 << ", c1:" << c1 << std::endl; 

    return 0;
}
