#!/bin/bash

for i in {1..9..1}
do
cat > submit_${i}.jdl << EOF
Universe   = vanilla
Executable = test.sh 
Arguments  = ${i} 1
Log        = test_${i}.log
Output     = test_${i}.out
Error      = test_${i}.out
Queue
EOF

  condor_submit submit_${i}.jdl
done
