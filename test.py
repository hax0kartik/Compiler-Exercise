import os, subprocess, glob

test_files = glob.glob("tests/*.tt")

for test_file in test_files:
    f = open(test_file, "r")
    file = f.read()
    f.close()

    print("---/ File Contents /---")
    print(file)

    initial_res = os.popen(f"./compiler {test_file} out.s").read()
    print("---/ Compilation proces /---")
    print(initial_res)

    print("---/ Generated code /---")
    print(open("out.s", "r").read())

    print("---/ Executing generated code /---")
    res = os.popen(f"gcc out.s -o out.out && ./out.out").read()
    print(res.strip("\n"))
    print("----------------------------------\n")
