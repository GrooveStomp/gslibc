/******************************************************************************
 * File: gstests.c
 * Created: 2016-08-22
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

void
TestAssert(void)
{
        /* NOTE: Commented out because this exits on failure! */
        /* GSTestAssert(1 == 2, "Expect %i to equal %i\n", 1, 2); */
}

void
TestRandomString(void)
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

int
main(int ArgCount, char **Args)
{
        TestAssert();
        TestRandomString();

        printf("All tests passed\n");
        return(EXIT_SUCCESS);
}
