/******************************************************************************
 * File: tests.c
 * Created: 2016-07-14
 * Last Updated: 2016-08-19
 * Creator: Aaron Oman (a.k.a GrooveStomp)
 * Notice: (C) Copyright 2016 by Aaron Oman
 ******************************************************************************/
#include "gs.h"
#include "gstest.h"
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <stdio.h>
#include <alloca.h>
#include <stdarg.h>

/******************************************************************************
 gstest
*******************************************************************************/
void
TestAssert()
{
        /* NOTE: Commented out because this exits on failure! */
        /* GSTestAssert(1 == 2, "Expect %i to equal %i\n", 1, 2); */
}

void
TestRandomString()
{
        char String[256];

        memset(String, 0, 256);
        for(int I=0; I<25; I++)
        {
                int Length = GSTestRandomString(String, 5, 15);
                GSTestAssert(Length >= 5, "%i >= 5\n", Length);
                GSTestAssert(Length <= 15, "%i <= 15\n", Length);
                for(int K=0; K<Length; K++)
                {
                        GSTestAssert(GSCharIsAlphabetical(String[K]), "%c is a char\n", String[K]);
                }
        }
}

/******************************************************************************
 * Miscellaneous Macros
 *****************************************************************************/
void
TestAbortWithMessage()
{
        /* NOTE: Commented out because this exits on failure! */
        /* GSAbortWithMessage("%s expected to equal %s\n", "Hello", "Not Hello"); */
}

void
TestArraySize()
{
        int Numbers[] = { 1, 2, 3, 4, 5 };
        int Size = GSArraySize(Numbers);
        GSTestAssert(Size == 5, "Number of elements in `Numbers' is 5");
}

void
TestArrayForEach()
{
        int Numbers[] = { 1, 2, 3, 4, 5 };
        int AssertionIndex = 0;
        GSArrayForEach(int *Number, Numbers)
        {
                GSTestAssert(Index == AssertionIndex, "Index is set to %i", AssertionIndex);
                GSTestAssert(*Number == Numbers[Index], "Numbers is index properly");
                AssertionIndex++;
        }
}

void
TestMax()
{
        int Result;

        Result = GSMax(1, 2);
        GSTestAssert(Result == 2, "Max chooses the larger value");
        Result = GSMax(2, 1);
        GSTestAssert(Result == 2, "Max chooses the larger value");
}

void
TestMin()
{
        int Result;

        Result = GSMin(1, 2);
        GSTestAssert(Result == 1, "Max chooses the smaller value");
        Result = GSMin(2, 1);
        GSTestAssert(Result == 1, "Max chooses the smaller value");
}

void
TestBytesToKilobytes()
{
        int Num = 1024;
        GSTestAssert(GSBytesToKilobytes(Num) == 1, "%i B == 1 KB", Num);
}

void
TestBytesToMegabytes()
{
        int Num = 1024*1024;
        GSTestAssert(GSBytesToMegabytes(Num) == 1, "%i B == 1 MB", Num);
}

void
TestBytesToGigabytes()
{
        int Num = 1024*1024*1024;
        GSTestAssert(GSBytesToGigabytes(Num) == 1, "%i B == 1 GB", Num);
}

/******************************************************************************
 * Boolean interface
 ******************************************************************************/

void
TestFalse()
{
        GSTestAssert(false != true, "False is not True");
        GSTestAssert(false == false, "False is False");
        GSTestAssert(false == 0, "False is Zero");
}

void
TestTrue()
{
        GSTestAssert(true != false, "True is not False");
        GSTestAssert(true == true, "True is True");
        GSTestAssert(true != 0, "True is not Zero");
}

/******************************************************************************
 * Char interface
 ******************************************************************************/

void
TestCharIsEndOfStream()
{
        GSTestAssert(GSCharIsEndOfStream('\0'), "%c is end of stream", '\0');
        GSTestAssert(!GSCharIsEndOfStream('1'), "%c is not end of stream", '1');
}

void
TestCharIsEndOfLine()
{
        char *IsEndOfLine = "\n\r";
        char *NotEndOfLine = "1nrt\t";

        for(int i = 0; i < GSStringLength(IsEndOfLine); i++)
        {
                GSTestAssert(GSCharIsEndOfLine(IsEndOfLine[i]), "%c is end of line", IsEndOfLine[i]);
        }

        for(int i = 0; i < GSStringLength(NotEndOfLine); i++)
        {
                GSTestAssert(!GSCharIsEndOfLine(NotEndOfLine[i]), "%c is not end of line", NotEndOfLine[i]);
        }
        GSTestAssert(!GSCharIsEndOfLine('\0'), "'\0' is not end of line");
}

void
TestCharIsWhitespace()
{
        char *IsWhitespace = " \t\v\f\n\r";
        char *NotWhitespace = "1ntvfnr0";

        for(int i = 0; i < GSStringLength(IsWhitespace); i++)
        {
                GSTestAssert(GSCharIsWhitespace(IsWhitespace[i]), "%c is whitespace", IsWhitespace[i]);
        }

        for(int i = 0; i < GSStringLength(NotWhitespace); i++)
        {
                GSTestAssert(!GSCharIsWhitespace(NotWhitespace[i]), "%c is not whitespace", NotWhitespace[i]);
        }
        GSTestAssert(!GSCharIsWhitespace('\0'), "'\0' is not whitespace");
}

void
TestCharIsOctal()
{
        char *IsOctal = "01234567";
        char *NotOctal = "aF89\r\n\t ";

        for(int i = 0; i < GSStringLength(IsOctal); i++)
        {
                GSTestAssert(GSCharIsOctal(IsOctal[i]), "%c is octal", IsOctal[i]);
        }

        for(int i = 0; i < GSStringLength(NotOctal); i++)
        {
                GSTestAssert(!GSCharIsOctal(NotOctal[i]), "%c is not octal", NotOctal[i]);
        }
        GSTestAssert(!GSCharIsOctal('\0'), "'\0' is not octal");
}

void
TestCharIsDecimal()
{
        char *IsDecimal = "0123456789";
        char *NotDecimal = "aAfF\r\n\t ";

        for(int i = 0; i < GSStringLength(IsDecimal); i++)
        {
                GSTestAssert(GSCharIsDecimal(IsDecimal[i]), "%c is decimal", IsDecimal[i]);
        }

        for(int i = 0; i < GSStringLength(NotDecimal); i++)
        {
                GSTestAssert(!GSCharIsDecimal(NotDecimal[i]), "%c is not decimal", NotDecimal[i]);
        }
        GSTestAssert(!GSCharIsDecimal('\0'), "'\0' is not decimal");
}

void
TestCharIsHexadecimal()
{
        char *IsHexadecimal = "0123456789abcdefABCDEF";
        char *NotHexadecimal = "gGhH\r\n\t xX";

        for(int i = 0; i < GSStringLength(IsHexadecimal); i++)
        {
                GSTestAssert(GSCharIsHexadecimal(IsHexadecimal[i]), "%c is hexadecimal", IsHexadecimal[i]);
        }

        for(int i = 0; i < GSStringLength(NotHexadecimal); i++)
        {
                GSTestAssert(!GSCharIsHexadecimal(NotHexadecimal[i]), "%c is not hexadecimal", NotHexadecimal[i]);
        }
        GSTestAssert(!GSCharIsHexadecimal('\0'), "'\0' is not hexadecimal");
}

void
TestCharIsAlphabetical()
{
        char *IsAlphabetical = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char *NotAlphabetical = "01234567890\r\n\t ";

        for(int i = 0; i < GSStringLength(IsAlphabetical); i++)
        {
                GSTestAssert(GSCharIsAlphabetical(IsAlphabetical[i]), "%c is alphabetical", IsAlphabetical[i]);
        }

        for(int i = 0; i < GSStringLength(NotAlphabetical); i++)
        {
                GSTestAssert(!GSCharIsAlphabetical(NotAlphabetical[i]), "%c is not alphabetical", NotAlphabetical[i]);
        }
        GSTestAssert(!GSCharIsAlphabetical('\0'), "'\0' is not alphabetical");
}

void
TestCharIsAlphanumeric()
{
        char *IsAlphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";
        char *NotAlphanumeric = "-_\r\n\t ";

        for(int i = 0; i < GSStringLength(IsAlphanumeric); i++)
        {
                GSTestAssert(GSCharIsAlphanumeric(IsAlphanumeric[i]), "%c is alphanumeric", IsAlphanumeric[i]);
        }

        for(int i = 0; i < GSStringLength(NotAlphanumeric); i++)
        {
                GSTestAssert(!GSCharIsAlphanumeric(NotAlphanumeric[i]), "%c is not alphanumeric", NotAlphanumeric[i]);
        }
        GSTestAssert(!GSCharIsAlphanumeric('\0'), "'\0' is not alphanumeric");
}

void
TestCharUpcase()
{
        char *Chars = "aA_1wW";

        GSTestAssert(GSCharUpcase(*Chars) == 'A', "'a' is Upcased to 'A'");
        Chars++;
        GSTestAssert(GSCharUpcase(*Chars) == 'A', "'A' is not changed");
        Chars++;
        GSTestAssert(GSCharUpcase(*Chars) == '_', "'_' is not changed");
        Chars++;
        GSTestAssert(GSCharUpcase(*Chars) == '1', "'1' is not changed");
        Chars++;
        GSTestAssert(GSCharUpcase(*Chars) == 'W', "'w' is Upcased to 'W'");
        Chars++;
        GSTestAssert(GSCharUpcase(*Chars) == 'W', "'W' is not changed");
}

void
TestCharDowncase()
{
        char *Chars = "aA_1wW";

        GSTestAssert(GSCharDowncase(*Chars) == 'a', "'a' is not changed");
        Chars++;
        GSTestAssert(GSCharDowncase(*Chars) == 'a', "'A' is Downcased to 'a'");
        Chars++;
        GSTestAssert(GSCharDowncase(*Chars) == '_', "'_' is not changed");
        Chars++;
        GSTestAssert(GSCharDowncase(*Chars) == '1', "'1' is not changed");
        Chars++;
        GSTestAssert(GSCharDowncase(*Chars) == 'w', "'w' is not changed");
        Chars++;
        GSTestAssert(GSCharDowncase(*Chars) == 'w', "'W' is Downcased to 'w'");
}

/******************************************************************************
 * String interface
 ******************************************************************************/

void
TestStringIsEqual()
{
        GSTestAssert(GSStringIsEqual("Hello", "Hello", GSStringLength("Hello")), "%s is equal to %s", "Hello", "Hello");
        GSTestAssert(GSStringIsEqual("Hello", "Hello there", GSStringLength("Hello")), "%s is equal to %s", "Hello", "Hello there");
        GSTestAssert(!GSStringIsEqual("Hello", "Hel", GSStringLength("Hello")), "%s is not equal to %s", "Hello", "Hel");
}

void
TestStringLength()
{
        GSTestAssert(GSStringLength("Hello") == 5, "GSStringLength(\"Hello\") == 5");
        GSTestAssert(GSStringLength("") == 0, "GSStringLength(\"\") == 0");
}

void
TestStringCopyWithNull()
{
        char Buffer[256];
        memset(Buffer, 1, 256);

        GSStringCopyWithNull("hello", Buffer, 5);
        GSTestAssert(GSStringIsEqual("hello", Buffer, GSStringLength(Buffer)), "hello == %s", Buffer);
}

void
TestStringCopyWithoutSurroundingWhitespace()
{
        char Buffer[256];
        char *Source = "   Hello there    ";
        int StringLength = GSStringLength(Source);

        memset(Buffer, 0, 256);
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, 4);
        GSTestAssert(GSStringIsEqual("Hell", Buffer, 4), "Hell == %s", Buffer);

        memset(Buffer, 0, 256);
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, StringLength);
        GSTestAssert(GSStringIsEqual("Hello there", Buffer, GSStringLength("Hello there")), "Hello there == %s", Buffer);
}

void
TestStringCopyWithoutSurroundingWhitespaceWithNull()
{
        char Buffer[256];
        char *Source = "   Hello there    ";
        int StringLength = GSStringLength(Source);

        memset(Buffer, 1, 256); /* Set buffer to 1 so it's not NULL-terminated by default. */
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, 4);
        GSTestAssert(GSStringIsEqual("Hell", Buffer, 4), "Hell == %s", Buffer);

        memset(Buffer, 1, 256); /* Set buffer to 1 so it's not NULL-terminated by default. */
        GSStringCopyWithoutSurroundingWhitespace(Source, Buffer, StringLength);
        GSTestAssert(GSStringIsEqual("Hello there", Buffer, GSStringLength("Hello there")), "Hello there == %s", Buffer);
}

void
TestStringCapitalize()
{
        char *String;
        char Result[256];

        String = "_hello_there_";
        memset(Result, 0, 256);
        GSStringCapitalize(String, Result, GSStringLength(String));
        GSTestAssert(GSStringIsEqual("HelloThere", Result, GSStringLength(Result)), "HelloThere == %s", Result);

        String = "alllowercase";
        memset(Result, 0, 256);
        GSStringCapitalize(String, Result, GSStringLength(String));
        GSTestAssert(GSStringIsEqual("Alllowercase", Result, GSStringLength(Result)), "Alllowercase == %s", Result);

        String = "_123abc\\\"'abc123";
        memset(Result, 0, 256);
        GSStringCapitalize(String, Result, GSStringLength(String));
        GSTestAssert(GSStringIsEqual("123abcabc123", Result, GSStringLength(Result)), "123abcabc123 == %s", Result);

        String = "CapitalizedExample";
        memset(Result, 0, 256);
        GSStringCapitalize(String, Result, GSStringLength(String));
        GSTestAssert(GSStringIsEqual("Capitalizedexample", Result, GSStringLength(Result)), "Capitalizedexample == %s", Result);
}

/******************************************************************************
 * Hash Map interface
 ******************************************************************************/

void
TestHashMapBytesRequired()
{
        int StringLength = 256;
        int NumElements = 13;
        size_t NumBytes = GSHashMapBytesRequired(StringLength, NumElements);
        size_t Size = sizeof(gs_hash_map) + (StringLength * NumElements) + (sizeof(void *) * NumElements);
        GSTestAssert(NumBytes == Size, "%lu == %lu\n", Size, NumBytes);
}

void
TestHashMapInit()
{
        int StringLength = 256;
        int NumElements = 13;
        size_t NumBytes = GSHashMapBytesRequired(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        GSTestAssert(Map->Count == 0, "%i == %i\n", Map->Count, 0);
        GSTestAssert(Map->Capacity == NumElements, "%i == %i\n", Map->Capacity, NumElements);
        GSTestAssert(Map->AllocatedBytes == NumBytes, "%lu == %lu\n", Map->AllocatedBytes, NumBytes);
        GSTestAssert(Map->MaxKeyLength == StringLength, "%i == %i\n", Map->MaxKeyLength, StringLength);

        char *KeysPtr = (char *)Map + sizeof(gs_hash_map);
        GSTestAssert((char *)Map->Keys == KeysPtr, "%p == %p\n", (void *)Map->Keys, (void *)KeysPtr);

        char *ValuesPtr = KeysPtr + (StringLength * NumElements);
        GSTestAssert((char *)Map->Values == ValuesPtr, "%p == %p\n", (void *)Map->Values, (void *)ValuesPtr);
}

void
TestHashMapGrow()
{
        int StringLength = 256;
        int NumElements = 13;
        size_t NumBytes = GSHashMapBytesRequired(StringLength, NumElements);

        void *Memory1 = malloc(NumBytes);
        gs_hash_map *Map = GSHashMapInit(Memory1, StringLength, NumElements);

        void *Memory2 = malloc(NumBytes * 2);

        gs_bool GrowResult = GSHashMapGrow(&Map, 0, NULL);
        GSTestAssert(GrowResult == false, "Should not be able to shrink hash table\n");

        GrowResult = GSHashMapGrow(&Map, NumElements * 2, NULL);
        GSTestAssert(GrowResult == false, "Should not be able to grow into NULL memory\n");

        GrowResult = GSHashMapGrow(&Map, NumElements * 2, Memory2);
        GSTestAssert(GrowResult == true, "Should be able to grow!\n");

        free(Memory1);
        free(Memory2);
}

void
TestHashMapAdd()
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapBytesRequired(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        char *Keys = "Key1\0Key2\0Key3\0";
        int KeyIndices[] = { 0, 5, 10 };
        char *Values = "Value1\0Value2\0Value3\0";
        int ValueIndices[] = { 0, 7, 14 };

        gs_bool AddResult;
        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                char *Value = &Values[ValueIndices[I]];
                AddResult = GSHashMapAdd(Map, Key, (void *)Value);
                GSTestAssert(AddResult == true, "Should be able to add (%s,%s)\n", Key, Value);
        }

        char *ExtraKey = "Extra Key";
        char *ExtraValue = "Extra Value";
        AddResult = GSHashMapAdd(Map, ExtraKey, ExtraValue);
        GSTestAssert(AddResult == false, "HashMap is full, should not be able to add (%s,%s)\n", ExtraKey, ExtraValue);
}

void
TestHashMapHasKey()
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapBytesRequired(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        char *Keys = "Key1\0Key2\0Key3\0";
        int KeyIndices[] = { 0, 5, 10 };
        char *Values = "Value1\0Value2\0Value3\0";
        int ValueIndices[] = { 0, 7, 14 };

        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                char *Value = &Values[ValueIndices[I]];
                GSHashMapAdd(Map, Key, (void *)Value);
        }

        gs_bool HasResult;
        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                HasResult = GSHashMapHasKey(Map, Key);
                GSTestAssert(HasResult == true, "Should have key (%s)\n", Key);
        }

        HasResult = GSHashMapHasKey(Map, "Some Key");
        GSTestAssert(HasResult == false, "We never added (%s) as a key...\n", "Some Key");
}

void
TestHashMapGet()
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapBytesRequired(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        char *Keys = "Key1\0Key2\0Key3\0";
        int KeyIndices[] = { 0, 5, 10 };
        char *Values = "Value1\0Value2\0Value3\0";
        int ValueIndices[] = { 0, 7, 14 };

        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                char *Value = &Values[ValueIndices[I]];
                GSHashMapAdd(Map, Key, (void *)Value);
        }

        void *GetResult;
        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                GetResult = GSHashMapGet(Map, Key);
                char *Value = (char *)GetResult;
                int Length = GSStringLength(Value);
                char Tmp[StringLength];
                sprintf(Tmp, "Value%i", I+1);
                GSTestAssert(GSStringIsEqual(Value, Tmp, Length), "%s == %s\n", Value, Tmp);
        }

        GetResult = GSHashMapGet(Map, "Some Key");
        GSTestAssert(GetResult == NULL, "We never added (%s) as a key...\n", "Some Key");
}

void
TestHashMapDelete()
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapBytesRequired(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        char *Keys = "Key1\0Key2\0Key3\0";
        int KeyIndices[] = { 0, 5, 10 };
        char *Values = "Value1\0Value2\0Value3\0";
        int ValueIndices[] = { 0, 7, 14 };

        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                char *Value = &Values[ValueIndices[I]];
                GSHashMapAdd(Map, Key, (void *)Value);
        }

        void *DeleteResult;
        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                DeleteResult = GSHashMapDelete(Map, Key);
                char *Value = (char *)DeleteResult;
                int Length = GSStringLength(Value);
                char Tmp[StringLength];
                sprintf(Tmp, "Value%i", I+1);
                GSTestAssert(GSStringIsEqual(Value, Tmp, Length), "%s == %s\n", Value, Tmp);
                GSTestAssert(Map->Count == NumElements - (I + 1), "%i == %i\n", Map->Count, NumElements - (I + 1));
        }

        DeleteResult = GSHashMapDelete(Map, "Some Key");
        GSTestAssert(DeleteResult == NULL, "We never added (%s) as a key...\n", "Some Key");
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
        GSTestAssert(Result == true, "Arg(%s) is found", Wanted);

        Wanted = "arg3";
        Result = GSArgIsPresent(&Args, Wanted);
        GSTestAssert(Result == false, "Arg(%s) is not found", Wanted);
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
        GSTestAssert(Index == 0, "Arg(%s) is at index(%i)", Arg, Index);

        Arg = "arg3";
        Index = GSArgIndex(&Args, Arg);
        GSTestAssert(Index == -1, "Arg(%s) is not found", Arg);
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
        GSTestAssert(GSStringIsEqual(Arg, "arg1", 4), "Arg(%s) is at index(%i)", Arg, Index);

        Index = -1;
        Arg = GSArgAtIndex(&Args, Index);
        GSTestAssert(Arg == NULL, "Arg(%s) is not found", Arg);

        Index = 2;
        Arg = GSArgAtIndex(&Args, Index);
        GSTestAssert(Arg == NULL, "Arg(%s) is not found", Arg);
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
        GSTestAssert(GSStringIsEqual(After, "arg2", 4), "Arg(%s) follows Arg(%s)", After, Arg);

        Arg = "arg2";
        After = GSArgAfter(&Args, Arg);
        GSTestAssert(After == NULL, "No argument follows Arg(%s)", Arg);

        Arg = "What?";
        After = GSArgAfter(&Args, Arg);
        GSTestAssert(After == NULL, "No argument follows Arg(%s)", Arg);
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
        GSTestAssert(Result == true, "-h or --help is present");

        Params[0] = "--help";
        Result = GSArgHelpWanted(&Args);
        GSTestAssert(Result == true, "-h or --help is present");

        Params[0] = "arg1";
        Result = GSArgHelpWanted(&Args);
        GSTestAssert(Result == false, "-h or --help is not present");
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
        GSTestAssert(Buffer.Start == Memory, "Buffer starts at Memory");
        GSTestAssert(Buffer.Cursor == Memory, "Buffer Cursor is at Start");
        GSTestAssert(Buffer.Length == 0, "Buffer has zero length");
        GSTestAssert(Buffer.Capacity == 25, "Buffer has proper Capacity");
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
        GSTestAssert(IsEOF == false, "Buffer is not EOF");

        Buffer.Cursor++;
        IsEOF = GSBufferIsEOF(&Buffer);
        GSTestAssert(IsEOF == true, "Buffer is EOF");
}

void
TestBufferNextLine()
{
        gs_buffer Buffer;
        char *Text = "This\nIs\nSome\nText\n";
        GSBufferInit(&Buffer, Text, GSStringLength(Text));

        GSTestAssert(GSStringIsEqual(Text, Buffer.Start, GSStringLength(Text)), "Buffer is unmodified");

        GSBufferNextLine(&Buffer);
        GSTestAssert(GSStringIsEqual("Is\nSome\nText\n", Buffer.Cursor, GSStringLength("Is\nSome\nText\n")), "Buffer is advanced to next line");
}

void
TestBufferSaveCursor()
{
        gs_buffer Buffer;
        char *Text = "This\nIs\nSome\nText\n";
        GSBufferInit(&Buffer, Text, GSStringLength(Text));
        GSBufferSaveCursor(&Buffer);
        GSBufferNextLine(&Buffer);
        GSTestAssert(GSStringIsEqual(Text, Buffer.SavedCursor, GSStringLength(Text)), "SavedCursor is original text.");
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
        GSTestAssert(GSStringIsEqual(Text, Buffer.Cursor, GSStringLength(Text)), "Cursor is restored.");
}

void
TestFileSize()
{
        FILE *File = fopen("temp.txt", "w");
        fwrite("Test\n", 1, 5, File);
        fclose(File);

        int FileSize = GSFileSize("temp.txt");
        GSTestAssert(FileSize == 5, "Size of file (%i) is 5", FileSize);
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

        GSTestAssert(Buffer.Length == FileSize, "Entire file contents were copied.");
        GSTestAssert(GSBufferIsEOF(&Buffer), "Buffer cursor is at end of file in memory.");
        GSTestAssert(GSStringIsEqual(Buffer.Start, "Test\n", FileSize), "File text was copied correctly.");
}

int
main(int ArgCount, char **Args)
{
        /**********************************************************************
          gstest
         **********************************************************************/
        TestAssert();
        TestRandomString();
        /**********************************************************************
          gslibc
         **********************************************************************/
        /* Miscellaneous Macros */
        TestAbortWithMessage();
        TestArraySize();
        TestArrayForEach();
        TestMax();
        TestMin();
        TestBytesToKilobytes();
        TestBytesToMegabytes();
        TestBytesToGigabytes();
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
        TestCharIsAlphanumeric();
        TestCharUpcase();
        TestCharDowncase();
        /* String */
        TestStringIsEqual();
        TestStringLength();
        TestStringCopyWithNull();
        TestStringCopyWithoutSurroundingWhitespace();
        TestStringCopyWithoutSurroundingWhitespaceWithNull();
        TestStringCapitalize();
        /* Hash Map */
        TestHashMapBytesRequired();
        TestHashMapInit();
        TestHashMapGrow();
        TestHashMapAdd();
        TestHashMapHasKey();
        TestHashMapGet();
        TestHashMapDelete();
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
