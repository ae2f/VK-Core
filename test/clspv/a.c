#include <stdio.h>
#include <stdlib.h>
#include "clspv/Compiler.h"

static char VV[200];

int main() {
    // CL source example:
    const char* clSrc = "__kernel void sample_test(__global int *dst, int count) {  \n"
                        "                                                           \n"
                        "   int  tid = get_global_id(0);                            \n"
                        "   for( int i = 0; i < count; i++ )                        \n"
                        "       dst[i] = tid + i;                                   \n"
                        "}                                                          \n";

    // Compile
    size_t outputSpvSize = 0;
    char* outputSpv = NULL;
    char* outputBuildLog = NULL;
    ClspvError ret = clspvCompileFromSourcesString(1,
                                                   NULL,
                                                   (const char**)&clSrc,
                                                   "",
                                                   &outputSpv,
                                                   &outputSpvSize,
                                                   &outputBuildLog);
    printf("Build Log:\n%s\n", outputBuildLog);
    if (ret != CLSPV_SUCCESS) {
        // Handle error ...
    }

    // Cleanup
    clspvFreeOutputBuildObjs(outputSpv, outputBuildLog);
    /*
        // User can also cleanup like so:

        free(outputSpv);       outputSpv       = NULL;
        free(outputBuildLog);  outputBuildLog  = NULL;
    */

    return 0;
}
