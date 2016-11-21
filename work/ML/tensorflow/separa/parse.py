import cv2 as cv
import numpy as np
import tensorflow as tf
import os as os
import math
import convolutional_version_2 as conv

DIR_PATH = "/home/visualization/work/ML/tensorflow/separa/"
FIG_PATH = DIR_PATH + "EUROVIS_figures/"
NEW_PATH = DIR_PATH + "EUROVIS_new/"
PNG_PATH = DIR_PATH + "png/"
CSV_FILE = "/home/visualization/work/ML/tensorflow/separa/RESULTS_EUROVIS2015.csv"

global FILE
global TRAIN_DATA
global TRAIN_LABEL


def get_figure():
    info = os.listdir(FIG_PATH)
    return info


def get_csv():
    info = os.listdir(NEW_PATH)
    return info


def read_csv(filename):
    info = np.loadtxt(filename, dtype=str, delimiter=",")
    return info


def show_csv_info():
    info = get_csv()
    for x in xrange(len(info)):
        data_list = read_csv(NEW_PATH + info[x])
        print (data_list.shape)


def image_show(filename):
    img = cv.imread(filename)
    print (filename)
    # time.sleep(10)

    window_name = "CV_IMAGE"
    cv.namedWindow(winname=window_name)

    while True:
        cv.imshow(winname=window_name, mat=img)
        character = cv.waitKey(100)
        if character == '\0x1b':  # for waiting the 'ESC' to excape
            break


def real_csv():
    info = np.loadtxt(fname=CSV_FILE, dtype=str, delimiter=",")
    print (info)


def view_class(index, RATE=830):
    info = read_csv(CSV_FILE)
    SELECT = index
    LABEL = (info[0][SELECT])

    NUM = info.shape[0]
    SELECT_NUM = (NUM // RATE)
    INFO = info[::SELECT_NUM,SELECT]
    INFO = INFO[1::]

    if type(INFO[0]) == str:
        INFO = INFO.astype(dtype=np.int64)

    RETURN_VALUE = ""
    RETURN_VALUE += str(LABEL)
    RETURN_VALUE += str(INFO)
    RETURN_VALUE = RETURN_VALUE.replace('[', ' ')
    RETURN_VALUE = RETURN_VALUE.replace(']', ' ')
    temp = list(RETURN_VALUE)

    return RETURN_VALUE


def compare():
    A = view_class(4)
    B = view_class(5)
    count = 0

    A = A.replace(' ', '')
    B = B.replace(' ', '')

    A = list(A)
    B = list(B)
    A = A[6:]
    B = B[6:]

    for x in xrange(len(A)):
        if A[x] == B[x]:
            count += 1

    print ("result for %f" % (float(count)/ len(A)))


def class_1():
    temp = (view_class(0))
    out = temp.split(' ')
    a = np.array(out)
    if a[len(a)-1] == '':
        a = a[1:len(a)-1]
    return a


def get_data(index=0, RATE=830):
    temp = (view_class(index, RATE))
    out = temp.split(' ')
    a = np.array(out)
    if a[len(a)-1] == '':
        a = a[1:len(a)-1]
    for x in xrange(len(a)):
        a[x] = str(a[x]).replace('\'', "")
        a[x] = str(a[x]).replace('\n', "")
    return a


def get_label(index=0, RATE=830):
    info = read_csv(CSV_FILE)
    return info[0, index]


def show_class():
    print (get_label(3))
    print (get_data(3)[0:5])
    print (get_label(0))
    print (get_data(0)[0:5])


def sum_check():
    data = get_data(3)
    arg = data.argmax()
    filename = get_data(0)
    print filename[arg-8:arg+3]
    print data[arg-8:arg+3]
    # print (data[arg])
    # print (get_data(0)[arg])


def combine(file_name, class_num):
    name = ""
    file_name = str(file_name)
    try:
        position = file_name.index(".csv")
        name = file_name[0:position] + "_cls" + class_num + ".png"
    except:
        name = ""
    return name


def test():
    get_file_name()


def get_file_name():
    file_name_data = get_data(0)
    file_name_num = get_data(3)

    global FILE
    FILE = []

    for x in xrange(len(file_name_data)):
        file_name = combine(file_name_data[x], file_name_num[x])
        if file_name != "":
            FILE.append(file_name)


def parse_data():

    global TRAIN_LABEL
    global TRAIN_DATA

    TRAIN_DATA = np.ndarray(shape=[conv.SIZE, conv.IMAGE_SIZE, conv.IMAGE_SIZE, conv.NUM_CHANNEL])

    TRAIN_LABEL = get_data(5)
    TRAIN_LABEL = TRAIN_LABEL[0:len(TRAIN_LABEL)-1]
    RETURN_TRAIN_LABEL = np.zeros([conv.SIZE, conv.LABEL])

    for x in xrange(len(FILE)):
        mat = cv.imread(filename=PNG_PATH + FILE[x])
        # print ("clean")
        # mat = img_clean(mat)
        gray = mat[60:645, 65:685]
        temp = cv.resize(gray, (conv.IMAGE_SIZE, conv.IMAGE_SIZE))
        temp = np.reshape(a=temp, newshape=[conv.IMAGE_SIZE, conv.IMAGE_SIZE, conv.NUM_CHANNEL])
        a = temp.astype(np.float32)
        b = img_rotate(a, 90)
        c = img_rotate(a, 180)
        d = img_rotate(a, 270)
        TRAIN_DATA[x * 4] = a
        TRAIN_DATA[x * 4 + 1] = b
        TRAIN_DATA[x * 4 + 2] = c
        TRAIN_DATA[x * 4 + 3] = d
        RETURN_TRAIN_LABEL[x * 4][TRAIN_LABEL[x]] = 1
        RETURN_TRAIN_LABEL[x * 4 + 1][TRAIN_LABEL[x]] = 1
        RETURN_TRAIN_LABEL[x * 4 + 2][TRAIN_LABEL[x]] = 1
        RETURN_TRAIN_LABEL[x * 4 + 3][TRAIN_LABEL[x]] = 1
    return TRAIN_DATA, RETURN_TRAIN_LABEL


def img_show(img):
    cv.namedWindow("IMG")
    while True:
        cv.imshow("IMG", img)
        character = cv.waitKey(100)
        if int(character) == 'a': break


def img_clean(img):
    return_matrix = np.zeros([img.shape[0], img.shape[1], 1])
    for x in xrange(img.shape[0]):
        for y in xrange(img.shape[1]):
            if img[x,y,0] + img[x,y,1] == 0:
                return_matrix[x,y,0] = -1
            elif img[x,y,0] + img[x,y,1] == 255:
                return_matrix[x,y,0] = 1
    return return_matrix


def img_rotate(img, angle):
    height = img.shape[0]
    width = img.shape[1]
    if angle % 180 == 0:
        scale = 1
    elif angle % 90 == 0:
            scale = float(max(height, width)) / min(height,width)
    else :
        scale = math.sqrt(pow(height,2) + pow(width,2))/min(height,width)
        rotateMat = cv.getRotationMatrix2D((width/2, height/2), angle, scale)
        rotageImg = cv.warpAffine(img, rotateMat, (width, height))
        return rotageImg


if __name__ == '__main__':
    tf.app.run()
