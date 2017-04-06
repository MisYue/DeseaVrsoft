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

	//处理命令行参数
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
	arguments.getApplicationUsage()->setDescription(arguments.getApplicationName() + " 可以打开、新建战斗部，并进行威力分析。");
	arguments.getApplicationUsage()->setCommandLineUsage(arguments.getApplicationName()+" [Option1] [Option2] ... ");
	arguments.getApplicationUsage()->addCommandLineOption("--taskguid", " 任务GUID");
	arguments.getApplicationUsage()->addCommandLineOption("--dbname", " 数据库名称");
	arguments.getApplicationUsage()->addCommandLineOption("--user", " 数据库用户");
	arguments.getApplicationUsage()->addCommandLineOption("--pwd", " 数据库密码");
	arguments.getApplicationUsage()->addCommandLineOption("--host", " 数据库主机");
	arguments.getApplicationUsage()->addCommandLineOption("--port", " 数据库端口");
	arguments.getApplicationUsage()->addCommandLineOption("--globaldatafile", "数据配置文件");


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


	//测试数据库连接
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
		//命令行包含任务GUID，取消连接数据库时，退出程序
		if(task_guid.size() > 0 && !ok)
		{
			qDebug() << ExpandQtCore::fromGBK("取消连接数据库，退出程序...");
			return 1;
		}
	}
	//全局数据初始化
	GlobalDataWrap::instance().Init(QString::fromStdString(global_data_file));
	//保存数据库连接对象
	GlobalDataWrap::instance().set_db_conn(&db_conn);
	//查询任务是否存在
	if(task_guid.size() > 0)
	{
		//若指定任务，则必须连接数据库
		Q_ASSERT(db_conn.IsValid());
		TaskDBAccess task_db(&db_conn);
		if(!task_db.IsExist(QString::fromStdString(task_guid)))
		{
			ExpandQtGui::critical(0, ExpandQtCore::fromGBK("错误"), ExpandQtCore::fromGBK("任务'%1'不存在，将退出程序！").arg(task_guid.c_str()));
			return 1;
		}
	}
	WarheadMainCtrlWnd w(QString::fromStdString(task_guid));
	w.showMaximized();
	return a.exec();
}





