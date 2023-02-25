#!/bin/bash
for try in 1 2; do
    echo ----------------------------------------------------------------------
    echo TRY $try:
    ./test/RUN_hybrid/performance_hybrid_1aboA.sh
    ./test/RUN_hybrid/performance_hybrid_1sbp.sh
    ./test/RUN_hybrid/performance_hybrid_glg.sh
    ./test/RUN_hybrid/performance_hybrid_actin.sh
    ./test/RUN_hybrid/performance_hybrid_2ack.sh
    ./test/RUN_hybrid/performance_hybrid_1hvA.sh
    ./test/RUN_hybrid/performance_hybrid_2cba.sh
    #./test//RUN_hybrid/performance_hybrid_2myr.sh #No memory!
done
