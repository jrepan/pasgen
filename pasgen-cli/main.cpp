#define _BSD_SOURCE
#include <unistd.h>
#include <iostream>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QCryptographicHash>
#include <QClipboard>

const int password_length = 30;
QCryptographicHash hash(QCryptographicHash::Sha3_224);

QString generate(QString password, QString page)
{
	hash.reset();
	hash.addData(password.toUtf8());
	hash.addData(page.toUtf8());

	return hash.result()
		.toBase64(QByteArray::OmitTrailingEquals)
		.replace('+',"").replace('/',"")
		.left(password_length);
}

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	QCommandLineParser parser;
	parser.addPositionalArgument("page", "Page name for what to generate the password");
	parser.process(a);

	QStringList argument = parser.positionalArguments();
	if (argument.length() != 1)
	{
		qFatal("Needs an argument.");
	}
	QString page = argument.first();

	char *password = getpass("Master password: "); //TODO: zeroise later

	QString generated = generate(password, page);
	QString check = generate(password, "check");

	qApp->clipboard()->setText(generated, QClipboard::Clipboard);
	qApp->clipboard()->setText(generated, QClipboard::Selection);

	std::cout << "Password: " << generated.toLocal8Bit().constData() << std::endl; //TODO: hide by default
	std::cout << "Checksum: " << check.toLocal8Bit().constData() << std::endl;

	return 0;
}
