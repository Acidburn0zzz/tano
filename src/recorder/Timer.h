#ifndef TANO_TIMER_H_
#define TANO_TIMER_H_

#include <QObject>
#include <QTime>
#include <QDate>

class Timer : public QObject {
Q_OBJECT
public:
	Timer(QString fname, QString fchannel, QString fplaylist, int fnum);
	~Timer();

public slots:
	QString name() const {return _name;}
	void setName(const QString &sname);
	QString channel() const {return _channel;}
	void setChannel(const QString &schannel);
	QString playlist() const {return _playlist;}
	void setPlaylist(const QString &splaylist);
	int num() const {return _num;}
	void setNum(const int &snum);
	QDate date() const {return _date;}
	void setDate(const QDate &sdate);
	QTime startTime() const {return _startTime;}
	void setStartTime(const QTime &sstartTime);
	QTime endTime() const {return _endTime;}
	void setEndTime(const QTime &sendTime);

private:
	QString _name;
	QString _channel;
	QString _playlist;
	int _num;
	QDate _date;
	QTime _startTime;
	QTime _endTime;
};

#endif // TANO_TIMER_H_
