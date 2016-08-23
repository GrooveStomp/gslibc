/******************************************************************************
 * File: tests.c
 * Created: 2016-07-14
 * Last Updated: 2016-08-23
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
 * Miscellaneous Macros
 *****************************************************************************/
void
TestNullChar(void)
{
        GSTestAssert(GSNullChar == '\0', "%c == %c\n", GSNullChar, '\0');
}

void
TestNullPtr(void)
{
        GSTestAssert(GSNullPtr == NULL, "%p == %p\n", (void *)GSNullPtr, (void *)NULL);
}

void
TestAbortWithMessage(void)
{
        /* NOTE: Commented out because this exits on failure! */
        /* GSAbortWithMessage("%s expected to equal %s\n", "Hello", "Not Hello"); */
}

void
TestArraySize(void)
{
        int Numbers[] = { 1, 2, 3, 4, 5 };
        int Size = GSArraySize(Numbers);
        GSTestAssert(Size == 5, "Number of elements in `Numbers' is 5");
}

void
TestArrayForEach(void)
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
TestMax(void)
{
        int Result;

        Result = GSMax(1, 2);
        GSTestAssert(Result == 2, "Max chooses the larger value");
        Result = GSMax(2, 1);
        GSTestAssert(Result == 2, "Max chooses the larger value");
}

void
TestMin(void)
{
        int Result;

        Result = GSMin(1, 2);
        GSTestAssert(Result == 1, "Max chooses the smaller value");
        Result = GSMin(2, 1);
        GSTestAssert(Result == 1, "Max chooses the smaller value");
}

void
TestBytesToKilobytes(void)
{
        int Num = 1024;
        GSTestAssert(GSBytesToKilobytes(Num) == 1, "%i B == 1 KB", Num);
}

void
TestBytesToMegabytes(void)
{
        int Num = 1024*1024;
        GSTestAssert(GSBytesToMegabytes(Num) == 1, "%i B == 1 MB", Num);
}

void
TestBytesToGigabytes(void)
{
        int Num = 1024*1024*1024;
        GSTestAssert(GSBytesToGigabytes(Num) == 1, "%i B == 1 GB", Num);
}

/******************************************************************************
 * Boolean interface
 ******************************************************************************/

void
TestFalse(void)
{
        GSTestAssert(false != true, "False is not True");
        GSTestAssert(false == false, "False is False");
        GSTestAssert(false == 0, "False is Zero");
}

void
TestTrue(void)
{
        GSTestAssert(true != false, "True is not False");
        GSTestAssert(true == true, "True is True");
        GSTestAssert(true != 0, "True is not Zero");
}

/******************************************************************************
 * Char interface
 ******************************************************************************/

void
TestCharIsEndOfStream(void)
{
        GSTestAssert(GSCharIsEndOfStream('\0'), "%c is end of stream", '\0');
        GSTestAssert(!GSCharIsEndOfStream('1'), "%c is not end of stream", '1');
}

void
TestCharIsEndOfLine(void)
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
TestCharIsWhitespace(void)
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
TestCharIsOctal(void)
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
TestCharIsDecimal(void)
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
TestCharIsHexadecimal(void)
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
TestCharIsAlphabetical(void)
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
TestCharIsAlphanumeric(void)
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
TestCharIsUpcase(void)
{
        char *Chars = "aA_1wW";
        GSTestAssert(GSCharIsUpcase(*Chars) == false, "%c is not upcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsUpcase(*Chars) == true, "%c is upcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsUpcase(*Chars) == false, "%c is not upcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsUpcase(*Chars) == false, "%c is not upcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsUpcase(*Chars) == false, "%c is not upcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsUpcase(*Chars) == true, "%c is upcase\n", *Chars);
}

void
TestCharUpcase(void)
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
TestCharIsDowncase(void)
{
        char *Chars = "aA_1wW";
        GSTestAssert(GSCharIsDowncase(*Chars) == true, "%c is downcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsDowncase(*Chars) == false, "%c is not downcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsDowncase(*Chars) == false, "%c is not downcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsDowncase(*Chars) == false, "%c is not downcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsDowncase(*Chars) == true, "%c is downcase\n", *Chars);
        Chars++;
        GSTestAssert(GSCharIsDowncase(*Chars) == false, "%c is not downcase\n", *Chars);
}

void
TestCharDowncase(void)
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
TestStringIsEqual(void)
{
        GSTestAssert(GSStringIsEqual("Hello", "Hello", GSStringLength("Hello")), "%s is equal to %s", "Hello", "Hello");
        GSTestAssert(GSStringIsEqual("Hello", "Hello there", GSStringLength("Hello")), "%s is equal to %s", "Hello", "Hello there");
        GSTestAssert(!GSStringIsEqual("Hello", "Hel", GSStringLength("Hello")), "%s is not equal to %s", "Hello", "Hel");
}

void
TestStringLength(void)
{
        GSTestAssert(GSStringLength("Hello") == 5, "GSStringLength(\"Hello\") == 5");
        GSTestAssert(GSStringLength("") == 0, "GSStringLength(\"\") == 0");
}

void
TestStringCopy(void)
{
        char String[512] = { "Hello" };
        GSStringCopy("Bye", String, 3);
        GSTestAssert(GSStringIsEqual("Bye", String, GSStringLength(String)), "Bye == %s", String);
        GSTestAssert(String[3] == GSNullChar, "%c == %c\n", GSNullChar, String[3]);
}

void
TestStringCopyNoNull(void)
{
        char String[512] = { "Hello" };
        GSStringCopy("Bye", String, 3);
        GSTestAssert(GSStringIsEqual("Byelo", String, GSStringLength(String)), "Byelo == %s", String);
        GSTestAssert(String[5] == GSNullChar, "%c == %c\n", GSNullChar, String[5]);
}

void
TestStringTrimWhitespace(void)
{
        char String1[512] = { "    Middle   " };
        GSStringTrimWhitespace(String1, 13);
        GSTestAssert(GSStringIsEqual("Middle", String1, 6), "Middle == %s", String1);

        char String2[512] = { "   After" };
        GSStringTrimWhitespace(String2, 8);
        GSTestAssert(GSStringIsEqual("After", String2, 5), "After == %s", String2);

        char String3[512] = { "Before    " };
        GSStringTrimWhitespace(String3, 11);
        GSTestAssert(GSStringIsEqual("Before", String3, 6), "Before == %s", String3);
}

void
TestStringCapitalize(void)
{
        char Result[256];

        char String1[512] = { "_hello_there_" };
        GSStringCapitalize(String1, GSStringLength(String1));
        GSTestAssert(GSStringIsEqual("_Hello_there_", String1, GSStringLength(String1)), "_Hello_there_ == %s\n", String1);

        char String2[512] = { "alllowercase" };
        GSStringCapitalize(String2, GSStringLength(String2));
        GSTestAssert(GSStringIsEqual("Alllowercase", String2, GSStringLength(String2)), "Alllowercase == %s\n", String2);

        char String3[512] = { "_123abc\\\"'abc123" };
        GSStringCapitalize(String3, GSStringLength(String3));
        GSTestAssert(GSStringIsEqual("_123Abc\\\"'abc123", String3, GSStringLength(String3)), "_123Abc\\\"'abc123 == %s\n", String3);

        char String4[512] = { "CapitalizedExample" };
        GSStringCapitalize(String4, GSStringLength(String4));
        GSTestAssert(GSStringIsEqual("CapitalizedExample", String4, GSStringLength(String4)), "CapitalizedExample == %s\n", String4);
}

void
TestStringSnakeCaseToCamelCase(void)
{
        int NewSize;

        char String1[512] = { "snake_case" };
        NewSize = GSStringSnakeCaseToCamelCase(String1, GSStringLength(String1));
        GSTestAssert(NewSize == GSStringLength(String1), "%i == %lu\n", NewSize, GSStringLength(String1));
        GSTestAssert(GSStringIsEqual("SnakeCase", String1, GSStringLength(String1)),
                     "%s == %s\n", "SnakeCase", String1);

        char String2[512] = { "snakecase" };
        NewSize = GSStringSnakeCaseToCamelCase(String2, GSStringLength(String2));
        GSTestAssert(NewSize == GSStringLength(String2), "%i == %lu\n", NewSize, GSStringLength(String2));
        GSTestAssert(GSStringIsEqual("Snakecase", String2, GSStringLength(String2)),
                     "%s == %s\n", "Snakecase", String2);

        char String3[512] = { "_Snake_Case_" };
        NewSize = GSStringSnakeCaseToCamelCase(String3, GSStringLength(String3));
        GSTestAssert(NewSize == GSStringLength(String3), "%i == %lu\n", NewSize, GSStringLength(String3));
        GSTestAssert(GSStringIsEqual("SnakeCase_", String3, GSStringLength(String3)),
                     "%s == %s\n", "SnakeCase_", String3);
}

void
TestStringCamelCaseToSnakeCase(void)
{
        int NewSize;

        char String1a[512] = { "CamelCase" };
        char String1b[512];
        NewSize = GSStringCamelCaseToSnakeCase(String1a, String1b, GSStringLength(String1a));
        GSTestAssert(NewSize == GSStringLength(String1b), "%i == %lu\n", NewSize, GSStringLength(String1b));
        GSTestAssert(GSStringIsEqual("camel_case", String1b, GSStringLength(String1b)),
                     "%s == %s\n", "camel_case", String1b);

        char String2a[512] = { "camel_CaSe" };
        char String2b[512];
        NewSize = GSStringCamelCaseToSnakeCase(String2a, String2b, GSStringLength(String2a));
        GSTestAssert(NewSize == GSStringLength(String2b), "%i == %lu\n", NewSize, GSStringLength(String2b));
        GSTestAssert(GSStringIsEqual("camel__ca_se", String2b, GSStringLength(String2b)),
                     "%s == %s\n", "camel__ca_se", String2b);

        char String3a[512] = { "snake_case" };
        char String3b[512];
        NewSize = GSStringCamelCaseToSnakeCase(String3a, String3b, GSStringLength(String3a));
        GSTestAssert(NewSize == GSStringLength(String3b), "%i == %lu\n", NewSize, GSStringLength(String3b));
        GSTestAssert(GSStringIsEqual("snake_case", String3b, GSStringLength(String3b)),
                     "%s == %s\n", "snake_case", String3b);
}

void
TestStringKeep(void)
{
        char String1[512] = { "thisISisAaHIDDENhiddenMESSAGEmessage" };
        char String2[512];
        GSStringKeep(String1, String2, GSStringLength(String1), GSCharIsDowncase);
        GSTestAssert(GSStringIsEqual("thisisahiddenmessage", String2, GSStringLength(String2)),
                     "%s == %s\n", "thisisahiddenmessage", String2);
}

void
TestStringReject(void)
{
        char String1[512] = { "thisISisAaHIDDENhiddenMESSAGEmessage" };
        char String2[512];
        GSStringReject(String1, String2, GSStringLength(String1), GSCharIsUpcase);
        GSTestAssert(GSStringIsEqual("thisisahiddenmessage", String2, GSStringLength(String2)),
                     "%s == %s\n", "thisisahiddenmessage", String2);
}

/******************************************************************************
 * Hash Map interface
 ******************************************************************************/

void
TestHashMapBytesRequired(void)
{
        int StringLength = 256;
        int NumElements = 13;
        size_t NumBytes = GSHashMapAllocSize(StringLength, NumElements);
        size_t Size = sizeof(gs_hash_map) + (StringLength * NumElements) + (sizeof(void *) * NumElements);
        GSTestAssert(NumBytes == Size, "%lu == %lu\n", Size, NumBytes);
}

void
TestHashMapInit(void)
{
        int StringLength = 256;
        int NumElements = 13;
        size_t NumBytes = GSHashMapAllocSize(StringLength, NumElements);
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
TestHashMapGrow(void)
{
        int StringLength = 256;
        int NumElements = 13;
        size_t NumBytes = GSHashMapAllocSize(StringLength, NumElements);

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
TestHashMapSet(void)
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapAllocSize(StringLength, NumElements);
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
                AddResult = GSHashMapSet(Map, Key, (void *)Value);
                GSTestAssert(AddResult == true, "Should be able to add (%s,%s)\n", Key, Value);
        }

        char *ExtraKey = "Extra Key";
        char *ExtraValue = "Extra Value";
        AddResult = GSHashMapSet(Map, ExtraKey, ExtraValue);
        GSTestAssert(AddResult == false, "HashMap is full, should not be able to add (%s,%s)\n", ExtraKey, ExtraValue);

        /* Now test updating a value. */
        char *UpdatedValue = "UpdatedValue";
        AddResult = GSHashMapSet(Map, "Key1", UpdatedValue);
        GSTestAssert(AddResult == true, "Updated value for key (%s)\n", "Key1");

        void *GetResult = GSHashMapGet(Map, "Key1");
        GSTestAssert(GetResult != GSNullPtr, "GetResult should be valid\n");
        GSTestAssert((char *)GetResult == UpdatedValue, "%p == %p\n", GetResult, (void *)UpdatedValue);
}

void
TestHashMapHasKey(void)
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapAllocSize(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        char *Keys = "Key1\0Key2\0Key3\0";
        int KeyIndices[] = { 0, 5, 10 };
        char *Values = "Value1\0Value2\0Value3\0";
        int ValueIndices[] = { 0, 7, 14 };

        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                char *Value = &Values[ValueIndices[I]];
                GSHashMapSet(Map, Key, (void *)Value);
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
TestHashMapGet(void)
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapAllocSize(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        char *Keys = "Key1\0Key2\0Key3\0";
        int KeyIndices[] = { 0, 5, 10 };
        char *Values = "Value1\0Value2\0Value3\0";
        int ValueIndices[] = { 0, 7, 14 };

        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                char *Value = &Values[ValueIndices[I]];
                GSHashMapSet(Map, Key, (void *)Value);
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
TestHashMapDelete(void)
{
        int StringLength = 256;
        int NumElements = 3;
        size_t NumBytes = GSHashMapAllocSize(StringLength, NumElements);
        gs_hash_map *Map = GSHashMapInit(alloca(NumBytes), StringLength, NumElements);

        char *Keys = "Key1\0Key2\0Key3\0";
        int KeyIndices[] = { 0, 5, 10 };
        char *Values = "Value1\0Value2\0Value3\0";
        int ValueIndices[] = { 0, 7, 14 };

        for(int I = 0; I < NumElements; I++)
        {
                char *Key = &Keys[KeyIndices[I]];
                char *Value = &Values[ValueIndices[I]];
                GSHashMapSet(Map, Key, (void *)Value);
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
TestArgsIsPresent(void)
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args *Args;
        Args = GSArgsInit(alloca(GSArgsAllocSize()), Count, Params);

        char *Wanted = "arg1";
        gs_bool Result = GSArgsIsPresent(Args, Wanted);
        GSTestAssert(Result == true, "Arg(%s) is found", Wanted);

        Wanted = "arg3";
        Result = GSArgsIsPresent(Args, Wanted);
        GSTestAssert(Result == false, "Arg(%s) is not found", Wanted);
}

void
TestArgsFind(void)
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args *Args;
        Args = GSArgsInit(alloca(GSArgsAllocSize()), Count, Params);

        char *Arg = "arg1";
        int Index = GSArgsFind(Args, Arg);
        GSTestAssert(Index == 0, "Arg(%s) is at index(%i)", Arg, Index);

        Arg = "arg3";
        Index = GSArgsFind(Args, Arg);
        GSTestAssert(Index == -1, "Arg(%s) is not found", Arg);
}

void
TestArgsAtIndex(void)
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args *Args;
        Args = GSArgsInit(alloca(GSArgsAllocSize()), Count, Params);

        int Index = 0;
        char *Arg = GSArgsAtIndex(Args, Index);
        GSTestAssert(GSStringIsEqual(Arg, "arg1", 4), "Arg(%s) is at index(%i)", Arg, Index);

        Index = -1;
        Arg = GSArgsAtIndex(Args, Index);
        GSTestAssert(Arg == NULL, "Arg(%s) is not found", Arg);

        Index = 2;
        Arg = GSArgsAtIndex(Args, Index);
        GSTestAssert(Arg == NULL, "Arg(%s) is not found", Arg);
}

void
TestArgsAfter(void)
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "arg1";
        Params[1] = "arg2";

        gs_args *Args;
        Args = GSArgsInit(alloca(GSArgsAllocSize()), Count, Params);

        char *Arg = "arg1";
        char *After = GSArgsAfter(Args, Arg);
        GSTestAssert(GSStringIsEqual(After, "arg2", 4), "Arg(%s) follows Arg(%s)", After, Arg);

        Arg = "arg2";
        After = GSArgsAfter(Args, Arg);
        GSTestAssert(After == NULL, "No argument follows Arg(%s)", Arg);

        Arg = "What?";
        After = GSArgsAfter(Args, Arg);
        GSTestAssert(After == NULL, "No argument follows Arg(%s)", Arg);
}

void
TestArgsHelpWanted(void)
{
        const int Count = 2;
        char *Params[Count];
        Params[0] = "-h";
        Params[1] = "arg2";

        gs_args *Args;
        Args = GSArgsInit(alloca(GSArgsAllocSize()), Count, Params);

        gs_bool Result = GSArgsHelpWanted(Args);
        GSTestAssert(Result == true, "-h or --help is present");

        Params[0] = "--help";
        Result = GSArgsHelpWanted(Args);
        GSTestAssert(Result == true, "-h or --help is present");

        Params[0] = "arg1";
        Result = GSArgsHelpWanted(Args);
        GSTestAssert(Result == false, "-h or --help is not present");
}

/******************************************************************************
 * Byte Streams and Buffers
 ******************************************************************************/

void
TestBufferInit(void)
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
TestBufferIsEOF(void)
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
TestBufferNextLine(void)
{
        gs_buffer Buffer;
        char *Text = "This\nIs\nSome\nText\n";
        GSBufferInit(&Buffer, Text, GSStringLength(Text));

        GSTestAssert(GSStringIsEqual(Text, Buffer.Start, GSStringLength(Text)), "Buffer is unmodified");

        GSBufferNextLine(&Buffer);
        GSTestAssert(GSStringIsEqual("Is\nSome\nText\n", Buffer.Cursor, GSStringLength("Is\nSome\nText\n")), "Buffer is advanced to next line");
}

void
TestBufferSaveCursor(void)
{
        gs_buffer Buffer;
        char *Text = "This\nIs\nSome\nText\n";
        GSBufferInit(&Buffer, Text, GSStringLength(Text));
        GSBufferSaveCursor(&Buffer);
        GSBufferNextLine(&Buffer);
        GSTestAssert(GSStringIsEqual(Text, Buffer.SavedCursor, GSStringLength(Text)), "SavedCursor is original text.");
}

void
TestBufferRestoreCursor(void)
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
TestFileSize(void)
{
        FILE *File = fopen("temp.txt", "w");
        fwrite("Test\n", 1, 5, File);
        fclose(File);

        int FileSize = GSFileSize("temp.txt");
        GSTestAssert(FileSize == 5, "Size of file (%i) is 5", FileSize);
        remove("temp.txt");
}

void
TestFileCopyToBuffer(void)
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
        /* Miscellaneous Macros */
        TestNullChar();
        TestNullPtr();
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
        TestCharIsUpcase();
        TestCharUpcase();
        TestCharIsDowncase();
        TestCharDowncase();
        /* String */
        TestStringIsEqual();
        TestStringLength();
        TestStringCopy();
        TestStringCopyNoNull();
        TestStringTrimWhitespace();
        TestStringCapitalize();
        TestStringSnakeCaseToCamelCase();
        TestStringCamelCaseToSnakeCase();
        TestStringKeep();
        TestStringReject();
        /* Hash Map */
        TestHashMapBytesRequired();
        TestHashMapInit();
        TestHashMapGrow();
        TestHashMapSet();
        TestHashMapHasKey();
        TestHashMapGet();
        TestHashMapDelete();
        /* Arg Parsing */
        TestArgsIsPresent();
        TestArgsFind();
        TestArgsAtIndex();
        TestArgsAfter();
        TestArgsHelpWanted();
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
