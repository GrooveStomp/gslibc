#include "gs.h"
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */
#include <stdio.h>
#include <alloca.h>

#define Assert(Description, Expression) AssertFn((Description), (Expression), __LINE__, __func__)

void
AssertFn(const char *Description, int Expression, int LineNumber, const char *FuncName)
{
        if(!Expression)
        {
                char *Suffix = "";
                if(Description != NULL)
                {
                        size_t AllocSize = gs_StringLength((char *)Description) + gs_StringLength(": ");
                        Suffix = (char *)alloca(AllocSize);
                        snprintf(Suffix, AllocSize + 1, ": %s", Description);
                }
                fprintf(stderr, "Assertion failed in %s() at line #%d%s\n", FuncName, LineNumber, Suffix);

                exit(EXIT_FAILURE);
        }
}

/******************************************************************************
 * Boolean interfaces
 ******************************************************************************/

void
TestFalse()
{
        Assert("False is not True", false != true);
        Assert("False is False", false == false);
        Assert("False is Zero", false == 0);
}

void
TestTrue()
{
        Assert("True is not False", true != false);
        Assert("True is True", true == true);
        Assert("True is not Zero", true != 0);
}

/******************************************************************************
 * Char interfaces
 ******************************************************************************/

void
TestIsCharEndOfStream()
{
        Assert("Is end of stream", gs_IsCharEndOfStream('\0'));
        Assert("Is not end of stream", !gs_IsCharEndOfStream('1'));
}

void
TestIsCharEndOfLine()
{
        Assert("\\n is end of line", gs_IsCharEndOfLine('\n'));
        Assert("\\r is end of line", gs_IsCharEndOfLine('\r'));
        Assert("\\t is not end of line", !gs_IsCharEndOfLine('\t'));
        Assert("1 is not end of line", !gs_IsCharEndOfLine('1'));
}

int
main(int ArgCount, char **Args)
{
        TestFalse();
        TestTrue();
        TestIsCharEndOfStream();
        TestIsCharEndOfLine();

        printf("All tests passed\n");
        return(EXIT_SUCCESS);
}
