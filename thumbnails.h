#include <QFileIconProvider>
#include <QPixmap>
#include <QProcess>
#include <QImageReader>
#include <QTemporaryFile>
#include <iostream>

// Okay this file is a load of AI generated slop (the same as main.cpp really)

class ThumbnailProvider : public QFileIconProvider {
	public:
		QIcon icon(const QFileInfo &info) const override {
			static const QSize thumbnailSize(64, 64);

			if (info.isFile() && info.suffix().toLower() == "jpg" || 
					info.suffix().toLower() == "png") {

				QImageReader reader(info.absoluteFilePath());
				reader.setScaledSize(thumbnailSize);
				QImage img = reader.read();
				if (!img.isNull()) {
					return QIcon(QPixmap::fromImage(img));
				}
			}

			if (info.isFile() && info.suffix().toLower() == "mp4" || 
					info.suffix().toLower() == "mpeg" ||
					info.suffix().toLower() == "webm" ||
					info.suffix().toLower() == "mkv") {
				QTemporaryFile tmp(QDir::tempPath() + "/thumb-XXXXXX.png");
				tmp.setAutoRemove(false);  // Let us control cleanup
				qDebug() << info.absoluteFilePath();
				QProcess::execute("ffmpeg", { "-ss", "00:00:01", "-i", info.absoluteFilePath(), "-vframes", "1", "-vf", "scale=64:64", "/tmp/squivids.png", "-y" });

				qDebug() << tmp.fileName();
				QImageReader reader("/tmp/squivids.png");
				reader.setScaledSize(thumbnailSize);
				QImage img = reader.read();
				if (!img.isNull()) {
					return QIcon(QPixmap::fromImage(img));
				}
			}
			return QFileIconProvider::icon(info); // fallback to default
		}
};
