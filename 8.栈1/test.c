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
//		printf("%d ", tmp);//ջ��඼�������õ� ����ͳ�ȥ��
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
            //�����ſ��������ϴ��������� 
            if (STisEmpty(&st)) {
                STdestroy(&st);
                return false;
            }

            STdatatype tmp = STtop(&st);
            STPop(&st);
            if ((*s==')'&&tmp!='(')
                ||(*s==']'&&tmp!='[')
                ||(*s=='}'&&tmp!='{')) {//���ƥ��
                STdestroy(&st);
                return false;
            }
            
        }
        s++;
    }

    //����п���ջ��ȫ�������� �������������������Ŷ�
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