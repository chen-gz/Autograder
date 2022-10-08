# score for this test
full_score = 20
penalty_perday = 0.05
tolerant = 1e-5

# 0 for no input; 1 for stdin input; 2 for file input;
test_input_type = 2
test_input_filename = "ece0301_unsorted_array.txt"
test_cases_path = "test_cases/step07"

# test_inputs should be set if test_input_type=0
test_inputs = []

# 0 for stdout output, 1 for file output
test_output_type = 1
test_output_filename = "ece0301_merge_sort_results.txt"

test_working_dir = "./test_dir/"

compile_command_student = f"g++ ./submissions/ece0301_ICA09_step07.cpp -o {test_working_dir}/submission"
compile_command_solution = f"g++ ./reference/ece0301_ICA09_step07.cpp -o {test_working_dir}/submission"

student_exec_name = f"submission"
solution_exec_name = f"solution"
