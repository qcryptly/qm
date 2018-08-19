#!/bin/bash
TEST_RESULTS=true
for filename in build/kernels/test*; do
    $filename
    TEST_RESULTS=$?&$TEST_RESULTS
done

echo "Regression test status: $TEST_RESULTS"
