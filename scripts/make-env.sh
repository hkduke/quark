#!/bin/bash
relative_path=$(dirname $0)
source ${relative_path}/common.sh

save_env_parameters() {
    conf_file_name=$1
    pr_info "save env vars to $conf_file_name" info verbose

    shift

    paras=$*

    if [ -f "$conf_file_name" ]; then
        rm $conf_file_name
    fi

    for i in ""$paras""; do
        echo export $i >> $conf_file_name
    done
}


save_env_parameters $*
