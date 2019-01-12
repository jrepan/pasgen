#include "common.h"
#include <QDataStream>
#include <QCryptographicHash>
#include <QTextStream>

const int default_password_length = 30;

QString generate(QString password, QString page, QSettings &settings)
{
	// Load the secret
	QString secret = settings.value("secret").toString();
	if (secret.isEmpty())
		settings.setValue("secret", "");

    // Get password length
    int password_length = default_password_length;
    if (page.startsWith("len") || page.startsWith("pin"))
    {
        QTextStream stream(&page);
        stream.seek(3); // 3 = strlen("len" or "pin")
        stream >> password_length;
        if (stream.status() != QTextStream::Ok)
            password_length = default_password_length;
    }

	// Generate hash
	QCryptographicHash hash(QCryptographicHash::Sha3_224);
    hash.addData(password.toUtf8());
    hash.addData(page.toUtf8());
	hash.addData(secret.toUtf8());

	// Convert the hash to string
    QByteArray raw = hash.result();
    if (page.startsWith("pin"))
    {
        unsigned int raw_nr;
        QDataStream(raw) >> raw_nr;
        return QString("%1")
			.arg(raw_nr)
			.right(password_length);
    }
    return raw
		.toBase64(QByteArray::OmitTrailingEquals)
		.replace('+', "")
		.replace('/', "")
		.left(password_length);
}
