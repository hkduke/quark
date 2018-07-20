#!/bin/bash

check_if_smp_env() {
    flag=$(uname -an | grep SMP);
    if [ "$flag" = "" ]; then
        echo "0";
    else
        echo "1";
    fi
}

check_if_smp_env
