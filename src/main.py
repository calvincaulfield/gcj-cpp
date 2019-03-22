import sys
import os
import re
import subprocess

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

def remove_extension(path):
    return '.'.join(path.split('.')[:-1]) 

def get_file_names_with_extension(extension):
    return [file for file in get_files('.') if file.endswith(f".{extension}")]

def compare_two_files(path1, path2):
    f1 = open(path1)
    f2 = open(path2)

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
answer_files = get_file_names_with_extension("answer")

print("Start testing")
# Solve all problems and check output
for cpp_file in cpp_files:
    exe_file = remove_extension(cpp_file) + '.exe'
    return_code = subprocess.run(["g++", f"{cpp_file}", "-o", f"{exe_file}"]).returncode
    if (return_code != 0):
        sys.exit(f"Compile error {cpp_file}")
    #subprocess.run(["chmod", "733", f"{exe_file}"])

    for in_file in in_files:
        if (TEST_MODE == 1 and "large" in in_file):
            continue
        if (TEST_MODE == 2 and "test" not in in_file):
            continue

        if in_file.startswith(remove_extension(cpp_file)):
            out_file = in_file.replace('.in', '.out')
   
            return_code = subprocess.run([f"{exe_file}"], stdin=open(in_file), stdout=open(out_file, 'w')).returncode
            if (return_code != 0):
                sys.exit(f"Runtime error {cpp_file}")

            # Compare with already proven answers
            answer_file_to_be = in_file.replace('.in', '.answer')
            if (answer_file_to_be not in answer_files):
                print("Not solved:\t\t{}".format(in_file))
            elif not compare_two_files(out_file, answer_file_to_be):
                print("Output error:\t\t{}".format(out_file))
            else:
                print("Correct: {}".format(out_file))


