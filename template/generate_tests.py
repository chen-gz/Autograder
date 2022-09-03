import os


if __name__ == "__main__":
    framework = './test_framework.py'
    tests_dir = './tests'

    test_sources = ""
    with open(framework) as f:
        test_sources += f.read()

    for file in os.listdir(tests_dir):
        if file.endswith('.txt'):
            out_source = ""
            with open(os.path.join(tests_dir, file)) as f1:
                out_source += f1.read()
                out_source += test_sources
            with open(os.path.join(tests_dir, os.path.splitext(file)[0]) + '.py', 'w') as f2:
                f2.write(out_source)

