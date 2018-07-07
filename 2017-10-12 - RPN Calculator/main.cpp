#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Stack
{
    int count;
    int capacity;
    double* memory;

    void Init(int size)
    {
        capacity = size;
        memory = new double[capacity];
    }

    void Push(int value)
    {
        if (count < capacity)
        {
            memory[count++] = value;
        }
    }

    int Pop()
    {
        if (count > 0)
        {
            --count;
            return memory[count];
        }
    }
};

bool isDigit(char v)
{
    return v >= '0' && v <= '9';
}

int main()
{
    Stack stack = {};
    stack.Init(200);

    double tempValue = 0;
    string name;
    bool isRunning = true;
    while (isRunning)
    {
        getline(cin, name);
        istringstream sin(name);

        while (!sin.eof())
        {
            sin >> ws;

            char current = sin.peek();
            if (isDigit(current))
            {
                sin >> tempValue;
                sin >> ws;
                stack.Push(tempValue);
            }
            else
            {
                sin >> current;
                sin >> ws;
                if (current == 'q')
                {
                    isRunning = false;
                    break;
                }
    
                double y = stack.Pop();
                double x = stack.Pop();
    
                switch (current)
                {
                    case '+':
                        stack.Push(x + y);
                        break;
                        
                    case '-':
                        stack.Push(x - y);
                        break;
                    
                    case '*':
                        stack.Push(x * y);
                        break;
                    
                    case '/':
                        stack.Push(x / y);
                        break;
                    
                    default:
                        cout << "Unknown operator " << current << endl;
                        return 0;
                }
            }
        }

        if (isRunning)
        {
            cout << stack.Pop() << endl;
            if (stack.count > 0)
            {
                cout << "Woah buddy, too much number!" << endl;
            }
        }
    }
}
