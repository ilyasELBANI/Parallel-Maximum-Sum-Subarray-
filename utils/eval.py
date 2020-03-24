from subprocess import STDOUT, check_output, TimeoutExpired, CalledProcessError
from os import listdir
from os.path import isfile, join
import subprocess
import time,sys

minn, maxx = 1,5
if len(sys.argv) >= 2 :
    minn = int(sys.argv[1])
    maxx = minn
if len(sys.argv) >= 3 :
    maxx = int(sys.argv[2])

dataFolder="data/"
binFolder="bin/"
srcFolder="src/"

datasets=[]

for i in range(minn,maxx+1):
    datasets.append(i)
    

def runDataset(name, i) :
    output=""
    try:
        print("File Number :", i, "\t" ) 
        output = subprocess.check_output([binFolder+name, dataFolder+"/test"+str(i)], stderr=STDOUT,universal_newlines=True).strip().replace('\n', '')
        # print("--- %s seconds ---" % (time.time() - start_time))
        # print(output)
        with open(dataFolder+"/result"+str(i)) as f:
            for line in f:
                # print(line)
                # print(output)
                # print(ord(line[-1]))
                # print(len(output))
                return str(line.replace('\n', '')==output)
    except  CalledProcessError as e :
        #we still have to check the output because
        #some student call returns non 0 value in case of success !
        output=e.output.strip().replace('\n', '')
        #print(output)
        if (e.returncode < 0) :
            return "Error Code"
        with open(dataFolder+"/result"+str(i)) as f:
            for line in f:
                return str(line.replace('\n', '')==output)
    except (TimeoutExpired) as e :
        return "TimeoutError"



def runProject(name) :
    result=""
    for d in datasets :
        result = result + ";" + runDataset(name, d)
    return result


def runAllProjects() :
    onlyfiles = [f for f in listdir(binFolder) if isfile(join(binFolder, f))]
    for f in onlyfiles:
        print(runProject(f))

def compileAndRunProjects() :
    onlyfiles = [f for f in listdir(srcFolder) if isfile(join(srcFolder, f))]
    for f in onlyfiles:
        name=binFolder + f[:-2]
        print(">",name)
        output = subprocess.check_output(["gcc","-std=c99", "-o" , name,  srcFolder+ f ,"-lm", "-fopenmp"], stderr=STDOUT, universal_newlines=True).strip().replace('\n', '')
        print(output)
        resultCompilation=(output=="")
        print(f[:-2] + ";" + str(resultCompilation)  + runProject(f[:-2]))

start_time = time.time()
compileAndRunProjects()
print("--- %s seconds ---" % (time.time() - start_time))
