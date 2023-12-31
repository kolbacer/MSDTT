#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  bool use_linebreaks;
  bool use_flush;
  bool use_file_redirect;
} params;

params getParams(int argc, char *argv[]) {
    params newParams = {false, false, false};
    bool* currentParam = &(newParams.use_linebreaks);

    for(int i = 1; i < argc && i <= 3; ++i, ++currentParam)
        *currentParam = argv[i][0] == '1';

    return newParams; 
}

int main(int argc, char *argv[])
{ 
    params mainParams = getParams(argc, argv);

    FILE* outStream = stdout;
    FILE* errStream = stderr;

    char* outString = mainParams.use_linebreaks ? "STDOUT\n" : "STDOUT";
    char* errString = mainParams.use_linebreaks ? "STDERR\n" : "STDERR";

    if (mainParams.use_file_redirect) {
        outStream = fopen("./output.txt", "a");
        errStream = outStream;
    }

    fputs(outString, outStream);
    mainParams.use_flush && fflush(outStream);
    fputs(errString, errStream);
    mainParams.use_flush && fflush(errStream);

    mainParams.use_file_redirect && fclose(outStream);

    return 0;
}