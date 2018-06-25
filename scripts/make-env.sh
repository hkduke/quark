#!/bin/bash
relative_path=$(dirname $0)
source ${relative_path}/common.sh

save_env_parameters() {
    clearf=$1
    shift

    conf_file_name=$1
    pr_info "save env vars to $conf_file_name" info verbose

    shift

    paras=$*
    
    #echo $paras

    if [ $clearf = "1" ] && [ -f "$conf_file_name" ]; then
        rm $conf_file_name
    fi
    
    for i in ""$paras""; do
        if [ ${i:0:1} != "#" ]; then
            x=$(echo $i | sed 's/,/ /g')
            echo export $x >> $conf_file_name
        fi
    done
}

save_env() {
    output=$1
    shift
    static_input=$1
    shift
    
    vars_statics=$(cat $static_input)
    vars=$*
    
    #echo "111 $vars_statics"

    
    save_env_parameters 1 $output $vars_statics
    save_env_parameters 0 $output $vars

}

save_env $*
