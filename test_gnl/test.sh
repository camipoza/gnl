#!/bin/bash

# ===========================
# =          Color          =
__nc()      { echo -ne "\033[0m"; }
_red()      { echo -ne "\033[31m$1"$(__nc); }
_green()    { echo -ne "\033[32m$1"$(__nc); }
_yellow()   { echo -ne "\033[33m$1"$(__nc); }
_blue()     { echo -ne "\033[34m$1"$(__nc); }
# ===========================



# ===========================
# =         Globals         =
_output_gnl_filename="gnl.output.txt"
_output_val_filename="val.output.txt"


__strict=0
__breaked=0
# ===========================



# ===========================
# =        Functions        =
_p_error() { echo -e "\n$(_red " ✘ ")$1\n\n"; exit 2; }
_p_info() { echo -e "$(_blue " i ")$1"; }
_p_corner() { echo -ne "  » "; }
_p_file() { echo -ne "$(_yellow "•") $1"; }
_p_ok() { echo -e "$(_blue " ✔ ")$1\n"; }

_show_usage() {
    _p_info "What is ./test.sh?"
    _p_corner; echo -e "Multiple tests, with multiple buffers and files for get_next_line."
    echo -e "    Each test run with valgrind, and compares file output with original"
    echo -e "    You can add your own file in the /folder_tests."
    echo -e "    This use your get_next_line.c and get_next_line_utils.c"
    echo -e ""
    
    _p_info "Usage:"
    _p_corner; echo -e "--all\tTest all without break in the first wrong result."
    _p_corner; echo -e "--break\tTest and break in the first wrong result."
    _p_corner; echo -e "--help\t\tShow usage info."
    echo -e ""

    _p_info "Glossary:"
    _p_corner; echo -e "$(_red "𖹭")\t\tMeans, makefile failed."
    _p_corner; echo -e "$(_red "v")\t\tMeans, valgrind leaks."
    _p_corner; echo -e "$(_red "✘")\t\tMeans, your GNL output is not equal to test original file."
    _p_corner; echo -e "$(_yellow "•")\t\tMeans, In Vscode terminal, ctrl + click, to show the file."
    _p_corner; echo -e "$(_green "✔")\t\tMeans, no leaks and comparison correct."

    exit 0;
}
# ===========================

clear

# Args to do the test
if [ "$1" == "--help" ]; then
    _show_usage
elif [ "$1" == "--all" ]; then
    __strict=0
elif [ "$1" == "--break" ]; then
    __strict=1
else
    _show_usage
fi

echo -e "\n$(_blue " Get Next Line")"
echo -e "\ttest tool by werodrig.\n\n\n"
_blue "Filename\t1\t2\t3\t4\t5\t10\t20\t42\t100\t1000\t10000\n"


for file in ./folder_tests/*.txt; do

    echo -ne "${file#./folder_tests/}\t"

    for buffer_size in 1 2 3 4 5 10 20 42 100 1000 10000; do

        rm -f $_output_gnl_filename a.out $_output_val_filename
        echo -ne "\t"

        cc test_maker.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=$buffer_size -o a.out > /dev/null 2>&1

        if [ $? -ne 0 ]; then
            _red "𖹭"
            if [ $__strict -eq 1 ]; then
                echo -e "\n\n"
                _p_error "Ooops! compile failed.\n   With buffer ${buffer_size}.\n   In the file $(_p_file $file)."
                exit 1
            fi
            continue
        fi

        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -s --log-file=$_output_val_filename ./a.out "$(printf "%s" "$file")" >$_output_gnl_filename 2>&1
        if grep -q "ERROR SUMMARY: [^0]" $_output_val_filename; then
            _red "v"
            if [ $__strict -eq 1 ]; then
                _p_error "Ooops! valgrind dont like your code.\n   With buffer ${buffer_size}.\n   In the file\t$(_p_file $file).\n   Check\t$(_p_file $_output_val_filename)."
            fi
            continue
        fi


        diff -q "$file" $_output_gnl_filename > /dev/null 2>&1
        if [ $? -ne 0 ]; then
            _red "✘"
            if [ $__strict -eq 1 ]; then
                echo -e "\n\n"
                _p_error "Ooops! output isn't right.\n   With buffer ${buffer_size}.\n   In the file\t$(_p_file $file).\n   Check\t$(_p_file $_output_gnl_filename)."
                exit 1
            fi
            continue
        else
            _green "✔"
        fi
    done
    echo -e ""
done

rm -f a.out
if [ $__strict -eq 0 ]; then
    rm -f $_output_gnl_filename $_output_val_filename
fi

echo -e "\n"