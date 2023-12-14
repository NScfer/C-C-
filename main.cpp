#include <stdio.h>
#include <ctype.h>
#include <math.h>

/**
 * @brief ջ�����ݽṹ
 */
#define MAX_SIZE 100

typedef struct Stack {
    double items[MAX_SIZE]; // �洢ջԪ�ص�����
    int top; // ջ��ָ��
} Stack;

/**
 * @brief ��Ԫ��ѹ��ջ��
 * 
 * @param ps ָ��ջ��ָ��
 * @param x ��ѹ���Ԫ��
 */
void Push(Stack *ps, double x) {
    if (ps->top == MAX_SIZE - 1) {
        printf("Stack overflow"); // ���ջ������ӡ������Ϣ
        return;
    } else {
        ps->top++; // ջ��ָ���һ
        ps->items[ps->top] = x; // ��Ԫ��ѹ��ջ��
    }
}

/**
 * @brief ����ջ��Ԫ��
 * 
 * @param ps ָ��ջ��ָ��
 * @return ������ջ��Ԫ��
 */
double Pop(Stack *ps) {
    double temp;
    if (ps->top == -1) {
        printf("Stack underflow"); // ���ջ�գ���ӡ������Ϣ
        return 0;
    } else {
        temp = ps->items[ps->top]; // ����ջ��Ԫ��
        ps->top--; // ջ��ָ���һ
        return temp; // ����ջ��Ԫ��
    }
}

/**
 * @brief �ж�ջ�Ƿ�Ϊ��
 * 
 * @param ps ָ��ջ��ָ��
 * @return ���ջΪ�շ���true�����򷵻�false
 */
bool IsEmpty(Stack *ps) {
    return ps->top == -1; // �ж�ջ�Ƿ�Ϊ��
}

/**
 * @brief ��ȡջ��Ԫ��
 * 
 * @param ps ָ��ջ��ָ��
 * @return ջ��Ԫ��
 */
double GetTop(Stack *ps) {
    if (ps->top == -1) {
        printf("Stack underflow"); // ���ջ�գ���ӡ������Ϣ
        return 0;
    } else {
        return ps->items[ps->top]; // ����ջ��Ԫ��
    }
}

/**
 * @brief ���ջ
 * 
 * @param ps ָ��ջ��ָ��
 */
void Clear(Stack *ps) {
    ps->top = -1; // ��ջ��ָ����Ϊ-1
}

int Isp(char op) {
    // �����������������ջ�ڵ����ȼ�
    switch (op) {
        case '=':
            // �Ⱥŵ����ȼ���ͣ�Ϊ0
            return 0;
        case '(':
            // �����ŵ����ȼ�Ϊ1
            return 1;
        case '^':
            // ����������ȼ���ߣ�Ϊ7
            return 7;
        case '*':
        case '/':
        case '%':
            // �˷���������ȡ������ȼ�Ϊ5
            return 5;
        case '+':
        case '-':
            // �ӷ��ͼ��������ȼ�Ϊ3
            return 3;
        case ')':
            // �����ŵ����ȼ�Ϊ8
            return 8;
        default:
            // �������Ĳ������������������-1
            return -1;
    }
}
/**
 *  @brief �����������������ջ������ȼ�
 * @param op
 */
int Icp(char op) {
    // �����������������ջ������ȼ�
    switch (op) {
        case '=':
            // �Ⱥŵ����ȼ���ͣ�Ϊ0
            return 0;
        case '(':
            // �����ŵ����ȼ���ߣ�Ϊ8
            return 8;
        case '^':
            // ����������ȼ�Ϊ6
            return 6;
        case '*':
        case '/':
        case '%':
            // �˷���������ȡ������ȼ�Ϊ4
            return 4;
        case '+':
        case '-':
            // �ӷ��ͼ��������ȼ�Ϊ2
            return 2;
        case ')':
            // �����ŵ����ȼ�Ϊ1
            return 1;
        default:
            // �������Ĳ������������������-1
            return -1;
    }
}
/**
 *  @brief �ж��ַ��Ƿ�Ϊ�����
 * @param ch
 */
bool IsOperator(char ch) {
    // �ж��ַ��Ƿ�Ϊ�����
    return ch == '=' || ch == '(' || ch == '^' || ch == '*' || ch == '/' || ch == '%' || ch == '+' || ch == '-' || ch == ')';
}
/**
 *  @brief �������л�ȡһ���ַ�
 * @param ch
 */
void GetChar(char *ch) {
    // �������л�ȡһ���ַ�
    scanf(" %c", ch);
}

/**
 * @brief �Ӳ�����ջ�л�ȡ����������
 *
 * ���������ջΪ�ջ���ֻ��һ��Ԫ�أ���ô�������ӡ������Ϣ������false��
 * ����ɹ���ȡ����������������ô�����᷵��true��
 *
 * @param opnd ������ջ��ָ��
 * @param x ���ڴ洢��ջ�л�ȡ�ĵ�һ��������
 * @param y ���ڴ洢��ջ�л�ȡ�ĵڶ���������
 * @return ����ɹ���ȡ������������������true�����򷵻�false
 */
bool GetTwoOperands(Stack *opnd, double *x, double *y) {
    // ��������ջ�Ƿ�Ϊ��
    if (IsEmpty(opnd)) {
        printf("���ʽ�д�!\n");
        return false;
    }
    // ��ջ�л�ȡ�ڶ���������
    *y = GetTop(opnd);
    Pop(opnd);

    // �ٴμ�������ջ�Ƿ�Ϊ��
    if (IsEmpty(opnd)) {
        printf("���ʽ�д�!\n");
        return false;
    }
    // ��ջ�л�ȡ��һ��������
    *x = GetTop(opnd);
    Pop(opnd);

    return true;
}

/**
 * @brief ִ�в���������
 *
 * ���ݴ���Ĳ��������Ӳ�����ջ�л�ȡ������������ִ����Ӧ�Ĳ�����
 *
 * @param opnd ������ջ��ָ��
 * @param op ������
 * @return ����ɹ�ִ�в���������true�����򷵻�false
 */
bool DoOperator(Stack *opnd, char op) {
    double x, y;
    bool result = GetTwoOperands(opnd, &x, &y);
    if (result) {
        switch (op) {
            case '+':
                Push(opnd, x + y); // ִ�мӷ�����
                break;
            case '-':
                Push(opnd, x - y); // ִ�м�������
                break;
            case '*':
                Push(opnd, x * y); // ִ�г˷�����
                break;
            case '/':
                if (y == 0) {
                    printf("����Ϊ��!\n");
                    return false; // �������Ϊ�㣬��ӡ������Ϣ������false
                }
                Push(opnd, x / y); // ִ�г�������
                break;
            case '%':
                if ((long) y == 0) {
                    printf("����Ϊ��!\n");
                    return false; // �������Ϊ�㣬��ӡ������Ϣ������false
                }
                Push(opnd, (long) x % (long) y); // ִ��ȡģ����
                break;
            case '^':
                Push(opnd, pow(x, y)); // ִ�����������
                break;
        }
        return true; // ����true��ʾ�ɹ�ִ�в���
    } else {
        return false; // ����false��ʾ��ȡ������ʧ��
    }
}

/**
 * @brief ���м�����
 *
 * �������ж�ȡ���ʽ�������ݲ����������ȼ����м��㣬������������
 *
 * @param opnd ������ջ��ָ��
 * @param optr ������ջ��ָ��
 */
void Run(Stack *opnd, Stack *optr) {
    Clear(opnd); // ��ղ�����ջ
    Clear(optr); // ��ղ�����ջ
    char ch, optr_top, prior_char, op;
    double operand;
    Push(optr, '='); // ��'='ѹ�������ջ��Ϊ��ʼ����
    prior_char = '='; // ��ʼ��prior_charΪ'='
    GetChar(&ch); // �������л�ȡ�ַ�
    optr_top = GetTop(optr); // ��ȡ������ջ��Ԫ��

    while (optr_top != '=' || ch != '=') {
        if (isdigit(ch) || ch == '.') {
            ungetc(ch, stdin); // ����ȡ���ַ��Ż�������
            scanf("%lf", &operand); // �������ж�ȡ������
            Push(opnd, operand); // ��������ѹ�������ջ
            prior_char = '0'; // ����prior_charΪ'0'
            GetChar(&ch); // �����������л�ȡ�ַ�
        } else if (!IsOperator(ch)) {
            printf("���ʽ�г��ַǷ��ַ�!\n");
            while (scanf("%c", &ch), ch != '='); // ��������Ƿ��ַ�����������ֱ������'='
            return;
        } else {
            if ((prior_char == '=' || prior_char == '(') && (ch == '+' || ch == '-')) {
                Push(opnd, 0); // ��ǰһ���ַ���'='��'('�ҵ�ǰ�ַ���'+'��'-'ʱ����0��Ϊ������ѹ�������ջ
            }
            if (Isp(optr_top) < Icp(ch)) {
                Push(optr, ch); // ���ջ�������������ȼ����ڵ�ǰ������������ǰ������ѹ�������ջ
                prior_char = ch; // ����prior_charΪ��ǰ������
                GetChar(&ch); // �����������л�ȡ�ַ�
            } else if (Isp(optr_top) > Icp(ch)) {
                op = GetTop(optr); // ��ȡ������ջ��Ԫ��
                Pop(optr); // ����������ջ��Ԫ��
                if (!DoOperator(opnd, op)) { // ִ�в��������������ʧ���򷵻�
                    return;
                }
            } else if (Isp(optr_top) == Icp(ch) && ch == ')') {
                Pop(optr); // ����������ջ��Ԫ��
                prior_char = ')'; // ����prior_charΪ')'
                GetChar(&ch); // �����������л�ȡ�ַ�
            }
        }
        optr_top = GetTop(optr); // ���²�����ջ��Ԫ��
    }

    if (IsEmpty(opnd) || Pop(optr) == 0) {
        printf("���ʽ�д�!\n");
        return;
    } else {
        double result = GetTop(opnd); // ��ȡ������ջ��Ԫ����Ϊ���
        Pop(opnd); // ����������ջ��Ԫ��
        if (!IsEmpty(opnd) || !IsEmpty(optr)) {
            printf("���ʽ�д�!\n");
            return;
        }
        printf("%lf\n", result); // ���������
        return;
    }
}

int main() {
    Stack opnd, optr;
    opnd.top = -1;
    optr.top = -1;
    char is_continue = 'Y';

    while (is_continue == 'Y') {
        printf("�ɽ���+-*/^%%�Լ������ŵı��ʽ���㣬������ʽ(�ԵȺš�=������):\n");
        printf("ע��������Ӣ�ĵ����ţ�\n");
        Run(&opnd, &optr);
        printf("�Ƿ����(Y/N)?");
        scanf(" %c", &is_continue);
        is_continue = toupper(is_continue);
    }

    return 0;
}