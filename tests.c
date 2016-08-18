/******************************************************************************
 * File: tests.c
 * Created: 2016-07-14
 * Last Updated: 2016-08-18
 * Creator: Aaron Oman (a.k.a GrooveStomp)
 * Notice: (C) Copyright 2016 by Aaron Oman
 ******************************************************************************/
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
 * Miscellaneous Macros
 *****************************************************************************/
void
TestAbortWithMessage()
{
        /* TODO(AARON): Not sure how to actually test this! */
}

void
TestArraySize()
{
        int Numbers[] = { 1, 2, 3, 4, 5 };
        int Size = GSArraySize(Numbers);
        Assert(Size == 5, "Number of elements in `Numbers' is 5");
}

void
TestArrayForEach()
{
        int Numbers[] = { 1, 2, 3, 4, 5 };
        int AssertionIndex = 0;
        GSArrayForEach(int *Number, Numbers)
        {
                Assert(Index == AssertionIndex, "Index is set to %i", AssertionIndex);
                Assert(*Number == Numbers[Index], "Numbers is index properly");
                AssertionIndex++;
        }
}

void
TestMax()
{
        int Result;

        Result = GSMax(1, 2);
        Assert(Result == 2, "Max chooses the larger value");
        Result = GSMax(2, 1);
        Assert(Result == 2, "Max chooses the larger value");
}

void
TestMin()
{
        int Result;

        Result = GSMin(1, 2);
        Assert(Result == 1, "Max chooses the smaller value");
        Result = GSMin(2, 1);
        Assert(Result == 1, "Max chooses the smaller value");
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
TestCharIsEndOfStream()
{
        Assert(GSCharIsEndOfStream('\0'), "%c is end of stream", '\0');
        Assert(!GSCharIsEndOfStream('1'), "%c is not end of stream", '1');
}

void
TestCharIsEndOfLine()
{
        char *IsEndOfLine = "\n\r";
        char *NotEndOfLine = "1nrt\t";

        for(int i = 0; i < GSStringLength(IsEndOfLine); i++)
        {
                Assert(GSCharIsEndOfLine(IsEndOfLine[i]), "%c is end of line", IsEndOfLine[i]);
        }

        for(int i = 0; i < GSStringLength(NotEndOfLine); i++)
        {
                Assert(!GSCharIsEndOfLine(NotEndOfLine[i]), "%c is not end of line", NotEndOfLine[i]);
        }
        Assert(!GSCharIsEndOfLine('\0'), "'\0' is not end of line");
}

void
TestCharIsWhitespace()
{
        char *IsWhitespace = " \t\v\f\n\r";
        char *NotWhitespace = "1ntvfnr0";

        for(int i = 0; i < GSStringLength(IsWhitespace); i++)
        {
                Assert(GSCharIsWhitespace(IsWhitespace[i]), "%c is whitespace", IsWhitespace[i]);
        }

        for(int i = 0; i < GSStringLength(NotWhitespace); i++)
        {
                Assert(!GSCharIsWhitespace(NotWhitespace[i]), "%c is not whitespace", NotWhitespace[i]);
        }
        Assert(!GSCharIsWhitespace('\0'), "'\0' is not whitespace");
}

void
TestCharIsOctal()
{
        char *IsOctal = "01234567";
        char *NotOctal = "aF89\r\n\t ";

        for(int i = 0; i < GSStringLength(IsOctal); i++)
        {
                Assert(GSCharIsOctal(IsOctal[i]), "%c is octal", IsOctal[i]);
        }

        for(int i = 0; i < GSStringLength(NotOctal); i++)
        {
                Assert(!GSCharIsOctal(NotOctal[i]), "%c is not octal", NotOctal[i]);
        }
        Assert(!GSCharIsOctal('\0'), "'\0' is not octal");
}

void
TestCharIsDecimal()
{
        char *IsDecimal = "0123456789";
        char *NotDecimal = "aAfF\r\n\t ";

        for(int i = 0; i < GSStringLength(IsDecimal); i++)
        {
                Assert(GSCharIsDecimal(IsDecimal[i]), "%c is decimal", IsDecimal[i]);
        }

        for(int i = 0; i < GSStringLength(NotDecimal); i++)
        {
                Assert(!GSCharIsDecimal(NotDecimal[i]), "%c is not decimal", NotDecimal[i]);
        }
        Assert(!GSCharIsDecimal('\0'), "'\0' is not decimal");
}

void
TestCharIsHexadecimal()
{
        char *IsHexadecimal = "0123456789abcdefABCDEF";
        char *NotHexadecimal = "gGhH\r\n\t xX";

        for(int i = 0; i < GSStringLength(IsHexadecimal); i++)
        {
                Assert(GSCharIsHexadecimal(IsHexadecimal[i]), "%c is hexadecimal", IsHexadecimal[i]);
        }

        for(int i = 0; i < GSStringLength(NotHexadecimal); i++)
        {
                Assert(!GSCharIsHexadecimal(NotHexadecimal[i]), "%c is not hexadecimal", NotHexadecimal[i]);
        }
        Assert(!GSCharIsHexadecimal('\0'), "'\0' is not hexadecimal");
}

void
TestCharIsAlphabetical()
{
        char *IsAlphabetical = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char *NotAlphabetical = "01234567890\r\n\t ";

        for(int i = 0; i < GSStringLength(IsAlphabetical); i++)
        {
                Assert(GSCharIsAlphabetical(IsAlphabetical[i]), "%c is alphabetical", IsAlphabetical[i]);
        }

        for(int i = 0; i < GSStringLength(NotAlphabetical); i++)
        {
                Assert(!GSCharIsAlphabetical(NotAlphabetical[i]), "%c is not alphabetical", NotAlphabetical[i]);
        }
        Assert(!GSCharIsAlphabetical('\0'), "'\0' is not alphabetical");
}

void
TestCharIsAlphanumeric()
{
        char *IsAlphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";
        char *NotAlphanumeric = "-_\r\n\t ";

        for(int i = 0; i < GSStringLength(IsAlphanumeric); i++)
        {
                Assert(GSCharIsAlphanumeric(IsAlphanumeric[i]), "%c is alphanumeric", IsAlphanumeric[i]);
        }

        for(int i = 0; i < GSStringLength(NotAlphanumeric); i++)
        {
                Assert(!GSCharIsAlphanumeric(NotAlphanumeric[i]), "%c is not alphanumeric", NotAlphanumeric[i]);
        }
        Assert(!GSCharIsAlphanumeric('\0'), "'\0' is not alphanumeric");
}

/******************************************************************************
 * String interface
 ******************************************************************************/

void
TestStringIsEqual()
{
        Assert(GSStringIsEqual("Hello", "Hello", GSStringLength("Hello")), "%s is equal to %s", "Hello", "Hello");
        Assert(GSStringIsEqual("Hello", "Hello there", GSStringLength("Hello")), "%s is equal to %s", "Hello", "Hello there");
        Assert(!GSStringIsEqual("Hello", "Hel", GSStringLength("Hello")), "%s is not equal to %s", "Hello", "Hel");
}

void
TestStringLength()
{
        Assert(GSStringLength("Hello") == 5, "GSStringLength(\"Hello\") == 5");
        Assert(GSStringLength("") == 0, "GSStringLength(\"\") == 0");
}

void
TestStringCopyWithNull()
{
        char Buffer[256];
        memset(Buffer, 1, 256);

        GSStringCopyWithNull("hello", Buffer, 5);
        Assert(GSStringIsEqual("hello", Buffer, GSStringLength(Buffer)), "hello == %s", Buffer);
}

void
TestStringCopyWithoutSurroundingWhitespace()
{
        char Buffer[256];
        char *Source = "   Hello there    ";
        int StringLength = GSStringLength(Source);

        memset(Buffer, 0, 256);
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, 4);
        Assert(GSStringIsEqual("Hell", Buffer, 4), "Hell == %s", Buffer);

        memset(Buffer, 0, 256);
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, StringLength);
        Assert(GSStringIsEqual("Hello there", Buffer, GSStringLength("Hello there")), "Hello there == %s", Buffer);
}

void
TestStringCopyWithoutSurroundingWhitespaceWithNull()
{
        char Buffer[256];
        char *Source = "   Hello there    ";
        int StringLength = GSStringLength(Source);

        memset(Buffer, 1, 256); /* Set buffer to 1 so it's not NULL-terminated by default. */
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, 4);
        Assert(GSStringIsEqual("Hell", Buffer, 4), "Hell == %s", Buffer);

        memset(Buffer, 1, 256); /* Set buffer to 1 so it's not NULL-terminated by default. */
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, StringLength);
        Assert(GSStringIsEqual("Hello there", Buffer, GSStringLength("Hello there")), "Hello there == %s", Buffer);
}

/******************************************************************************
 * Hash Map interface
 ******************************************************************************/

void
TestHashMapSpaceRequired()
{
        int Size;
        int Expected;

        Size = GSHashMapSpaceRequired(1);
        Expected = sizeof(int) + sizeof(void *) + sizeof(gs_hash_map);
        Assert(Size == Expected, "Size of HashMap with 1 key == %d", Expected);

        Size = GSHashMapSpaceRequired(50);
        Expected = sizeof(int) * 50 + sizeof(void *) * 50 + sizeof(gs_hash_map);
        Assert(Size == Expected, "Size of HashMap with 50 keys == %d", Expected);
}

void
TestHashMapCreate()
{
        gs_hash_map *Map;
        Map = GSHashMapCreate(-1, NULL);
        Assert(Map->Count == 0, "HashMap count is initialized");
        Assert(Map->Size == GSHashMapInitialSize, "HashMap size is initialized");
        free(Map); /* GSHashMapCreate internally calls `malloc' if second parameter is NULL */

        int Size = GSHashMapSpaceRequired(20);
        void *Buffer = alloca(Size);
        Map = GSHashMapCreate(20, Buffer);
        Assert(Map->Count == 0, "HashMap count is initialized");
        Assert(Map->Size == 20, "HashMap size is initialized");
}

void
TestHashMap()
{
        int NumElements = 20;
        void *Buffer = alloca(GSHashMapSpaceRequired(NumElements));
        gs_hash_map *Map = GSHashMapCreate(NumElements, Buffer);

        char *Keys[] = { "Key1", "Key2", "Key3" };
        char *Values[] = { "Value1", "Value2", "Value3" };
        for(int i = 0; i < GSArraySize(Keys); i++)
        {
                GSHashMapAdd(Map, Keys[i], (void *)Values[i]);
        }

        for(int i = 0; i < GSArraySize(Keys); i++)
        {
                char *Value;
                gs_bool Found = GSHashMapGet(Map, Keys[i], (void *)&Value);
                Assert(Found == true, "Key(%s) is found", Keys[i]);
                Assert(GSStringIsEqual(Value, Values[i], GSStringLength(Values[i])), "Value(%s) is found", Value);
        }
}

/******************************************************************************
 * Argument parsing interface
 ******************************************************************************/

void
TestArgIsPresent()
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args Args;
        GSArgInit(&Args, Count, Params);

        char *Wanted = "arg1";
        gs_bool Result = GSArgIsPresent(&Args, Wanted);
        Assert(Result == true, "Arg(%s) is found", Wanted);

        Wanted = "arg3";
        Result = GSArgIsPresent(&Args, Wanted);
        Assert(Result == false, "Arg(%s) is not found", Wanted);
}

void
TestArgIndex()
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args Args;
        GSArgInit(&Args, Count, Params);

        char *Arg = "arg1";
        int Index = GSArgIndex(&Args, Arg);
        Assert(Index == 0, "Arg(%s) is at index(%i)", Arg, Index);

        Arg = "arg3";
        Index = GSArgIndex(&Args, Arg);
        Assert(Index == -1, "Arg(%s) is not found", Arg);
}

void
TestArgAtIndex()
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args Args;
        GSArgInit(&Args, Count, Params);

        int Index = 0;
        char *Arg = GSArgAtIndex(&Args, Index);
        Assert(GSStringIsEqual(Arg, "arg1", 4), "Arg(%s) is at index(%i)", Arg, Index);

        Index = -1;
        Arg = GSArgAtIndex(&Args, Index);
        Assert(Arg == NULL, "Arg(%s) is not found", Arg);

        Index = 2;
        Arg = GSArgAtIndex(&Args, Index);
        Assert(Arg == NULL, "Arg(%s) is not found", Arg);
}

void
TestArgAfter()
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args Args;
        GSArgInit(&Args, Count, Params);

        char *Arg = "arg1";
        char *After = GSArgAfter(&Args, Arg);
        Assert(GSStringIsEqual(After, "arg2", 4), "Arg(%s) follows Arg(%s)", After, Arg);

        Arg = "arg2";
        After = GSArgAfter(&Args, Arg);
        Assert(After == NULL, "No argument follows Arg(%s)", Arg);

        Arg = "What?";
        After = GSArgAfter(&Args, Arg);
        Assert(After == NULL, "No argument follows Arg(%s)", Arg);
}

void
TestArgHelpWanted()
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "-h";
        Params[1] = "arg2";

        gs_args Args;
        GSArgInit(&Args, Count, Params);

        gs_bool Result = GSArgHelpWanted(&Args);
        Assert(Result == true, "-h or --help is present");

        Params[0] = "--help";
        Result = GSArgHelpWanted(&Args);
        Assert(Result == true, "-h or --help is present");

        Params[0] = "arg1";
        Result = GSArgHelpWanted(&Args);
        Assert(Result == false, "-h or --help is not present");
}

/******************************************************************************
 * Byte Streams and Buffers
 ******************************************************************************/

void
TestBufferInit()
{
        gs_buffer Buffer;
        char Memory[25];
        GSBufferInit(&Buffer, Memory, 25);
        Assert(Buffer.Start == Memory, "Buffer starts at Memory");
        Assert(Buffer.Cursor == Memory, "Buffer Cursor is at Start");
        Assert(Buffer.Length == 0, "Buffer has zero length");
        Assert(Buffer.Capacity == 25, "Buffer has proper Capacity");
}

void
TestBufferIsEOF()
{
        gs_bool IsEOF;
        gs_buffer Buffer;
        char Memory[25];
        GSBufferInit(&Buffer, Memory, 25);

        Buffer.Length = 1;
        IsEOF = GSBufferIsEOF(&Buffer);
        Assert(IsEOF == false, "Buffer is not EOF");

        Buffer.Cursor++;
        IsEOF = GSBufferIsEOF(&Buffer);
        Assert(IsEOF == true, "Buffer is EOF");
}

void
TestBufferNextLine()
{
        gs_buffer Buffer;
        char *Text = "This\nIs\nSome\nText\n";
        GSBufferInit(&Buffer, Text, GSStringLength(Text));

        Assert(GSStringIsEqual(Text, Buffer.Start, GSStringLength(Text)), "Buffer is unmodified");

        GSBufferNextLine(&Buffer);
        Assert(GSStringIsEqual("Is\nSome\nText\n", Buffer.Cursor, GSStringLength("Is\nSome\nText\n")), "Buffer is advanced to next line");
}

void
TestBufferSaveCursor()
{
        gs_buffer Buffer;
        char *Text = "This\nIs\nSome\nText\n";
        GSBufferInit(&Buffer, Text, GSStringLength(Text));
        GSBufferSaveCursor(&Buffer);
        GSBufferNextLine(&Buffer);
        Assert(GSStringIsEqual(Text, Buffer.SavedCursor, GSStringLength(Text)), "SavedCursor is original text.");
}

void
TestBufferRestoreCursor()
{
        gs_buffer Buffer;
        char *Text = "This\nIs\nSome\nText\n";
        GSBufferInit(&Buffer, Text, GSStringLength(Text));
        GSBufferSaveCursor(&Buffer);
        GSBufferNextLine(&Buffer);
        GSBufferRestoreCursor(&Buffer);
        Assert(GSStringIsEqual(Text, Buffer.Cursor, GSStringLength(Text)), "Cursor is restored.");
}

void
TestFileSize()
{
        FILE *File = fopen("temp.txt", "w");
        fwrite("Test\n", 1, 5, File);
        fclose(File);

        int FileSize = GSFileSize("temp.txt");
        Assert(FileSize == 5, "Size of file (%i) is 5", FileSize);
        remove("temp.txt");
}

void
TestFileCopyToBuffer()
{
        FILE *File = fopen("temp.txt", "w");
        fwrite("Test\n", 1, 5, File);
        fclose(File);

        int FileSize = GSFileSize("temp.txt");
        gs_buffer Buffer;
        GSBufferInit(&Buffer, (char *)alloca(FileSize), FileSize);
        GSFileCopyToBuffer("temp.txt", &Buffer);
        remove("temp.txt");

        Assert(Buffer.Length == FileSize, "Entire file contents were copied.");
        Assert(GSBufferIsEOF(&Buffer), "Buffer cursor is at end of file in memory.");
        Assert(GSStringIsEqual(Buffer.Start, "Test\n", FileSize), "File text was copied correctly.");
}

int
main(int ArgCount, char **Args)
{
        /* Miscellaneous Macros */
        TestAbortWithMessage();
        TestArraySize();
        TestArrayForEach();
        TestMax();
        TestMin();
        /* Boolean */
        TestFalse();
        TestTrue();
        /* Char */
        TestCharIsEndOfStream();
        TestCharIsEndOfLine();
        TestCharIsWhitespace();
        TestCharIsOctal();
        TestCharIsDecimal();
        TestCharIsHexadecimal();
        TestCharIsAlphabetical();
        /* String */
        TestStringIsEqual();
        TestStringLength();
        TestStringCopyWithNull();
        TestStringCopyWithoutSurroundingWhitespace();
        TestStringCopyWithoutSurroundingWhitespaceWithNull();
        /* Hash Map */
        TestHashMapSpaceRequired();
        TestHashMapCreate();
        TestHashMap();
        /* Arg Parsing */
        TestArgIsPresent();
        TestArgIndex();
        TestArgAtIndex();
        TestArgAfter();
        TestArgHelpWanted();
        /* Byte Streams and Buffers */
        TestBufferInit();
        TestBufferIsEOF();
        TestBufferNextLine();
        TestBufferSaveCursor();
        TestBufferRestoreCursor();
        TestFileSize();
        TestFileCopyToBuffer();

        printf("All tests passed\n");
        return(EXIT_SUCCESS);
}
