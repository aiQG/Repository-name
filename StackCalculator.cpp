#include <iostream>
#include <stack>
using namespace std;

int main()
{
    string input = "";
    cin >> input;
    input = "(" + input + ")";
    /*
    合法性check
    */

    stack<int> numberStacks[100];
    int nNum = 0;
    stack<char> symbolStacks[100];
    int nSym = 0;
    int number = 0;

    stack<int> tempNumStack;
    stack<char> tempSymStack;

    bool isNumber = false;
    int A = 0;
    int B = 0;
    for (int i = 0; i < input.length(); i++)
    {
        switch (input[i])
        {
        case '+':
        case '-':
        case '*':
        case '/':
            if (isNumber)
            {

                numberStacks[nNum].push(number);
            }
            // cout << number << endl;
            // cout << "A" << nNum << endl;
            number = 0;
            symbolStacks[nSym].push(input[i]);
            isNumber = false;
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            number = number * 10 + input[i] - 0x30;
            isNumber = true;
            break;

        case '(':
            nSym++;
            nNum++;
            isNumber = false;
            break;

        case ')':
            if (isNumber)
            {
                numberStacks[nNum].push(number);
                number = 0;
            }
            tempNumStack.push(numberStacks[nNum].top());
            numberStacks[nNum].pop();
            while (symbolStacks[nSym].size() != 0)
            {
                switch (symbolStacks[nSym].top())
                {
                case '-':
                case '+':
                    tempSymStack.push(symbolStacks[nSym].top());
                    symbolStacks[nSym].pop();
                    tempNumStack.push(numberStacks[nNum].top());
                    numberStacks[nNum].pop();
                    break;
                case '*':
                    A = numberStacks[nNum].top();
                    numberStacks[nNum].pop();
                    B = tempNumStack.top();
                    tempNumStack.pop();
                    tempNumStack.push(A * B);
                    symbolStacks[nSym].pop();
                    break;
                case '/':
                    A = numberStacks[nNum].top();
                    numberStacks[nNum].pop();
                    B = tempNumStack.top();
                    tempNumStack.pop();
                    tempNumStack.push(A / B);
                    symbolStacks[nSym].pop();
                    break;
                }
            }
            while (tempSymStack.size() != 0)
            {
                switch (tempSymStack.top())
                {
                case '+':
                    A = tempNumStack.top();
                    tempNumStack.pop();
                    B = tempNumStack.top();
                    tempNumStack.pop();
                    tempNumStack.push(A + B);
                    tempSymStack.pop();
                    break;
                case '-':
                    A = tempNumStack.top();
                    tempNumStack.pop();
                    B = tempNumStack.top();
                    tempNumStack.pop();
                    tempNumStack.push(A - B);
                    tempSymStack.pop();
                    break;
                default:
                    break;
                }
            }
            nSym--;
            nNum--;
            numberStacks[nNum].push(tempNumStack.top());
            tempNumStack.pop();
            isNumber = false;

            break;
        default:
            break;
        }
    }
    cout << numberStacks[nNum].top() << endl;
    // cout << numberStacks[nNum].size() << endl;
    return 0;
}
