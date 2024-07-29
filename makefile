
CXX = g++
CXXFLAGS = -Wall -std=c++11

QT_PATH = /usr/local/Qt-5.15.2

INCLUDE_PATH = $(QT_PATH)/include
LIB_PATH = $(QT_PATH)/lib

QT_MODULES = Widgets

QT_LIBS = $(foreach module, $(QT_MODULES), -lQt5$(module))

SOURCES = main.cpp mainwindow.cpp Tree.cpp
OBJECTS = $(SOURCES:.cpp=.o)

TARGET = TreeVisualizer

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(LIB_PATH) $(QT_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_PATH) -I$(INCLUDE_PATH)/QtWidgets -I$(INCLUDE_PATH)/QtCore -I$(INCLUDE_PATH)/QtGui -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)
