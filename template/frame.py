# Autograder template for ECE 0301 at pitt
# Design and write by Guangzong Chen(guangzong@pitt.edu)
import unittest
from gradescope_utils.autograder_utils.decorators import partial_credit
from utils import get_output, compare_output, run_cmd
import shutil
import os


student_exec_full = os.path.join(test_working_dir, student_exec_name)
solution_exe_full = os.path.join(test_working_dir, solution_exec_name)

student_exec = f"./{student_exec_name}"
solution_exec = f"./{solution_exec_name}"


def compile_code():
    msg = run_cmd(compile_command_student)
    if not os.path.exists(student_exec_full):
        print(msg)
        return False

    run_cmd(compile_command_solution)
    if not os.path.exists(solution_exe_full):
        print("Autograder configuration is wrong. Contact Instructor and TAs.\n")
        return False
    return True


def test_input_no():
    score = full_score
    msgs = ""
    submission_stdout = get_output(f"{student_exec}", f"{test_working_dir}").decode('utf-8')
    jury_stdout = get_output(f"{solution_exec}", f"{test_working_dir}").decode('utf-8')
    ret, msg = compare_output(submission_stdout, jury_stdout)
    if not ret:
        print(msg)
        return 0
    return score


def test_input_by_string():
    score = full_score
    test_case_cnt = 0
    for inp in test_inputs:
        test_case_cnt += 1
        submission_stdout = get_output(f"{student_exec}", f"{test_working_dir}", inputs=inp).decode('utf-8')
        jury_stdout = get_output(f"{solution_exec}", f"{test_working_dir}", inputs=inp).decode('utf-8')
        ret, msg = compare_output(submission_stdout, jury_stdout)
        # ret, msg = test_cases(student_exec_name, solution_exec_name, inp)
        if not ret:
            print(f'Test {test_case_cnt}/{len(test_inputs)} failed.\nTest Input: \n{inp.decode()}\n')
            print(msg)
            score -= full_score / len(test_inputs)
    return score


def test_input_by_file():
    score = full_score
    test_file_list = []
    for file in os.listdir(test_cases_path):
        if file.endswith(".txt"):
            test_file_list.append(os.path.join(test_cases_path, file))
    test_case_cnt = 0
    for test_file in test_file_list:
        msgs = ""
        test_case_cnt += 1

        shutil.copy(test_file, f'{test_working_dir}/{test_input_filename}')  # overwrite
        output_file_path = os.path.join(test_working_dir, test_output_filename)

        submission_stdout = get_output(f"{student_exec}", f"{test_working_dir}").decode('utf-8')
        submission_out = ""
        jury_out = ""
        if os.path.exists(output_file_path):
            with open(output_file_path, 'r') as f:
                submission_out = f.read()
            os.remove(output_file_path)
        else:
            msgs += f'Submission no output file.\n'

        jury_stdout = get_output(f"{solution_exec}", f"{test_working_dir}").decode('utf-8')
        if os.path.exists(output_file_path):
            with open(output_file_path, 'r') as f:
                jury_out = f.read()
        else:
            msgs += f'Jury no output file.\n'

        ret, msg = compare_output(submission_out, jury_out)
        ret2, msg2 = compare_output(submission_stdout, jury_stdout)
        if ret is False or ret2 is False:
            print(f"Test {test_case_cnt}/{len(test_file_list)} failed. Input file name: {test_file}")
            print(msgs)

            score -= full_score / len(test_file_list)
            if not ret:
                print("file output does not match.")
                print(msg)
            if not ret2:
                print("stdout does not match.")
                print(msg2)

    return score


def test_late():
    return 0


class Test(unittest.TestCase):

    @partial_credit(full_score)
    def test(self, set_score=None):
        if not compile_code():
            set_score(0)
            return

        ls = test_late()

        if test_input_type == 0:
            set_score(max(0, test_input_no() + ls))
        if test_input_type == 1:
            set_score(max(0, test_input_by_string() + ls))
        if test_input_type == 2:
            set_score(max(0, test_input_by_file() + ls))


