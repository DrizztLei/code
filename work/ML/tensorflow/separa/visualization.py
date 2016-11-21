import test


def process_data_label():
    test.get_file_name()
    SIZE = 828
    IMAGE_SIZE = 128
    NUM_CHANNEL = 3
    LABEL = 6
    data, label = test.parse_data(SIZE=SIZE, IMAGE_SIZE=IMAGE_SIZE, NUM_CHANNEL=NUM_CHANNEL, LABEL=LABEL)
    control = 1

    process_data = test.approximate_normalization(data)

    """
    temp = test.cv.imread("/home/visualization/work/ML/tensorflow/separa/png/worldmap_PCA_data_cls4.png")
    print temp.shape
    control_shape = temp.shape
    for x in xrange(control_shape[0]):
        for y in xrange(control_shape[1]):
            R = temp[x, y, 0]
            G = temp[x, y, 1]
            B = temp[x, y, 2]

            if R + G + B == 255:
                print temp[x, y]

    test.mat_show(temp)
    print ("done")
    raw_input()
    """

    return process_data, label

data, label = process_data_label()
temp = data[-1]
for x in range(-100,100):
    if x in data[1]:
        print x
