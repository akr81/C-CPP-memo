import glob
import os
import re
import subprocess
import sys

files = glob.glob('./test/*.cpp')

for file in files:
    # print target file
    print(os.path.basename(file))

    # execute preprocess
    command = ["g++", file, "-E"]
    res = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    out = res.stdout.decode("utf-8")

    outline = []

    # modify function call
    for line in out.splitlines():
        candidate = True

        # target line must have "ptr_type"
        if not "ptr_type" in line:
            candidate = False

        # remove typedef declaration
        if "typedef" in line:
            candidate = False

        # remove non-function
        if not re.search('\w+\(.*\)', line):
            candidate = False

        # remove prototype declaration
        if re.search('\w+\s+\w+\(', line):
            candidate = False

        # replace target
        if candidate:
            line = re.sub('\w+ptr_type', '', line)
            print(line)

        # store result
        outline.append(line)

    # output to file
    outpath = os.path.join("./pre", os.path.basename(file))
    with open(outpath, mode='w') as f:
        f.write('\n'.join(outline))