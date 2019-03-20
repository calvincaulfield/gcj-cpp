import sys
import os
import re
import importlib
import solution

SOLUTION_DIRECTORY = "solution"
INPUT_FILE_DIR = "in"
OUTPUT_FILE_DIR = "out"
ANSWER_FILE_DIR = "answer"


# 0: full, 1: small, 2: test
TEST_MODE = 0

def get_files(dir):
    result = []
    for cur, _, files in os.walk(dir):
        for file in files:
            result.append(os.path.relpath(os.path.join(cur, file), dir))
    return result

def remove_extension(file):
    pass

def get_file_names_with_extension(extension):
    return [file for file in get_files('.') if file.endswith(f".{extension}")]

def compare_two_files(file1, file2):
    f1 = open(file1)
    f2 = open(file2)

    while True:
        line1 = f1.readline()
        line2 = f2.readline()
        if (line1 != line2):
            return False
        if (not line1):
            break
    return True

cpp_files = get_file_names_with_extension("cpp")
in_files = get_file_names_with_extension("in")
answer_files = get_file_names_with_extension("ok")

# Solve all problems and check output
for cpp_file in cpp_files:

    for in_file in in_files:
        if (TEST_MODE == 1 and "large" in in_file):
            continue
        if (TEST_MODE == 2 and "test" not in in_file):
            continue

        if in_file.startswith(cpp_files):
            handle = open(os.path.join(INPUT_FILE_DIR, in_file))
            out_file = in_file.replace('.in', '.out')
            out_handle = open(os.path.join(OUTPUT_FILE_DIR, out_file), 'w')
            eval("{}.solve({}, {})".format(module, 'handle', 'out_handle'))
            handle.close()
            out_handle.close()

            # Compare with already proven answers
            if (out_file not in answer_files):
                print("Not solved:\t\t{}".format(out_file))
            elif not compare_two_files(os.path.join(OUTPUT_FILE_DIR, out_file), os.path.join(ANSWER_FILE_DIR, out_file)):
                    print("Output error:\t\t{}".format(out_file))
            else:
                print("Correct: {}".format(out_file))


