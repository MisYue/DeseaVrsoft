#include "WarheadMainCtrlWnd.h"
#include "GlobalDataWrap.h"
#include <QtWidgets>
#include <BasicTool/expandqtcore.h>
#include <BasicTool/expandqtgui.h>
#include <DBAccess/DBConn.h>
#include <TaskDBAccess/taskdbaccess.h>
#include <DBMUi/DBConnDlg.h>
#include <osg/ApplicationUsage>
#include <osg/ArgumentParser>
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

#if QT_VERSION < 0x050000
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
	QTranslator translator;
	translator.load("qt_zh_CN.qm");
	a.installTranslator(&translator);
	QFile file(":/root/css");
	file.open(QFile::ReadOnly);
	QString styleSheet = ExpandQtCore::fromGBK(file.readAll().data());
	a.setStyleSheet(styleSheet);

	//���������в���
	//--taskguid=123 --dbname=myorcl --user=system --pwd=myorcl --host=localhost --port=1521
	std::string task_guid;
	std::string db_name;
	std::string user;
	std::string pwd;
	std::string host;
	std::string port;
	std::string global_data_file("globaldata.txt");

	osg::ArgumentParser arguments(&argc,argv);
	arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
	arguments.getApplicationUsage()->setDescription(arguments.getApplicationName() + " ���Դ򿪡��½�ս����������������������");
	arguments.getApplicationUsage()->setCommandLineUsage(arguments.getApplicationName()+" [Option1] [Option2] ... ");
	arguments.getApplicationUsage()->addCommandLineOption("--taskguid", " ����GUID");
	arguments.getApplicationUsage()->addCommandLineOption("--dbname", " ���ݿ�����");
	arguments.getApplicationUsage()->addCommandLineOption("--user", " ���ݿ��û�");
	arguments.getApplicationUsage()->addCommandLineOption("--pwd", " ���ݿ�����");
	arguments.getApplicationUsage()->addCommandLineOption("--host", " ���ݿ�����");
	arguments.getApplicationUsage()->addCommandLineOption("--port", " ���ݿ�˿�");
	arguments.getApplicationUsage()->addCommandLineOption("--globaldatafile", "���������ļ�");


	unsigned int helpType = 0;
	if ((helpType = arguments.readHelpType()))
	{
		arguments.getApplicationUsage()->write(std::cout, helpType);
		return 1;
	}


	while (arguments.read("--taskguid", task_guid)) ;
	while (arguments.read("--dbname", db_name)) ;
	while (arguments.read("--user", user)) ;
	while (arguments.read("--pwd", pwd)) ;
	while (arguments.read("--host", host)) ;
	while (arguments.read("--port", port)) ;
	while (arguments.read("--globaldatafile", global_data_file)) ;


	//�������ݿ�����
	DBConn db_conn;
	db_conn.set_db_name(QString::fromStdString(db_name));
	db_conn.set_user(QString::fromStdString(user));
	db_conn.set_pwd(QString::fromStdString(pwd));
	db_conn.set_host_name(QString::fromStdString(host));
	db_conn.set_port(QString::fromStdString(port).toInt());
	db_conn.set_driver_type("QOCI");
	db_conn.Connect();
	if(!db_conn.IsValid())
	{
		DBConnDlg conn_dlg(&db_conn);
		bool ok = (QDialog::Accepted == conn_dlg.exec());
		//�����а�������GUID��ȡ���������ݿ�ʱ���˳�����
		if(task_guid.size() > 0 && !ok)
		{
			qDebug() << ExpandQtCore::fromGBK("ȡ���������ݿ⣬�˳�����...");
			return 1;
		}
	}
	//ȫ�����ݳ�ʼ��
	GlobalDataWrap::instance().Init(QString::fromStdString(global_data_file));
	//�������ݿ����Ӷ���
	GlobalDataWrap::instance().set_db_conn(&db_conn);
	//��ѯ�����Ƿ����
	if(task_guid.size() > 0)
	{
		//��ָ������������������ݿ�
		Q_ASSERT(db_conn.IsValid());
		TaskDBAccess task_db(&db_conn);
		if(!task_db.IsExist(QString::fromStdString(task_guid)))
		{
			ExpandQtGui::critical(0, ExpandQtCore::fromGBK("����"), ExpandQtCore::fromGBK("����'%1'�����ڣ����˳�����").arg(task_guid.c_str()));
			return 1;
		}
	}
	WarheadMainCtrlWnd w(QString::fromStdString(task_guid));
	w.showMaximized();
	return a.exec();
}





