
// idfyanai@gmail.com

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    ternaryTree.add_root(1);
    TreeNode<int>* root = ternaryTree.get_root();
    ternaryTree.add_sub_node(root, 2);
    ternaryTree.add_sub_node(root, 3);
    ternaryTree.add_sub_node(root, 4);
    ternaryTree.add_sub_node(root->children[0], 5);
    ternaryTree.add_sub_node(root->children[0], 6);
    ternaryTree.add_sub_node(root->children[0], 7);
    ternaryTree.add_sub_node(root->children[1], 8);
    ternaryTree.add_sub_node(root->children[1], 9);
    ternaryTree.add_sub_node(root->children[1], 10);

    std::cout << "Hello, This is my visualized graphs implementation!" << std::endl;

    displayTree();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::displayTree() {
    scene->clear();
    if (ternaryTree.get_root()) {
        drawNode(ternaryTree.get_root(), scene, 400, 50, 0);
    }
}

void MainWindow::drawNode(TreeNode<int>* node, QGraphicsScene *scene, int x, int y, int level) {
    if (!node) return;

    QGraphicsTextItem *item = new QGraphicsTextItem(QString::number(node->value));
    item->setPos(x, y);
    scene->addItem(item);

    int childX = x - 100 * pow(2, -level);
    int childY = y + 50;

    for (TreeNode<int>* child : node->children) {
        if (child) {
            scene->addLine(x + 10, y + 20, childX + 10, childY, QPen(Qt::black));
            drawNode(child, scene, childX, childY, level + 1);
            childX += 200 * pow(2, -level);
        }
    }
}
