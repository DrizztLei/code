HEADERS       = glwidget.h \
                window.h \
    bmp.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
    bmp.cpp

RESOURCES     = textures.qrc

QT           += widgets

CXXFLAGS += gnu+=11

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/textures

INSTALLS += target
CONFIG += opengl
LIBS += -I/usr/include/opencv -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_cvv -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core
LIBS += -lGL -lGLU -lglut
