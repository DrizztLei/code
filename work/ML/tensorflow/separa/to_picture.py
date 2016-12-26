import numpy as np
import sys
import matplotlib.pyplot as plt
import os

color = {0: 'b', 1: 'g', 2: 'r', 3: 'c', 4: 'm', 5: 'y', 6: 'k', 7: 'w'}

argc = len(sys.argv)
if argc < 3:
    sys.exit(-1)
elif argc == 4:
    filename = sys.argv[1]
    output_label = int(sys.argv[2])
    score = int(sys.argv[3])
else:
    filename = sys.argv[1]
    print (sys.argv[2])
    output_label = int(sys.argv[2])
    score = -1

info = np.loadtxt(fname=filename, delimiter=',')
if info.shape[1] != 3:
    print ("not 2 dimension.")
    sys.exit(-1)
point_label = info[..., 0:1]
point_label = np.reshape(point_label, [-1])

x = info[..., 1:2]
y = info[..., 2:3]

if 0 in point_label:
    index = np.argmax(point_label)
    NUMBER = point_label[index]
    NUMBER += 1
else:
    index = np.argmax(point_label)
    NUMBER = point_label[index]

NUMBER = int(NUMBER)

index_max_x = np.argmax(x)
index_min_x = np.argmin(x)
index_max_y = np.argmax(y)
index_min_y = np.argmin(y)

arg_max_x = x[index_max_x]
arg_min_x = x[index_min_x]
arg_max_y = y[index_max_y]
arg_min_y = y[index_min_y]

if arg_min_x < 0:
    x += np.abs(arg_min_x)
if arg_min_y < 0:
    y += np.abs(arg_min_y)

for control_color in range(1, NUMBER + 1):
    if control_color != output_label:
        continue
    figure = plt.figure("SPARSE IMAGE", figsize=[7.2, 7.2])
    size = point_label.shape[0]

    for index in range(size):
        out = point_label[index]
        if int(out) == int(control_color):
            # temp = color[out]
            # mark_color = temp
            coor_x = x[index]
            coor_x = np.array(coor_x)
            coor_y = y[index]
            coor_y = np.array(coor_y)
            plt.scatter(coor_x, coor_y, color='r')

        else:
            coor_x = x[index]
            coor_x = np.array(coor_x)
            coor_y = y[index]
            coor_y = np.array(coor_y)

            plt.scatter(coor_x, coor_y, color='k')

    print ("file name : %s" % filename)
    print ("control class : %d" % output_label)
    if score != -1:
        print ("score : %d" % score)
    else:
        score = int(raw_input("score not found, show me your score : \n"))
    # plt.show()
    output_path  = filename
    output_path = output_path.replace(".csv", "_CLS_" + str(output_label) + ".png")
    figure.savefig(output_path)
    print ("save the %s " % output_path)