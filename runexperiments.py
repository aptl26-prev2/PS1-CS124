# Usage: run `python3 runexperiments.py` to generate MST output for D=2, 3, 4. N=2,...,26

import os

os.system('make all')
for n in range(1, 19):
    N = 2**n 
    command = './randmst ' + str(N) + ' 5 ' + str(0)
    # print(command)
    os.system(command)
    
for D in range(2, 5):
    for n in range(1, 19):
        N = 2**n 
        command = './randmst ' + str(N) + ' 5 ' + str(D)
        # print(command)
        os.system(command)