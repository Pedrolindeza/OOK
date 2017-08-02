import glob
import subprocess
import os, sys

#Folder
#   tests
#   expected
#   ook

alltests = glob.glob("tests/*.ook")
alltests.sort();
subprocess.call(["make", "clean"], cwd="./ook")
subprocess.call(["make"], cwd="./ook")
subprocess.call(["rm", "-f", "*.txt"], cwd="./results/")
subprocess.call(["rm", "-f", "*.asm"], cwd="./results/asm/")
subprocess.call(["rm", "-f", "*"], cwd="./results/exe/")
subprocess.call(["rm", "-f", "*.o"], cwd="./results/o/")



i = 0
tests_passed = 0;
while i < len(alltests):
	result = alltests[i].replace("tests","results/asm").replace(".ook",".asm")
	test = alltests[i]
	i += 1
	subprocess.call(["./ook/ook", test, "-o", result])
	subprocess.call(["yasm", "-felf32", result, "-o", test.replace("tests","results/o").replace(".ook",".o")])
	subprocess.call(["ld", "-melf_i386" ,"-o", test.replace("tests","results/exe").replace(".ook",""), test.replace("tests","results/o").replace(".ook",".o"), "-lrts"])

	with open("./" + test.replace("tests","results").replace(".ook",".txt"), 'a+') as file:
		subprocess.call(["./" + test.replace("tests","results/exe").replace(".ook","")], stdout = file)


	my_file = open("./" + test.replace("tests","results").replace(".ook",".txt"), 'r')
	david_file = open(test.replace("tests","./expected").replace(".ook",".out"), 'r')


	david_output =  my_file.read().strip(" \n\r\t")
	my_output = david_file.read().strip(" \n\r\t")

	my_file.close()
	david_file.close()

	if (david_output == my_output):
		tests_passed += 1
	else:
		subprocess.call(["colordiff", test.replace("tests","./expected").replace(".ook",".out"), test.replace("tests","./results").replace(".ook",".txt")])






	#subprocess.call(["diff", test.replace("tests","./expected").replace(".ook",".out"), test.replace("tests","./results").replace(".ook",".txt")])
	#
	#input() # para esperar
	#ld -o examples/ex1 examples/ex1.o -lrts

print(str(tests_passed/len(alltests) * 100) + "% tests passed")