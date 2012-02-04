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

#include "container/xmltv/XmltvCrewMember.h"
#include "container/xmltv/XmltvProgramme.h"
#include "xmltv/XmltvCrewModel.h"

XmltvProgramme::XmltvProgramme(const QString &channel,
                               QObject *parent)
    : ListItem(parent),
      _channel(channel)
{
    _crew = new XmltvCrewModel(this);
}

XmltvProgramme::~XmltvProgramme()
{
    delete _crew;
}

QHash<int, QByteArray> XmltvProgramme::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DisplayRole] = "display";
    names[DisplayIconRole] = "displayIcon";
    names[TitleRole] = "title";
    names[ChannelRole] = "channel";
    names[StartRole] = "start";
    names[StopRole] = "stop";
    names[SubTitleRole] = "subtitle";
    names[DescRole] = "desc";
    names[DateRole] = "date";
    names[CategoriesRole] = "categories";
    names[LanguageRole] = "language";
    names[OriginalLanguageRole] = "originallanguage";
    names[LenghtRole] = "lenght";
    names[LenghtUnitsRole] = "lenghtunits";
    names[IconRole] = "icon";
    names[IconSizeRole] = "iconsize";
    return names;
}

QVariant XmltvProgramme::data(int role) const
{
    switch (role)
    {
    case DisplayRole:
        return display();
    case DisplayIconRole:
        return displayIcon();
    case TitleRole:
        return title();
    case ChannelRole:
        return channelDisplayName();
    case StartRole:
        return start();
    case StopRole:
        return stop();
    case SubTitleRole:
        return subTitle();
    case DescRole:
        return desc();
    case DateRole:
        return date();
    case CategoriesRole:
        return categories();
    case LanguageRole:
        return language();
    case OriginalLanguageRole:
        return originalLanguage();
    case LenghtRole:
        return lenght();
    case LenghtUnitsRole:
        return lenghtUnits();
    case IconRole:
        return icon();
    case IconSizeRole:
        return iconSize();
    default:
        return QVariant();
    }
}

QString XmltvProgramme::display() const
{
    return QString("%1 - %2").arg(start().toString("hh:mm"), title());
}

QIcon XmltvProgramme::displayIcon() const
{
    return QIcon(":/icons/16x16/calendar.png");
}

void XmltvProgramme::setChannelDisplayName(const QString &s)
{
    if (_channelDisplayName != s) {
        _channelDisplayName = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setTitle(const QString &s)
{
    if (_title != s) {
        _title = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setStart(const QDateTime &d)
{
    if (_start != d) {
        _start = d;
        emit dataChanged();
    }
}

void XmltvProgramme::setStop(const QDateTime &d)
{
    if (_stop != d) {
        _stop = d;
        emit dataChanged();
    }
}

void XmltvProgramme::setSubTitle(const QString &s)
{
    if (_subTitle != s) {
        _subTitle = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setDesc(const QString &s)
{
    if (_desc != s) {
        _desc = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setDate(const QDateTime &d)
{
    if (_date != d) {
        _date = d;
        emit dataChanged();
    }
}

void XmltvProgramme::addCategory(const QString &s)
{
    if (!_categories.contains(s)) {
        _categories << s;
        emit dataChanged();
    }
}

void XmltvProgramme::setLanguage(const QString &s)
{
    if (_language != s) {
        _language = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setOriginalLanguage(const QString &s)
{
    if (_originalLanguage != s) {
        _originalLanguage = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setLenght(const QString &s)
{
    if (_lenght != s) {
        _lenght = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setLenghtUnits(const Tano::Xmltv::LenghtUnits &e)
{
    if (_lenghtUnits != e) {
        _lenghtUnits = e;
        emit dataChanged();
    }
}

void XmltvProgramme::setIcon(const QString &s)
{
    if (_icon != s) {
        _icon = s;
        emit dataChanged();
    }
}

void XmltvProgramme::setIconSize(const QSize &s)
{
    if (_iconSize != s) {
        _iconSize = s;
        emit dataChanged();
    }
}

void XmltvProgramme::addDirector(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Director, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addActor(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Actor, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addWriter(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Writer, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addAdapter(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Adapter, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addProducer(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Producer, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addComposer(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Composer, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addEditor(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Editor, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addPresenter(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Presenter, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addCommentator(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Commentator, this);
    _crew->appendRow(crew);
}

void XmltvProgramme::addGuest(const QString &s)
{
    XmltvCrewMember *crew = new XmltvCrewMember(s, Tano::Xmltv::Guest, this);
    _crew->appendRow(crew);
}
