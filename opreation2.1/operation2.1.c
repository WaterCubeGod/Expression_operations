#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define STACK_MAX_SIZE   50
typedef char ElemType;
typedef int Static;
typedef struct {
	ElemType* top;
	ElemType* base;
	int size;
}SqStack;
//��ʼ��
Static initStack(SqStack* S) {
	S->base = (ElemType*)malloc(sizeof(ElemType) * STACK_MAX_SIZE);
	if (!S->base) {
		return 0;
	}
	S->top = S->base;
	S->size = STACK_MAX_SIZE;
	return 1;
}
//��ջ
Static emptyStack(SqStack* S) {
	return S->top == S->base;
}
//��ջ
Static PUSH(SqStack* S, ElemType e) {
	if (S->top - S->base >= S->size - 1) {
		return 0;
	}
	*S->top = e;
	S->top++;
	return 1;
}
//��ջ
ElemType POP(SqStack* S) {
	if (emptyStack(S)) {
		return 0;
	}
	S->top--;
	return *S->top;
}
//��ȡջ��Ԫ��
ElemType getTop(SqStack* S) {
	ElemType e;
	if (emptyStack(S)) {
		return 0;
	}
	e = *(S->top - 1);
	return e;
}
//�Ƚ����ȼ�
Static priority(ElemType a, ElemType b) {
	int flag = 0;
	switch (a) {
	case '(':
		flag = 1;
		break;
	case '+':
		if (b == '+' || b == '-')flag = 1;
		break;
	case '-':
		if (b == '+' || b == '-')flag = 1;
		break;
	case ')':
		flag = 1;
		break;
	case '*':
		if (b != '(')flag = 1;
		break;
	case '/':
		if (b != '(')flag = 1;
		break;
	default:
		break;
	}
	return flag;
}
//�ж��Ƿ��������
Static calculation(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '(') return 1;
	return 0;
}
//�沨��ʽ
Static nibolan(ElemType* c1, ElemType* c2) {
	ElemType* str1 = c1;
	SqStack* stack;
	SqStack S;
	stack = &S;
	initStack(stack);
	int n = 0;
	PUSH(stack, '#');
	while (*str1) {
		ElemType e = '0';
		e = getTop(stack);
		//�����
		if (calculation(*str1)) {
			ElemType e = '0';
			e = getTop(stack);
			if (e == '#') {
				PUSH(stack, *str1);
			}
			//�Ƚ����ȼ������в�ͬ�Ķ���
			else if (priority(e, *str1)) {
				if (e != '(') {
					*c2 = e;
					c2++;
					n++;
				}
				POP(stack);
				PUSH(stack, *str1);
			}
			else {
				if (*str1 != ')') {
					PUSH(stack, *str1);
				}
				else {
					while (*(stack->top - 1) != '#') {
						e = getTop(stack);
						*c2 = e;
						c2++;
						n++;
						POP(stack);
					}
				}
			}
		}
		//��ĸ
		else {
			*c2 = *str1;
			c2++;
			n++;
		}
		str1++;
	}
	//ʣ�������
	while (*(stack->top - 1) != '#') {
		*c2 = getTop(stack);
		if (*stack->top != '#') {
			c2++;
			n++;
		}
		POP(stack);
	}
	return 1;
}
//������������
int CalS(int a, int b, ElemType c) {
	if (c == '+') {
		return a + b;
	}
	if (c == '-') {
		int c = a - b;
		return a - b;
	}
	if (c == '*') {
		return a * b;
	}
	if (c == '/') {
		return a / b;
	}
	return 0;
}
//��������
ElemType Cal(SqStack* OPND, ElemType c) {
	ElemType e;

	ElemType B = POP(OPND);
	ElemType A = POP(OPND);
	int a = (int)A - 48;
	int b = (int)B - 48;
	e = (ElemType)(CalS(a, b, c) + 48);
	return e;
}
//��׺���ʽ����
int Calculate(char* c, int n) {
	char* str = c;
	//�������
	SqStack* OPND;
	SqStack s1;
	OPND = &s1;

	initStack(OPND);

	PUSH(OPND, '#');
	int a = 1;
	while (str) {
		ElemType e = *str;
		//�ж��Ƿ�Ϊ�����
		//ÿ������������Ͷ�ǰ�������м��㲢������������ջ��
		if (calculation(e)) {
			PUSH(OPND, Cal(OPND, e));
			int t = 0;
		}
		else {
			PUSH(OPND, e);
		}
		str++;
		char k = getTop(OPND);
		if (a >= n) {
			break;
		}
		a++;
	}
	int b = (int)(getTop(OPND) - 48);
	return b;
}

int main() {
	char* c = (char*)malloc(sizeof(char) * 50);
	int n;
	scanf("%s", c);
	scanf("%d", &n);
	char* c1 = (char*)malloc(sizeof(char) * 9);
	char* c2 = c1;
	nibolan(c, c1);
	printf("%d", Calculate(c1, n));
}