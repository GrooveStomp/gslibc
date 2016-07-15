/******************************************************************************
 * File: gs.h
 * Created: 2016-07-14
 * Last Updated: 2016-07-14
 * Creator: Aaron Oman (a.k.a GrooveStomp)
 * Notice: (C) Copyright 2016 by Aaron Oman
 ******************************************************************************/
#include <stdlib.h>
#include <string.h> /* memset */

/******************************************************************************
 * Boolean Definitions
 ******************************************************************************/

typedef int gs_bool;
#define false 0
#define true !false

/******************************************************************************
 * Character Definitions
 *-----------------------------------------------------------------------------
 * Functions to interact with C's basic ASCII char type.
 ******************************************************************************/

gs_bool
gs_IsCharEndOfStream(char C)
{
	return(C == '\0');
}

gs_bool
gs_IsCharEndOfLine(char C)
{
	return((C == '\n') ||
	       (C == '\r'));
}

gs_bool
gs_IsCharWhitespace(char C)
{
	return((C == ' ') ||
	       (C == '\t') ||
	       (C == '\v') ||
	       (C == '\f') ||
	       gs_IsCharEndOfLine(C));
}

gs_bool
gs_IsCharOctal(char C)
{
	gs_bool Result = (C >= '0' && C <= '7');
	return(Result);
}

gs_bool
gs_IsCharDecimal(char C)
{
	gs_bool Result = (C >= '0' && C <= '9');
	return(Result);
}

gs_bool
gs_IsCharHexadecimal(char C)
{
	gs_bool Result = ((C >= '0' && C <= '9') ||
		       (C >= 'a' && C <= 'f') ||
		       (C >= 'A' && C <= 'F'));
	return(Result);
}

gs_bool
gs_IsCharAlphabetical(char C)
{
	gs_bool Result = ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'));
	return(Result);
}

/******************************************************************************
 * String Definitions
 *-----------------------------------------------------------------------------
 * C string type. That is, ASCII characters with terminating NULL.
 ******************************************************************************/

gs_bool
gs_IsStringEqual(char *LeftString, char *RightString, int MaxNumToMatch)
{
	int NumMatched = 0;

	while(NumMatched < MaxNumToMatch)
	{
		if(*LeftString == *RightString)
		{
			LeftString++;
			RightString++;
			NumMatched++;
		}
		else
		{
			return(false);
		}
	}

	return(true);
}

size_t
gs_StringLength(char *String)
{
	char *P = String;
	while(*P != '\0') P++;
	return(P - String);
}

gs_bool
gs_StringCopyWithNull(char *Source, char *Dest)
{
        int i = 0;
        for(; Source[i] != '\0'; i++)
        {
                Dest[i] = Source[i];
        }
        Dest[i] = '\0';
}

/******************************************************************************
 * Hash Map
 *-----------------------------------------------------------------------------
 *
 * Usage:
 *     char *Value = "value";
 *     char *Result = NULL;
 *     gs_bool Found = false;
 *     gs_hash_map Map = gs_HashMapCreate();
 *     gs_HashMapAdd(&Map, "key", (void *)Value);
 *     Found = gs_HashMapGet(&Map, "key", (void *)Result);
 *     if(Found) printf("Result: %s\n", Result);
 *
 ******************************************************************************/

#define InitialSize 50

typedef struct gs_hash_map {
        int Count;
        int Size;
        int *Keys;
        void *(*Values);
} gs_hash_map;

int
__gs_HashMapCompute(char *Key)
{
        /*
          sdbm hash function: http://stackoverflow.com/a/14409947
        */
        int HashAddress = 0;
        for(int Counter = 0; Key[Counter] != '\0'; Counter++)
        {
                HashAddress = Key[Counter] +
                        (HashAddress << 6) +
                        (HashAddress << 16) -
                        HashAddress;
        }
        return(HashAddress);
}

size_t
gs_NumBytesForNewHashMap(int NumKeys)
{
        int SizeOfKeys = sizeof(int) * NumKeys;
        int SizeToAlloc = SizeOfKeys * 2 + sizeof(gs_hash_map);
        return(SizeToAlloc);
}

gs_hash_map *
__gs_HashMapAlloc(int NumKeys, void *Memory)
{
        gs_hash_map *NewHash;

        if(NumKeys == -1)
        {
                NumKeys = InitialSize;
        }

        int SizeToAlloc = gs_NumBytesForNewHashMap(NumKeys);
        int SizeOfKeys = sizeof(int) * NumKeys;

        if(Memory == NULL)
        {
                NewHash = (gs_hash_map*)malloc(SizeToAlloc);
        }
        else
        {
                NewHash = (gs_hash_map*)Memory;
        }
        memset((void *)NewHash, 0, sizeof(SizeToAlloc));

        NewHash->Keys = (int *)((char *)NewHash + sizeof(gs_hash_map));
        NewHash->Values = (void *)((char *)NewHash + sizeof(gs_hash_map) + SizeOfKeys);
        NewHash->Size = NumKeys;

        return(NewHash);
}

/*
  NumKeys: Number of initial key/value pairs expected. Specify -1 to use default.
  Memory:  Memory buffer to place HashMap into. Specify NULL to use malloc.
*/
gs_hash_map *
gs_HashMapCreate(int NumKeys, void *Memory) {
        gs_hash_map *NewHash = __gs_HashMapAlloc(NumKeys, Memory);
        return(NewHash);
}

gs_bool
gs_HashMapAdd(gs_hash_map *Hash, char *Key, void *Value) {
        if(Hash->Size == Hash->Count) return false;

        int IntKey = __gs_HashMapCompute(Key);
        Hash->Keys[Hash->Count] = IntKey;
        Hash->Values[Hash->Count++] = Value;
        return(true);
}

gs_bool
gs_HashMapGet(gs_hash_map *Hash, char *Key, void **Value) {
        int IntKey = __gs_HashMapCompute(Key);
        for(int i = 0; i < Hash->Count; ++i)
        {
                if(Hash->Keys[i] == IntKey)
                {
                        *Value = Hash->Values[i];
                        return true;
                }
        }
        return(false);
}
