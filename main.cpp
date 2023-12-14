#include <stdio.h>
#include <ctype.h>
#include <math.h>

/**
 * @brief 栈的数据结构
 */
#define MAX_SIZE 100

typedef struct Stack {
    double items[MAX_SIZE]; // 存储栈元素的数组
    int top; // 栈顶指针
} Stack;

/**
 * @brief 将元素压入栈顶
 * 
 * @param ps 指向栈的指针
 * @param x 待压入的元素
 */
void Push(Stack *ps, double x) {
    if (ps->top == MAX_SIZE - 1) {
        printf("Stack overflow"); // 如果栈满，打印错误信息
        return;
    } else {
        ps->top++; // 栈顶指针加一
        ps->items[ps->top] = x; // 将元素压入栈顶
    }
}

/**
 * @brief 弹出栈顶元素
 * 
 * @param ps 指向栈的指针
 * @return 弹出的栈顶元素
 */
double Pop(Stack *ps) {
    double temp;
    if (ps->top == -1) {
        printf("Stack underflow"); // 如果栈空，打印错误信息
        return 0;
    } else {
        temp = ps->items[ps->top]; // 保存栈顶元素
        ps->top--; // 栈顶指针减一
        return temp; // 返回栈顶元素
    }
}

/**
 * @brief 判断栈是否为空
 * 
 * @param ps 指向栈的指针
 * @return 如果栈为空返回true，否则返回false
 */
bool IsEmpty(Stack *ps) {
    return ps->top == -1; // 判断栈是否为空
}

/**
 * @brief 获取栈顶元素
 * 
 * @param ps 指向栈的指针
 * @return 栈顶元素
 */
double GetTop(Stack *ps) {
    if (ps->top == -1) {
        printf("Stack underflow"); // 如果栈空，打印错误信息
        return 0;
    } else {
        return ps->items[ps->top]; // 返回栈顶元素
    }
}

/**
 * @brief 清空栈
 * 
 * @param ps 指向栈的指针
 */
void Clear(Stack *ps) {
    ps->top = -1; // 将栈顶指针置为-1
}

int Isp(char op) {
    // 根据运算符返回其在栈内的优先级
    switch (op) {
        case '=':
            // 等号的优先级最低，为0
            return 0;
        case '(':
            // 左括号的优先级为1
            return 1;
        case '^':
            // 幂运算的优先级最高，为7
            return 7;
        case '*':
        case '/':
        case '%':
            // 乘法、除法和取余的优先级为5
            return 5;
        case '+':
        case '-':
            // 加法和减法的优先级为3
            return 3;
        case ')':
            // 右括号的优先级为8
            return 8;
        default:
            // 如果输入的不是上述运算符，返回-1
            return -1;
    }
}
/**
 *  @brief 根据运算符返回其在栈外的优先级
 * @param op
 */
int Icp(char op) {
    // 根据运算符返回其在栈外的优先级
    switch (op) {
        case '=':
            // 等号的优先级最低，为0
            return 0;
        case '(':
            // 左括号的优先级最高，为8
            return 8;
        case '^':
            // 幂运算的优先级为6
            return 6;
        case '*':
        case '/':
        case '%':
            // 乘法、除法和取余的优先级为4
            return 4;
        case '+':
        case '-':
            // 加法和减法的优先级为2
            return 2;
        case ')':
            // 右括号的优先级为1
            return 1;
        default:
            // 如果输入的不是上述运算符，返回-1
            return -1;
    }
}
/**
 *  @brief 判断字符是否为运算符
 * @param ch
 */
bool IsOperator(char ch) {
    // 判断字符是否为运算符
    return ch == '=' || ch == '(' || ch == '^' || ch == '*' || ch == '/' || ch == '%' || ch == '+' || ch == '-' || ch == ')';
}
/**
 *  @brief 从输入中获取一个字符
 * @param ch
 */
void GetChar(char *ch) {
    // 从输入中获取一个字符
    scanf(" %c", ch);
}

/**
 * @brief 从操作数栈中获取两个操作数
 *
 * 如果操作数栈为空或者只有一个元素，那么函数会打印错误信息并返回false。
 * 如果成功获取了两个操作数，那么函数会返回true。
 *
 * @param opnd 操作数栈的指针
 * @param x 用于存储从栈中获取的第一个操作数
 * @param y 用于存储从栈中获取的第二个操作数
 * @return 如果成功获取了两个操作数，返回true，否则返回false
 */
bool GetTwoOperands(Stack *opnd, double *x, double *y) {
    // 检查操作数栈是否为空
    if (IsEmpty(opnd)) {
        printf("表达式有错!\n");
        return false;
    }
    // 从栈中获取第二个操作数
    *y = GetTop(opnd);
    Pop(opnd);

    // 再次检查操作数栈是否为空
    if (IsEmpty(opnd)) {
        printf("表达式有错!\n");
        return false;
    }
    // 从栈中获取第一个操作数
    *x = GetTop(opnd);
    Pop(opnd);

    return true;
}

/**
 * @brief 执行操作符操作
 *
 * 根据传入的操作符，从操作数栈中获取两个操作数并执行相应的操作。
 *
 * @param opnd 操作数栈的指针
 * @param op 操作符
 * @return 如果成功执行操作，返回true，否则返回false
 */
bool DoOperator(Stack *opnd, char op) {
    double x, y;
    bool result = GetTwoOperands(opnd, &x, &y);
    if (result) {
        switch (op) {
            case '+':
                Push(opnd, x + y); // 执行加法操作
                break;
            case '-':
                Push(opnd, x - y); // 执行减法操作
                break;
            case '*':
                Push(opnd, x * y); // 执行乘法操作
                break;
            case '/':
                if (y == 0) {
                    printf("除数为零!\n");
                    return false; // 如果除数为零，打印错误信息并返回false
                }
                Push(opnd, x / y); // 执行除法操作
                break;
            case '%':
                if ((long) y == 0) {
                    printf("除数为零!\n");
                    return false; // 如果除数为零，打印错误信息并返回false
                }
                Push(opnd, (long) x % (long) y); // 执行取模操作
                break;
            case '^':
                Push(opnd, pow(x, y)); // 执行幂运算操作
                break;
        }
        return true; // 返回true表示成功执行操作
    } else {
        return false; // 返回false表示获取操作数失败
    }
}

/**
 * @brief 运行计算器
 *
 * 从输入中读取表达式，并根据操作符的优先级进行计算，最终输出结果。
 *
 * @param opnd 操作数栈的指针
 * @param optr 操作符栈的指针
 */
void Run(Stack *opnd, Stack *optr) {
    Clear(opnd); // 清空操作数栈
    Clear(optr); // 清空操作符栈
    char ch, optr_top, prior_char, op;
    double operand;
    Push(optr, '='); // 将'='压入操作符栈作为起始符号
    prior_char = '='; // 初始化prior_char为'='
    GetChar(&ch); // 从输入中获取字符
    optr_top = GetTop(optr); // 获取操作符栈顶元素

    while (optr_top != '=' || ch != '=') {
        if (isdigit(ch) || ch == '.') {
            ungetc(ch, stdin); // 将读取的字符放回输入流
            scanf("%lf", &operand); // 从输入中读取操作数
            Push(opnd, operand); // 将操作数压入操作数栈
            prior_char = '0'; // 更新prior_char为'0'
            GetChar(&ch); // 继续从输入中获取字符
        } else if (!IsOperator(ch)) {
            printf("表达式中出现非法字符!\n");
            while (scanf("%c", &ch), ch != '='); // 如果遇到非法字符，跳过输入直到遇到'='
            return;
        } else {
            if ((prior_char == '=' || prior_char == '(') && (ch == '+' || ch == '-')) {
                Push(opnd, 0); // 在前一个字符是'='或'('且当前字符是'+'或'-'时，将0作为操作数压入操作数栈
            }
            if (Isp(optr_top) < Icp(ch)) {
                Push(optr, ch); // 如果栈顶操作符的优先级低于当前操作符，将当前操作符压入操作符栈
                prior_char = ch; // 更新prior_char为当前操作符
                GetChar(&ch); // 继续从输入中获取字符
            } else if (Isp(optr_top) > Icp(ch)) {
                op = GetTop(optr); // 获取操作符栈顶元素
                Pop(optr); // 弹出操作符栈顶元素
                if (!DoOperator(opnd, op)) { // 执行操作符操作，如果失败则返回
                    return;
                }
            } else if (Isp(optr_top) == Icp(ch) && ch == ')') {
                Pop(optr); // 弹出操作符栈顶元素
                prior_char = ')'; // 更新prior_char为')'
                GetChar(&ch); // 继续从输入中获取字符
            }
        }
        optr_top = GetTop(optr); // 更新操作符栈顶元素
    }

    if (IsEmpty(opnd) || Pop(optr) == 0) {
        printf("表达式有错!\n");
        return;
    } else {
        double result = GetTop(opnd); // 获取操作数栈顶元素作为结果
        Pop(opnd); // 弹出操作数栈顶元素
        if (!IsEmpty(opnd) || !IsEmpty(optr)) {
            printf("表达式有错!\n");
            return;
        }
        printf("%lf\n", result); // 输出计算结果
        return;
    }
}

int main() {
    Stack opnd, optr;
    opnd.top = -1;
    optr.top = -1;
    char is_continue = 'Y';

    while (is_continue == 'Y') {
        printf("可进行+-*/^%%以及带括号的表达式运算，输入表达式(以等号“=”结束):\n");
        printf("注意请输入英文的括号！\n");
        Run(&opnd, &optr);
        printf("是否继续(Y/N)?");
        scanf(" %c", &is_continue);
        is_continue = toupper(is_continue);
    }

    return 0;
}