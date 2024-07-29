
// idfyanai@gmail.com

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Tree.h"
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Tree<int, 3> ternaryTree;
    QGraphicsScene *scene;

    void displayTree();
    void drawNode(TreeNode<int>* node, QGraphicsScene *scene, int x, int y, int level);
};

#endif
