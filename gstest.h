#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */

#define GSTestAssert(Expression, ...) \
        { \
                if(!(Expression)) \
                { \
                        fprintf(stderr, "Assertion failed in %s() at line #%d: ", __func__, __LINE__); \
                        fprintf(stderr, __VA_ARGS__); \
                        exit(EXIT_FAILURE); \
                } \
        }

unsigned int /* Memory should be MaxLength size, at least. */
GSTestRandomString(char *Memory, unsigned int MaxLength, unsigned int MinLength)
{
        int Length = rand() % (MaxLength - MinLength) + MinLength;
        int Range = 'z' - 'a';
        for(int I=0; I<Length; I++)
        {
                Memory[I] = rand() % Range + 'a';
        }
        Memory[Length] = '\0';

        return(Length);
}
