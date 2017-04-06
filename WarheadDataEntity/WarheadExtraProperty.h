#pragma once
#include "entity.h"

class WARHEADDATAENTITY_EXPORT WarheadExtraProperty :
	public Entity
{
public:
	WarheadExtraProperty(void);
	virtual ~WarheadExtraProperty(void);
	void set_id(int id) { id_ = id; }
	int get_id() const { return id_; }

	void set_share(bool share) { share_ = share; }
	bool get_share() const { return share_; }

	void set_guid(const QString& guid) { guid_ = guid; }
	QString get_guid() const { return guid_; }

	void set_name(const QString& name) { name_ = name; }
	QString get_name() const { return name_; }

	void set_describe(const QString& describe) { describe_ = describe; }
	QString get_describe() const { return describe_; }

	void set_country(const QString& country) { country_ = country; }
	QString get_country() const { return country_; }

	void set_missile_name(const QString& missile_name) { missile_name_ = missile_name; }
	QString get_missile_name() const { return missile_name_; }

	void set_task_guid(const QString& task_guid) { task_guid_ = task_guid; }
	QString get_task_guid() const { return task_guid_; }

	void set_sub_class_guid(const QString& guid) { sub_class_guid_ = guid; }
	QString get_sub_class_guid() const { return sub_class_guid_; }

	void set_service_start_date(const QDate& date) { service_start_date_ = date; }
	QDate get_service_start_date() const { return service_start_date_; }

	void set_service_end_date(const QDate& date) { service_end_date_ = date; }
	QDate get_service_end_date() const { return service_end_date_; }

	void set_create_time(const QDateTime& time) { create_time_ = time; }
	QDateTime get_create_time() const { return create_time_; }

	void set_update_time(const QDateTime& time) { update_time_ = time; }
	QDateTime get_update_time() const { return update_time_; }
protected:
	bool share_;
	int id_;
	QString guid_;
	QString name_;
	QString describe_;
	QString country_;
	QString sub_class_guid_;
	QString task_guid_;
	QString missile_name_;
	QDate service_start_date_;
	QDate service_end_date_;
	QDateTime create_time_;
	QDateTime update_time_;
};

