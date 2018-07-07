#include <cstdio>
#include <cstdlib>

void fizzbuzz()
{
    for (int i = 1; i <= 100; ++i)
    {
        if (i % 3 == 0)
        {
            printf("Fizz");
        }

        if (i % 5 == 0)
        {
            printf("Buzz");
        }

        if (i % 3 != 0 && i % 5 != 0)
        {
            printf("%d", i);
        }

        printf("\n");
    }
}

char* reverse(char* source)
{
    char* end = source;
    while (*end) ++end;

    int length = end - source;
    char* buffer = (char*)malloc(length + 1);
    buffer[length] = 0;

    --end;
    for (int i = 0; i < length; ++i)
    {
        buffer[i] = *end;
        --end;
    }

    return buffer;
}

int main()
{
    // fizzbuzz();

    char* reversed = reverse("Hello World!");
    printf("%s\n", reversed);
}
