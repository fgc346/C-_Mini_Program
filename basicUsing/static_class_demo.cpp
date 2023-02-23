#include "static_class_demo.h"

int main()
{
    Test a(1);
    a.print();
    printAge(Test::age);
    Example example;
    // Example::debug.any();
    auto debug_1 = Example::debug;
    if(debug_1.any())
    {
        printf(" the debug is called\n");
    };
    auto data_val = Example::data.ival;
    printf("the data_val = %d data.ival= %d\n", data_val, Example::data.ival);
    
    printf("b_1 = %d, c_1 = %c, i_1 = %d\n", Example::b_1, Example::c_1, Example::i_1);
    printf("cb_1 = %d, cc_1 = %c, ci_1 = %d\n", Example::cb1, Example::cc1, Example::ci1);
    printf("cb_2 = %d, cc_2 = %c, ci_2 = %d\n", Example::cb2, Example::cc2, Example::ci2);
    printf("cexprb2 = %d, cexprc2 = %c, cexpri2 = %d\n", Example::cexprb2, Example::cexprc2, Example::cexpri2);
    printf("f_1 = %f, d_1 = %f\n", Example::f_1, Example::d_1);
    printf("cexprf2 = %f, cexprd2 = %f\n", Example::cexprf2, Example::cexprd2);
    // printf("cf1 = %f, cd1 = %f\n", Example::cf1, Example::cd1);

    return 0;
}