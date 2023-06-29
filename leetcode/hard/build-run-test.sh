#!/bin/bash

usage()
{
    echo "Description : Run testcases"
    echo "Usage : "
    echo "     $ source `basename "$0"` -f <file name> -p <tc path>"
    echo "Requirement : Implement freopen()"
    echo "#include <cstdio>"
    echo "using namespace std;"
    echo "    int main() {"
    echo "        freopen(getenv(\"out\"), "w", stdout);"
    echo "        freopen(getenv(\"in\"), "r", stdin);"
    echo "        int tc;"
    echo "        cin >> tc;  // read from "in""
    echo "        cout << tc << endl; //write to "out""
    echo "}"
    echo "Optional parameters:"
    echo "    [-f]: file name to build; default main.cc"
    echo "    [-p]: path where TC files exist"
    echo "    [-c]: clean output diretories"
    echo "    [-b]: build only, not test"
    echo "    [-y]: run python and test it"
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
    if [[ -f "./a.out" ]]; then
        rm ./a.out
    fi
    logging "Clean output completed :=)"
    exit 0
}

build_file="main.cc"
exec_file="a.out"
tc_path="tc"
output_path="output-$(date '+%Y%m%d-%H%M%S')"
run_test=true
run_python=false
python_file="main.py"
target_file=""

OLD_OPTIND=$OPTIND
while getopts "hf:p:cby" opt_flag
do
    case $opt_flag in
        h) usage;
            ;;
        f) target_file="$OPTARG";
            ;;
        p) tc_path="$OPTARG";
            ;;
        c) clean_output;
            ;;
        b) run_test=false;
            ;;
        y) run_python=true;
            ;;
        ?) usage;
            ;;
    esac
done
OPTIND=$OLD_OPTIND

if [[ -n "$target_file" ]]; then
    build_file=$target_file
    python_file=$target_file
fi

build_cpp()
{
    if [[ ${OSTYPE} == "darwin"* ]]; then
        g++-13 -std=c++1z "./${build_file}"
    else
        g++ -std=c++1z "./${build_file}"
    fi

    if [[ $? != 0 ]]; then
        logging "[ERROR] Fail to build ${build_file}"
        exit 1
    fi

    logging "Build completed :-)"
}

test_cpp()
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

    if [[ -f "./$exec_file" ]]; then
        rm ./${exec_file}
    fi
}

test_python()
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
        time cat ${tc_input_file} | python3 ./${python_file} > ${output_file}

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

main()
{
    if [[ "$run_python" == true ]]; then
        test_python
    else
        build_cpp
        if [[ "$run_test" == true ]]; then
            test_cpp
        fi
    fi
}

main