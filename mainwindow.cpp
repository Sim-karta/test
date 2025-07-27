#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db/users.db");

    if (db.open()) {
        ui->statusbar->showMessage("Вы успешно подключились к базе данных: " + db.databaseName());

        model = new QSqlTableModel(this, db);
        model->setTable("Users");
        model->select();
        model->setHeaderData(1, Qt::Horizontal, "Фамилия", Qt::DisplayRole);
        model->setHeaderData(2, Qt::Horizontal, "Имя", Qt::DisplayRole);
        model->setHeaderData(3, Qt::Horizontal, "Отчество", Qt::DisplayRole);
        model->setHeaderData(4, Qt::Horizontal, "Отдел №", Qt::DisplayRole);

        ui->tableView->setModel(model);

        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setColumnHidden(0, true);
    } else {
        ui->statusbar->showMessage("При подключении к базе данных произошла ошибка: " + db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{   
    db.close();
    delete ui;
}

void MainWindow::on_addBtn_clicked() {
    model->insertRow(model->rowCount());
}

void MainWindow::on_tableView_clicked(const QModelIndex &i) {
    currentRow = i.row();
}

void MainWindow::on_refBtn_clicked() {
    model->select();
    ui->tableView->selectRow(currentRow);
}

void MainWindow::on_delBtn_clicked() {
    model->removeRow(currentRow);
    model->select();
}