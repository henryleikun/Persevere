#define _CRT_SECURE_NO_WARNINGS 1

#include "stack.h"
//
//int main() {
//	ST st;
//	STiniti(&st);
//
//	STPush(&st, 1);
//	STPush(&st, 2);
//	STPush(&st, 3);
//	STPush(&st, 4);
//	STPush(&st, 5);
//
//	while (!STisEmpty(&st)) {
//		STdatatype tmp = STtop(&st);
//		STPop(&st);
//		printf("%d ", tmp);//栈大多都是这样用的 用完就出去了
//	}
//
//	STdestroy(&st);
//	return 0;
//}



bool isValid(char* s) {
    ST st;
    STiniti(&st);
    while (*s) {
        if (*s == '(' || *s == '{' || *s == '[') {
            STPush(&st, *s);
        }
        else {
            //右括号可能数量上大于左括号 
            if (STisEmpty(&st)) {
                STdestroy(&st);
                return false;
            }

            STdatatype tmp = STtop(&st);
            STPop(&st);
            if ((*s==')'&&tmp!='(')
                ||(*s==']'&&tmp!='[')
                ||(*s=='}'&&tmp!='{')) {//如果匹配
                STdestroy(&st);
                return false;
            }
            
        }
        s++;
    }

    //最后有可能栈里全是左括号 即左括号数量比右括号多
    bool ret = STisEmpty(&st);
    STdestroy(&st);

    return ret;
}



int main() {
    char s[3] = "()";

    int ret = isValid(s);

    printf("%d\n", ret);

    return 0;
}