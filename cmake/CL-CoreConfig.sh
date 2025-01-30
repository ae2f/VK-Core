#!/bin/bash

GIVEN_PATH="$1"
GIVEN_CL_PATH="$2"
GIVEN_COMPILER="$3"
HERE="$4"

PRM_INCLUDE="$HERE/clinclude/"

echo "Hello World! BmpCLConfig is running..."
echo "Current Position: $HERE"
echo "Given Path: $GIVEN_PATH"
echo "Given Compiler: $GIVEN_COMPILER"

# Preprocess 0: Get all source and throw it to ...cl
find "$GIVEN_PATH" -name '*.cl.c' | while read -r file; do
    OUT_NAME="${file%.cl.c}"
    OUT_NAME_TMP="${OUT_NAME}.tmp.c"
    OUT_NAME_H="${OUT_NAME}h"

    # Read the content of the file
    IN_CTN=$(<"$file")

    # Write to the temporary file
    {
        echo "#define ae2fCL_LocAsCL"
        echo "$IN_CTN"
    } > "$OUT_NAME_TMP"

    # Run the compiler
    $GIVEN_COMPILER -Wno-error -E -P -I"$PRM_INCLUDE" -I"$GIVEN_CL_PATH" "$OUT_NAME_TMP" -o "$OUT_NAME"
    
    # Remove the temporary file
    rm "$OUT_NAME_TMP"

    # Write to the header file
    {
        while IFS= read -r line; do
            echo "\"${line//\\/\\\\}\"" | sed 's/"/\\"/g' | sed 's/$/\\n"/'
        done < "$OUT_NAME"
    } > "$OUT_NAME_H"

    # Print the result (stdout)
    echo "$RESULT"
done