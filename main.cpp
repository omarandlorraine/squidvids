#include <QApplication>
#include <QListView>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

int main(int argc, char *argv[]) {
	    QApplication app(argc, argv);

    // Create file system model
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::homePath()); // Start at home directory
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); // Show files and folders

    // Create a list view and configure for grid
    QListView *view = new QListView;
    view->setModel(model);
    view->setRootIndex(model->index(QDir::homePath()));

    // Configure view to look like a thumbnail grid
    view->setViewMode(QListView::IconMode);
    view->setResizeMode(QListView::Adjust);
    view->setIconSize(QSize(64, 64)); // Thumbnail size
    view->setGridSize(QSize(100, 100));
    view->setSpacing(10);

	QObject::connect(view, &QListView::clicked, [&](const QModelIndex &index) {
			QString path = model->filePath(index);
			QFileInfo info(path);
			if (info.isDir()) {
				view->setRootIndex(model->index(path));
			} else {
				QDesktopServices::openUrl(QUrl::fromLocalFile(path));
			}
			});

    // Main window
    QWidget window;
    QVBoxLayout layout;
    layout.addWidget(view);
    window.setLayout(&layout);
    window.setWindowTitle("SquidVids");
    window.resize(800, 600);
    window.show();

    return app.exec();
}
