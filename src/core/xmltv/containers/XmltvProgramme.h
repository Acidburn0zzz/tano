/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef TANO_XMLTVPROGRAMME_H_
#define TANO_XMLTVPROGRAMME_H_

#include <QtCore/QDateTime>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QFont>

#include "ListItem.h"

class XmltvCrewModel;

class XmltvProgramme : public ListItem
{
Q_OBJECT
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        DecorationRole = Qt::DecorationRole,
        DisplayFontRole = Qt::FontRole,
        TitleRole = Qt::UserRole + 1,
        ChannelRole,
        StartRole,
        StopRole,
        SubTitleRole,
        DescRole,
        DateRole,
        CategoriesRole,
        LanguageRole,
        OriginalLanguageRole,
        LengthRole,
        LengthUnitsRole,
        IconRole,
        IconSizeRole
    };

    // Length units
    enum LengthUnits
    {
        Seconds,
        Minutes,
        Hours
    };

    explicit XmltvProgramme(const QString &id,
                            QObject *parent = 0);
    explicit XmltvProgramme(const QString &id,
                            const QString &channel,
                            QObject *parent = 0);
    ~XmltvProgramme();

    inline QString id() const { return _id; }
    QVariant data(const int &role) const;
    QString display() const;
    QIcon decoration() const;
    QHash<int, QByteArray> roleNames() const;

    QFont displayFont() const;

    inline QString channel() const { return _channel; }
    void setChannel(const QString &s);
    inline QString channelDisplayName() const { return _channelDisplayName; }
    void setChannelDisplayName(const QString &s);
    inline QString title() const { return _title; }
    void setTitle(const QString &s);
    inline QDateTime start() const { return _start; }
    void setStart(const QDateTime &d);
    inline QDateTime stop() const { return _stop; }
    void setStop(const QDateTime &d);
    inline QString subTitle() const { return _subTitle; }
    void setSubTitle(const QString &s);
    inline QString desc() const { return _desc; }
    void setDesc(const QString &s);
    inline QDateTime date() const { return _date; }
    void setDate(const QDateTime &d);
    inline QStringList categories() const { return _categories; }
    void addCategory(const QString &s);
    void setCategories(const QStringList &s);
    inline QString language() const { return _language; }
    void setLanguage(const QString &s);
    inline QString originalLanguage() const { return _originalLanguage; }
    void setOriginalLanguage(const QString &s);
    inline QString length() const { return _length; }
    void setLength(const QString &s);
    inline LengthUnits lengthUnits() const { return _lengthUnits; }
    void setLengthUnits(const LengthUnits &e);
    inline QString icon() const { return _icon; }
    void setIcon(const QString &s);
    inline QSize iconSize() const { return _iconSize; }
    void setIconSize(const QSize &s);

    // Credits
    void addDirector(const QString &s);
    void addActor(const QString &s);
    void addWriter(const QString &s);
    void addAdapter(const QString &s);
    void addProducer(const QString &s);
    void addComposer(const QString &s);
    void addEditor(const QString &s);
    void addPresenter(const QString &s);
    void addCommentator(const QString &s);
    void addGuest(const QString &s);

    XmltvCrewModel *crew() { return _crew; }

    static LengthUnits lengthUnits(const QString &type);
    static QString lengthUnits(const LengthUnits &type);
    static QString lengthUnitsShort(const LengthUnits &type);

private:
    QString _id;
    QString _channel;
    QString _channelDisplayName;
    QString _title;
    QDateTime _start;
    QDateTime _stop;
    QString _subTitle;
    QString _desc;
    QDateTime _date;
    QStringList _categories;
    QString _language;
    QString _originalLanguage;
    QString _length;
    LengthUnits _lengthUnits;
    QString _icon;
    QSize _iconSize;

    XmltvCrewModel *_crew;
};

#endif // TANO_XMLTVPROGRAMME_H_