import unittest
# from gradescope_utils.autograder_utils.decorators import weight
# from gradescope_utils.autograder_utils.decorators import partial_credit
# import subprocess32 as subprocess
import subprocess
from os import path
import os
import logging
import re
import sys
import shlex
from typing import Union


def get_output(exe_file, cwd='', inputs=b''):
    """
    This function is used to get the output from the executing file
    Notice that instead of getting the unicode(which is recommended by gradescope) string, I just fetch the
    string from stdout. Because in our homework we always use ASCII
    @exe_file    A unicode string representing the executing file
    @return    The standard output string
    """
    # args = shlex.split(exe_file)
    test_program = subprocess.run(exe_file, stdout=subprocess.PIPE, stderr=subprocess.PIPE, input=inputs, cwd=cwd)
    # output,
    return test_program.stdout + test_program.stderr


def run_cmd(command: str):
    args = shlex.split(command)
    proc = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    # print(proc.stdout.read())
    return str(proc.stdout.read().decode()) + '\n' + str(proc.stderr.read().decode())



def compare_output(user_input: str, target: str, tolerant: Union[float,None] = None):
    ret = True
    input_lines_tmp = user_input.splitlines()
    target_lines_tmp = target.splitlines()
    input_lines = [line for line in input_lines_tmp if line.strip() != ""]
    target_lines = [line for line in target_lines_tmp if line.strip() != ""]
    msg = ''
    if len(input_lines) != len(target_lines):
        msg += f'Jury have {len(target_lines)} lines output.\nYou have {len(input_lines)} lines output.\n'
        ret = False
    line_mismatch = False
    for i in range(min(len(input_lines), len(target_lines))):
        if input_lines[i] == target_lines[i]:
            continue
        input_words = input_lines[i].lower().split()
        target_words = target_lines[i].lower().split()
        if input_words == target_words:
            continue
        # chech words length
        if len(input_words) == len(target_words):
            # check numbers
            ok = True
            for j in range(len(input_words)):
                input_word = input_words[j]
                target_word = target_words[j]
                if input_word == target_word:
                    continue
                if tolerant is not None:
                    try:
                        if abs(float(input_word) - float(target_word)) <= tolerant:
                            continue
                        else:
                            ok = False
                            break
                    except ValueError:
                        pass
            if ok:
                continue

        msg += f'First mismatch line is {i}\n'
        msg += f'The jury output is:"{target_lines[i]}".\n'
        msg += f'You    output   is:"{input_lines[i]}".\n\n'
        ret = False
        line_mismatch = True
        break
    if not line_mismatch and not ret:
        if len(input_lines) < len(target_lines):
            msg += f'Jury output at line {len(input_lines)} is "{target_lines[len(input_lines)]}"\n'
    return ret, msg
