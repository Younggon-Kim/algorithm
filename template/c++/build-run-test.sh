#!/bin/bash

usage()
{
    echo "Description : Run testcases"
    echo "Usage : "
    echo "     $ source `basename "$0"` -f <filter expression> -p <tc path>"
    echo "Requirement : Implement freopen()"
    echo "#include <cstdio>"
    echo "using namespace std;"
    echo "    int main() {"
    echo "        freopen(getenv("out"), "w", stdout);"
    echo "        freopen(getenv("in"), "r", stdin);"
    echo "        int tc;"
    echo "        cin >> tc;  // read from "in""
    echo "        cout << tc << endl; //write to "out""
    echo "}"
    echo "Optional parameters:"
    echo "    [-f]: file name to build; default main.cc"
    echo "    [-p]: path where TC files exist"
    echo "    [-c]: clean output diretories"
    echo "    [-b]: build only, not test"
    echo "    [-h]: help"
    exit 0
}

logging()
{
    echo "======================================"
    echo "$1"
    echo "======================================"
}

clean_output()
{
    rm -rf ./output-*
    logging "Clean output completed :=)"
    exit 0
}

build_file="main.cc"
exec_file="a.out"
tc_path="tc"
output_path="output-$(date '+%Y%m%d-%H%M%S')"
exec_test=true

OLD_OPTIND=$OPTIND
while getopts "hf:p:cb" opt_flag
do
    case $opt_flag in
        h) usage;
            ;;
        f) build_file="$OPTARG";
            ;;
        p) tc_path="$OPTARG";
            ;;
        c) clean_output;
            ;;
        b) exec_test=false;
            ;;
        ?) usage;
            ;;
    esac
done
OPTIND=$OLD_OPTIND

build()
{
    if [[ ${OSTYPE} == "darwin"* ]]; then
        g++-12 -std=c++1z "./${build_file}"
    else
        g++ -std=c++1z "./${build_file}"
    fi

    if [[ $? != 0 ]]; then
        logging "[ERROR] Fail to build ${build_file}"
        exit 1
    fi

    logging "Build completed :-)"
}

test()
{
    logging "Test started :=o $(date '+%Y/%m/%d-%H:%M:%S')"
    mkdir "${output_path}"
    tc_input_files=$(ls ./${tc_path}/*.in)
    for tc_input_file in ${tc_input_files}
    do
        # prepare variables
        tc_name=${tc_input_file%%".in"}
        tc_name=${tc_name##"./${tc_path}/"}
        tc_output_file="./${tc_path}/${tc_name}.out"
        output_file="./${output_path}/${tc_name}.out"
        diff_file="./${output_path}/${tc_name}.diff"

        # execute
        time env in="${tc_input_file}" out="${output_file}" ./${exec_file}

        # check output and tc output
        diff=`diff "${output_file}" "${tc_output_file}"`
        if [[ ! -z "${diff}" ]]; then
            echo "output and tc output" >> "${diff_file}"
            echo "${diff}" >> "${diff_file}"
        else
            rm "${output_file}"
        fi
    done
    logging "Test completed :-) $(date '+%Y/%m/%d-%H:%M:%S')"
}

build
if [[ "$exec_test" == true ]]; then
    test
fi