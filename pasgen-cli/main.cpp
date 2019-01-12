#define _BSD_SOURCE
#include <unistd.h>
#include <iostream>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QClipboard>
#include "../common.h"

const int password_length = 30;

int main(int argc, char *argv[])
{
	QGuiApplication a(argc, argv);

	QCommandLineParser parser;
	QCommandLineOption option("visible", "Is generated password visible", "boolean", "false");
	parser.addPositionalArgument("page", "Page name for what to generate the password");
	parser.addOption(option);
	parser.process(a);

	QStringList argument = parser.positionalArguments();
	if (argument.length() != 1)
	{
		qFatal("Needs an argument.");
	}
	QString page = argument.first();

	QSettings settings("pasgen");

	char *password = getpass("Master password: ");

	QString generated = generate(password, page, settings);
	QString check = generate(password, "check", settings);

	qApp->clipboard()->setText(generated, QClipboard::Clipboard);
	qApp->clipboard()->setText(generated, QClipboard::Selection);

	std::cout << "Password has been copied to clipboard" << std::endl;
	if (parser.value(option) == "true")
		std::cout << "Password: " << generated.toLocal8Bit().constData() << std::endl;
	else
		std::cout << "Password is hidden by default, use --visible true to show." << std::endl;
	std::cout << "Checksum: " << check.toLocal8Bit().constData() << std::endl;

	memset(password, 0, strlen(password));
	return 0;
}
