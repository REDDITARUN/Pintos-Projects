import sys
import subprocess


def score_arg_passing(echo_call):

    ### Run test_arg_passing.sh script
    result = subprocess.Popen(['pa2_arg_test/test_arg_passing.sh', echo_call],
             stdout=subprocess.PIPE,
             stderr=subprocess.STDOUT)

    stdout, stderr = result.communicate()

    print(stdout)
    print('-----')
    
    with open('pa2_arg_test/gold.txt', 'r') as f:
        gold = f.read()

    gold = ''.join(gold)

    out_dump = []
    for line in stdout.splitlines():
        if 'bfff' in line:
            out_dump.append(line+'\n')

    out_dump = ''.join(out_dump)

    return 100 if (gold.splitlines() == out_dump.splitlines()) else 0


if __name__ == '__main__':
    score = score_arg_passing("echo hello there 1 2 3 4 5")
    print("Score for pa2_phase_1: " + str(score))
