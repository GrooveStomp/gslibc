#include "gs.h"
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <stdio.h>
#include <alloca.h>
#include <stdarg.h>

#define Assert(Expression, ...) AssertFn(__LINE__, __func__, (Expression), __VA_ARGS__)

void
AssertFn(int LineNumber, const char *FuncName, int Expression, char *FormatString, ...)
{
        if(!Expression)
        {
                va_list Arg;
                va_start(Arg, FormatString);

                char Suffix[512];
                snprintf(Suffix, 512, FormatString, Arg);
                fprintf(stderr, "Assertion failed in %s() at line #%d: %s\n", FuncName, LineNumber, Suffix);

                exit(EXIT_FAILURE);
        }
}

/******************************************************************************
 * Boolean interface
 ******************************************************************************/

void
TestFalse()
{
        Assert(false != true, "False is not True");
        Assert(false == false, "False is False");
        Assert(false == 0, "False is Zero");
}

void
TestTrue()
{
        Assert(true != false, "True is not False");
        Assert(true == true, "True is True");
        Assert(true != 0, "True is not Zero");
}

/******************************************************************************
 * Char interface
 ******************************************************************************/

void
TestIsCharEndOfStream()
{
        Assert(gs_IsCharEndOfStream('\0'), "%c is end of stream", '\0');
        Assert(!gs_IsCharEndOfStream('1'), "%c is not end of stream", '1');
}

void
TestIsCharEndOfLine()
{
        char *IsEndOfLine = "\n\r";
        char *NotEndOfLine = "1nrt\t";

        for(int i = 0; i < gs_StringLength(IsEndOfLine); i++)
        {
                Assert(gs_IsCharEndOfLine(IsEndOfLine[i]), "%c is end of line", IsEndOfLine[i]);
        }

        for(int i = 0; i < gs_StringLength(NotEndOfLine); i++)
        {
                Assert(!gs_IsCharEndOfLine(NotEndOfLine[i]), "%c is not end of line", NotEndOfLine[i]);
        }
        Assert(!gs_IsCharEndOfLine('\0'), "'\0' is not end of line");
}

void
TestIsCharWhitespace()
{
        char *IsWhitespace = " \t\v\f\n\r";
        char *NotWhitespace = "1ntvfnr0";

        for(int i = 0; i < gs_StringLength(IsWhitespace); i++)
        {
                Assert(gs_IsCharWhitespace(IsWhitespace[i]), "%c is whitespace", IsWhitespace[i]);
        }

        for(int i = 0; i < gs_StringLength(NotWhitespace); i++)
        {
                Assert(!gs_IsCharWhitespace(NotWhitespace[i]), "%c is not whitespace", NotWhitespace[i]);
        }
        Assert(!gs_IsCharWhitespace('\0'), "'\0' is not whitespace");
}

void
TestIsCharOctal()
{
        char *IsOctal = "01234567";
        char *NotOctal = "aF89\r\n\t ";

        for(int i = 0; i < gs_StringLength(IsOctal); i++)
        {
                Assert(gs_IsCharOctal(IsOctal[i]), "%c is octal", IsOctal[i]);
        }

        for(int i = 0; i < gs_StringLength(NotOctal); i++)
        {
                Assert(!gs_IsCharOctal(NotOctal[i]), "%c is not octal", NotOctal[i]);
        }
        Assert(!gs_IsCharOctal('\0'), "'\0' is not octal");
}

void
TestIsCharDecimal()
{
        char *IsDecimal = "0123456789";
        char *NotDecimal = "aAfF\r\n\t ";

        for(int i = 0; i < gs_StringLength(IsDecimal); i++)
        {
                Assert(gs_IsCharDecimal(IsDecimal[i]), "%c is decimal", IsDecimal[i]);
        }

        for(int i = 0; i < gs_StringLength(NotDecimal); i++)
        {
                Assert(!gs_IsCharDecimal(NotDecimal[i]), "%c is not decimal", NotDecimal[i]);
        }
        Assert(!gs_IsCharDecimal('\0'), "'\0' is not decimal");
}

void
TestIsCharHexadecimal()
{
        char *IsHexadecimal = "0123456789abcdefABCDEF";
        char *NotHexadecimal = "gGhH\r\n\t xX";

        for(int i = 0; i < gs_StringLength(IsHexadecimal); i++)
        {
                Assert(gs_IsCharHexadecimal(IsHexadecimal[i]), "%c is hexadecimal", IsHexadecimal[i]);
        }

        for(int i = 0; i < gs_StringLength(NotHexadecimal); i++)
        {
                Assert(!gs_IsCharHexadecimal(NotHexadecimal[i]), "%c is not hexadecimal", NotHexadecimal[i]);
        }
        Assert(!gs_IsCharHexadecimal('\0'), "'\0' is not hexadecimal");
}

void
TestIsCharAlphabetical()
{
        char *IsAlphabetical = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char *NotAlphabetical = "01234567890\r\n\t ";

        for(int i = 0; i < gs_StringLength(IsAlphabetical); i++)
        {
                Assert(gs_IsCharAlphabetical(IsAlphabetical[i]), "%c is alphabetical", IsAlphabetical[i]);
        }

        for(int i = 0; i < gs_StringLength(NotAlphabetical); i++)
        {
                Assert(!gs_IsCharAlphabetical(NotAlphabetical[i]), "%c is not alphabetical", NotAlphabetical[i]);
        }
        Assert(!gs_IsCharAlphabetical('\0'), "'\0' is not alphabetical");
}

/******************************************************************************
 * String interface
 ******************************************************************************/

void
TestIsStringEqual()
{
        Assert(gs_IsStringEqual("Hello", "Hello", gs_StringLength("Hello")), "%s is equal to %s", "Hello", "Hello");
        Assert(gs_IsStringEqual("Hello", "Hello there", gs_StringLength("Hello")), "%s is equal to %s", "Hello", "Hello there");
        Assert(!gs_IsStringEqual("Hello", "Hel", gs_StringLength("Hello")), "%s is not equal to %s", "Hello", "Hel");
}

void
TestStringLength()
{
        Assert(gs_StringLength("Hello") == 5, "gs_StringLength(\"Hello\") == 5");
        Assert(gs_StringLength("") == 0, "gs_StringLength(\"\") == 0");
}

void
TestStringCopyWithNull()
{
        char Buffer[256];
        memset(Buffer, 1, 256);

        gs_StringCopyWithNull("hello", Buffer);
        Assert(gs_IsStringEqual("hello", Buffer, gs_StringLength(Buffer)), "hello == %s", Buffer);
}

/******************************************************************************
 * Hash Map interface
 ******************************************************************************/

void
TestHashMapSpaceRequired()
{
        int Size;
        int Expected;

        Size = gs_HashMapSpaceRequired(1);
        Expected = sizeof(int) + sizeof(void *) + sizeof(gs_hash_map);
        Assert(Size == Expected, "Size of HashMap with 1 key == %d", Expected);

        Size = gs_HashMapSpaceRequired(50);
        Expected = sizeof(int) * 50 + sizeof(void *) * 50 + sizeof(gs_hash_map);
        Assert(Size == Expected, "Size of HashMap with 50 keys == %d", Expected);
}

void
TestHashMapCreate()
{
        gs_hash_map *Map;
        Map = gs_HashMapCreate(-1, NULL);
        Assert(Map->Count == 0, "HashMap count is initialized");
        Assert(Map->Size == gs_HashMapInitialSize, "HashMap size is initialized");
        free(Map); /* gs_HashMapCreate internally calls `malloc' if second parameter is NULL */

        int Size = gs_HashMapSpaceRequired(20);
        void *Buffer = alloca(Size);
        Map = gs_HashMapCreate(20, Buffer);
        Assert(Map->Count == 0, "HashMap count is initialized");
        Assert(Map->Size == 20, "HashMap size is initialized");
}

void
TestHashMap()
{
        int NumElements = 20;
        void *Buffer = alloca(gs_HashMapSpaceRequired(NumElements));
        gs_hash_map *Map = gs_HashMapCreate(NumElements, Buffer);

        char *Keys[] = { "Key1", "Key2", "Key3" };
        char *Values[] = { "Value1", "Value2", "Value3" };
        for(int i = 0; i < ArraySize(Keys); i++)
        {
                gs_HashMapAdd(Map, Keys[i], (void *)Values[i]);
        }

        for(int i = 0; i < ArraySize(Keys); i++)
        {
                char *Value;
                gs_bool Found = gs_HashMapGet(Map, Keys[i], (void *)&Value);
                Assert(Found == true, "Key(%s) is found", Keys[i]);
                Assert(gs_IsStringEqual(Value, Values[i], gs_StringLength(Values[i])), "Value(%s) is found", Value);
        }
}

int
main(int ArgCount, char **Args)
{
        /* Boolean */
        TestFalse();
        TestTrue();
        /* Char */
        TestIsCharEndOfStream();
        TestIsCharEndOfLine();
        TestIsCharWhitespace();
        TestIsCharOctal();
        TestIsCharDecimal();
        TestIsCharHexadecimal();
        TestIsCharAlphabetical();
        /* String */
        TestIsStringEqual();
        TestStringLength();
        TestStringCopyWithNull();
        /* Hash Map */
        TestHashMapSpaceRequired();
        TestHashMapCreate();
        TestHashMap();

        printf("All tests passed\n");
        return(EXIT_SUCCESS);
}
