import cv2 as cv
import numpy as np
import tensorflow as tf

DIR_PATH=""
FIG_PATH=""
EVAL_PATH=""


def get_figure():
    print ("figure")


def get_picture():
    print ("get picture mat")


def read_csv(filename):
    print ("reading the csv file")
    info = np.loadtxt(filename, dtype=int, delimiter=',')

    label_1 = info[...,0]
    label_2 = info[...,1]
    label_3 = info[...,2]


def main(argv=None):
    print ("main call")


if __name__ == '__main__':
    tf.app.run()