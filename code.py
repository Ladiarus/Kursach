import os
directory = os.getcwd()

f2 = open("code.txt", "w")
def rec (curr_dir, n):
    if n == 2:
        return
    for filename in os.listdir(curr_dir):
        full_filename = curr_dir + '\\' + filename
        print(full_filename)
        if filename.endswith(".cpp"):
            f = open(full_filename[0:-3] + 'h', "r")
            f2.write("/////" + filename[0:-3] + 'h' + '\n\n')
            f2.write(f.read() + '\n\n')
            f = open(full_filename, "r")
            f2.write("/////" + filename + '\n\n')
            f2.write(f.read() + '\n\n')
        if '.' not in filename:
            rec(full_filename, n+1)

rec(directory, 0)