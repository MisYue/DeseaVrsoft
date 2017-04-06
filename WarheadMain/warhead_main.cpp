
#include "warhead_main.h"
#include "ui_warheadmain.h"
#include "unit_dialog.h"
#include "material_dialog.h"
#include "ui_save_set.h"
#include "InputDialog.h"
#include <tool/global_data.h>
#include <tool/tool.h>
#include <WarheadDraw/warhead_draw_wnd.h>
#include <WarheadModelData/warhead_model.h>
#include <WarheadModelData/warhead_layer.h>
#include <WarheadModelData/warhead_section.h>
#include <WarheadReadWrite/warhead_write.h>
#include <WarheadReadWrite/warhead_read.h>

WarheadMain::WarheadMain(const QString& model_file, QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, ui(new Ui::WarheadMainClass)
	, model_(0)
	, model_file_(model_file)
{
	ui->setupUi(this);
	setWindowTitle(qApp->applicationName());

	UnitDialog unit_dialog;
	if(QDialog::Rejected == unit_dialog.exec())
		exit(0);
	GlobalData& global_data = GlobalData::instance();
	QString title_text = windowTitle() + GBK2Unicode("-单位系统 [") + global_data.GetLengthUnit() + ", " + global_data.GetMassUnit() + ", " + global_data.GetTimeUnit() + "]";
	setWindowTitle(title_text);
	TryOpenModel(model_file_);

	draw_wnd_ = new WarheadDrawWnd(model_, WarheadDrawWnd::kEdit);

	setCentralWidget(draw_wnd_);

	ui->action_save_as_file->setEnabled(false);

	connect(ui->action_new, SIGNAL(triggered()), this, SLOT(on_new()));
	connect(ui->action_save, SIGNAL(triggered()), this, SLOT(on_save()));
	connect(ui->action_save_as_file, SIGNAL(triggered()), this, SLOT(on_save_as()));
	connect(ui->action_open_from_file, SIGNAL(triggered()), this, SLOT(on_open()));
	connect(ui->action_charge_material, SIGNAL(triggered()), this, SLOT(on_charge_material()));
	connect(ui->action_metal_material, SIGNAL(triggered()), this, SLOT(on_metal_material()));

}

WarheadMain::~WarheadMain()
{
	JudgeSave();
	delete ui;
}

void WarheadMain::on_new()
{
	QStringList items;
	items << GBK2Unicode("杀爆弹")/* << GBK2Unicode("侵爆弹")*/;
	//bool ok;
	//QString item = QInputDialog::getItem(this, GBK2Unicode("战斗部类型"),
	//	GBK2Unicode("类型"), items, 0, false, &ok);
	CInputDialog input_dialog;
	QComboBox* types_inputer = new QComboBox(&input_dialog);
	QLineEdit* name_inputer = new QLineEdit(&input_dialog);
	types_inputer->addItems(items);
	name_inputer->setText("New Warhead");
	input_dialog.AddRow(GBK2Unicode("战斗部类型"), types_inputer);
	input_dialog.AddRow(GBK2Unicode("名称"), name_inputer);

	if(input_dialog.exec() == QDialog::Accepted)
	{
		QString type = types_inputer->currentText();
		QString name = name_inputer->text();

		JudgeSave();
		model_file_.clear();
		ui->action_save_as_file->setEnabled(false);

		model_ = new WarheadModel;
		//?目前只有杀爆弹
		model_->set_type(kKill);
		model_->set_name(name);
		Bit_2DCSWithExpAndUS& cs = model_->get_cs();
		cs.Set_Initial(cs.Get_2DCSWithExplain(), GlobalData::instance().get_unit_system());
		draw_wnd_->set_model(model_);
	}
}

void WarheadMain::on_save()
{
	bool out_csv = SaveCheck();

	int destrete_num = 200;
	if(SaveSet(destrete_num))
	{
		QString file_name = model_file_;
		if(file_name.isEmpty())
			file_name = QFileDialog::getSaveFileName(this, GBK2Unicode("保存"), QString(), GBK2Unicode("战斗部模型 (*.whd)"));
		if(!file_name.isEmpty())
		{
			if(file_name.right(4) != ".whd")
				file_name += ".whd";
			WarheadWrite writer(model_);
			if(!writer.WriteXMLFile(file_name, destrete_num))
			{
				QMessageBox box(this);
				box.setIcon(QMessageBox::Warning);
				box.setWindowTitle(GBK2Unicode("错误"));
				box.addButton(GBK2Unicode("确定"), QMessageBox::AcceptRole);
				box.setText(GBK2Unicode("保存XML模型失败！"));
				box.exec();
			}
			if(out_csv)
			{
				QString csv_file_name = file_name.left(file_name.size()-4);
				csv_file_name += ".csv";
				if(!writer.WriteCSVFile(csv_file_name))
				{
					QMessageBox box(this);
					box.setIcon(QMessageBox::Warning);
					box.setWindowTitle(GBK2Unicode("错误"));
					box.addButton(GBK2Unicode("确定"), QMessageBox::AcceptRole);
					box.setText(GBK2Unicode("保存CSV威力基础文件失败！"));
					box.exec();
				}
			}
#ifdef _DEBUG
			//保存svg及三维模型
			{
				QString struct_file_name = file_name.left(file_name.size()-4);
				draw_wnd_->SaveStructure(struct_file_name);
			}
#endif
			model_file_ = file_name;
			ui->action_save_as_file->setEnabled(true);
			QMessageBox box(this);
			box.setIcon(QMessageBox::Information);
			box.setWindowTitle(GBK2Unicode("信息"));
			box.addButton(GBK2Unicode("确定"), QMessageBox::AcceptRole);
			box.setText(GBK2Unicode("保存成功！"));
			box.exec();
		}
	}

}

void WarheadMain::on_save_as()
{
	bool out_csv = SaveCheck();

	int destrete_num = 200;
	if(SaveSet(destrete_num))
	{
		QString file_name = QFileDialog::getSaveFileName(this, GBK2Unicode("另存为"), QString(), GBK2Unicode("战斗部模型 (*.whd)"));
		if(!file_name.isEmpty())
		{
			if(file_name.right(4) != ".whd")
				file_name += ".whd";
			WarheadWrite writer(model_);
			if(!writer.WriteXMLFile(file_name, destrete_num))
			{
				QMessageBox box(this);
				box.setIcon(QMessageBox::Warning);
				box.setWindowTitle(GBK2Unicode("错误"));
				box.addButton(GBK2Unicode("确定"), QMessageBox::AcceptRole);
				box.setText(GBK2Unicode("保存XML模型失败！"));
				box.exec();
			}
			if(out_csv)
			{
				QString csv_file_name = file_name.left(file_name.size()-4);
				csv_file_name += ".csv";
				if(!writer.WriteCSVFile(csv_file_name))
				{
					QMessageBox box(this);
					box.setIcon(QMessageBox::Warning);
					box.setWindowTitle(GBK2Unicode("错误"));
					box.addButton(GBK2Unicode("确定"), QMessageBox::AcceptRole);
					box.setText(GBK2Unicode("保存CSV威力基础文件失败！"));
					box.exec();
				}
			}
#ifdef _DEBUG
			//保存svg及三维模型
			{
				QString struct_file_name = file_name.left(file_name.size()-4);
				draw_wnd_->SaveStructure(struct_file_name);
			}
#endif
			QMessageBox box(this);
			box.setIcon(QMessageBox::Information);
			box.setWindowTitle(GBK2Unicode("信息"));
			box.addButton(GBK2Unicode("确定"), QMessageBox::AcceptRole);
			box.setText(GBK2Unicode("另存成功！"));
			box.exec();
		}
	}
	
}

bool WarheadMain::SaveCheck()
{
	bool result = false;
	if(model_)
	{
		if(model_->get_fire_points().size() > 0 && model_->get_sections().size() > 0)
		{
			result = true;
		}
		else if(model_->get_sections().size() < 1)
		{
			//QMessageBox::warning(this, GBK2Unicode("保存检查"), GBK2Unicode("请至少添加一段"));
		}
		else if(model_->get_fire_points().size() < 1)
		{
			//QMessageBox::warning(this, GBK2Unicode("保存检查"), GBK2Unicode("请至少设置一个起爆点"));
		}
	}
	return result;
}
bool WarheadMain::SaveSet(int& destrete_num)
{
	bool needed_input = false;
	foreach(WarheadSection* section, model_->get_sections())
	{
		QList<WarheadLayer*> layers = section->get_layers();
		QList<WarheadLayer*>::iterator iter = layers.begin();
		if(++iter != layers.end())
		{
			if((*iter)->get_layer_type() == kShell)
			{
				needed_input = true;
				break;
			}
		}
	}
	QDialog dialog;
	Ui::SaveSet ui;
	ui.setupUi(&dialog);
	if(!needed_input)
	{	
		ui.widget_destrete->hide();
	}
	Bit_2DCSWithExplain cs_explain = model_->get_cs().Get_2DCSWithExplain();
	Bit_2DCS cs_2d = cs_explain.Get_CS();
	Bit_Point2D origin = cs_2d.Get_OriginalPoint();
	Bit_Point2D x_v = cs_2d.Get_XAixVector();
	Bit_UnitSystem us = GlobalData::instance().get_unit_system();
	ui.doubleSpinBox->setDecimals(GlobalData::instance().GetLengthPrecisionHint());
	ui.doubleSpinBox->setSuffix(GlobalData::instance().GetLengthUnit());
	ui.doubleSpinBox->setMinimum(0);
	ui.doubleSpinBox->setValue(origin.Get_x());
	double charge_length = model_->get_character_data().length;
	if(WarheadEndCap* end_cap = model_->get_left_end_cap())
	{
		charge_length -= end_cap->get_length();
	}
	if(WarheadEndCap* end_cap = model_->get_right_end_cap())
	{
		charge_length -= end_cap->get_length();
	}
	ui.spinBox->setValue(charge_length * GlobalData::instance().get_unit_system().Get_LengthCoefficient());

	if(x_v.Get_x() == 1 && x_v.Get_y() == 0)
	{
		ui.comboBox->setCurrentIndex(0);
	}
	else
	{
		ui.comboBox->setCurrentIndex(1);
	}

	ui.textEdit->setText(GBK2Unicode(cs_explain.Get_Explain()));

	if(QDialog::Accepted == dialog.exec())
	{
		destrete_num = 200;
		destrete_num = ui.spinBox->value();
		Bit_2DCSWithExplain cs_explain;
		Bit_Point2D x_v(1, 0);
		if(ui.comboBox->currentIndex() == 1)
		{
			x_v.Set_x(-1);
		}
		Bit_2DCS cs(Bit_Point2D(ui.doubleSpinBox->value(), 0), 1, x_v);
		cs_explain.Set_Initial(0, "CS", ui.textEdit->toPlainText().toLocal8Bit().data(), cs);
		Bit_UnitSystem us = model_->get_cs().Get_UnitSystem();
		model_->get_cs().Set_Initial(cs_explain, us);
		draw_wnd_->update_cs();
		return true;
	}
	else
	{
		return false;
	}
}
void WarheadMain::on_open()
{
	QString file_name = QFileDialog::getOpenFileName(this, GBK2Unicode("打开"), QString(), GBK2Unicode("战斗部模型 (*.whd)"));
	if(!file_name.isEmpty())
	{
		JudgeSave();
		WarheadRead reader;
		model_ = reader.ReadXMLFile(file_name);
		draw_wnd_->set_model(model_);
		model_file_ = file_name;
		ui->action_save_as_file->setEnabled(true);
	}
}
void WarheadMain::JudgeSave()
{
	if(model_)
	{
		//判断是否保存

		delete model_;
	}
}

void WarheadMain::TryOpenModel(const QString& model_file)
{
	
}

void WarheadMain::on_metal_material()
{
	MaterialDialog dialog(MaterialDialog::kMetal, this);
	dialog.resize(size()/2);
	dialog.exec();
}
void WarheadMain::on_charge_material()
{
	MaterialDialog dialog(MaterialDialog::kCharge, this);
	dialog.resize(size()/2);
	dialog.exec();
}