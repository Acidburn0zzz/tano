/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

#ifndef TANO_CHANNEL_H_
#define TANO_CHANNEL_H_

#include <QtCore/QString>
#include <QtCore/QStringList>

#include "CoreSharedExport.h"

#include "ListItem.h"

/*!
    \class Channel Channel.h core/Channel.h
    \brief Channel item

    A channel item for playlist models
*/
class TANO_CORE_EXPORT Channel : public ListItem
{
Q_OBJECT
public:
    /*!
        \enum Roles
        \brief Data role identifiers
    */
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        DecorationRole = Qt::DecorationRole,
        NameRole = Qt::UserRole + 1,
        NumberRole,
        TypeRole,
        LanguageRole,
        UrlRole,
        XmltvIdRole,
        CategoriesRole,
        LogoRole
    };

    /*!
        \enum Type
        \brief Channel type identifiers
    */
    enum Type
    {
        SD,
        HD,
        Radio
    };

    /*!
        \brief Basic constructor
        \param parent parent object (QObject *)
    */
    explicit Channel(QObject *parent = 0);

    /*!
        \brief Advanced constructor - also set name and number
        \param name new channel's name (QString)
        \param number new channel's number (int)
        \param parent parent object (QObject *)
    */
    explicit Channel(const QString &name,
                     const int &number,
                     QObject *parent = 0);
    ~Channel();

    // Implemented virtual functions
    inline QString id() const { return _url; }
    QVariant data(const int &role) const;
    QString display() const;
    QIcon decoration() const;
    QHash<int, QByteArray> roleNames() const;

    /*!
        \brief Get chanel number
        \return channel number (int)
    */
    inline int number() const { return _number; }
    /*!
        \brief Set chanel number
        \param number new channel number (int)
    */
    void setNumber(const int &number);

    /*!
        \brief Get channel type
        \return channel type (Channel::Type)
    */
    inline Type type() const { return _type; }
    /*!
        \brief Set channel type
        \return type new channel type (Channel::Type)
    */
    void setType(const Type &type);

    /*!
        \brief Get channel name
        \return channel name (QString)
    */
    inline QString name() const { return _name; }
    /*!
        \brief Set channel name
        \return name new channel name (QString)
    */
    void setName(const QString &name);

    /*!
        \brief Get channel language
        \return channel language (QString)
    */
    inline QString language() const { return _language; }
    /*!
        \brief Set channel language
        \return language new channel language (QString)
    */
    void setLanguage(const QString &language);

    /*!
        \brief Get channel url
        \return channel url (QString)
    */
    inline QString url() const { return _url; }
    /*!
        \brief Set channel url
        \return url new channel url (QString)
    */
    void setUrl(const QString &url);

    /*!
        \brief Get channel XMLTV ID
        \return channel XMLTV ID (QString)
    */
    inline QString xmltvId() const { return _xmltvId; }
    /*!
        \brief Set channel XMLTV ID
        \return xmltvId new channel XMLTV ID (QString)
    */
    void setXmltvId(const QString &xmltvId);

    /*!
        \brief Get channel categories
        \return channel categories (QStringList)
    */
    inline QStringList categories() const { return _categories; }
    /*!
        \brief Set channel categories
        \return categories new channel categories (QStringList)
    */
    void setCategories(const QStringList &categories);

    /*!
        \brief Get channel logo
        \return channel logo (QString)
    */
    inline QString logo() const { return _logo; }
    /*!
        \brief Set channel logo
        \return logo new channel logo (QString)
    */
    void setLogo(const QString &logo);

    /*!
        \brief Channel type strings
        \return channel type strings (QStringList)
    */
    static QStringList types();

private:
    QString _name;
    int _number;
    Type _type;
    QString _language;
    QString _url;
    QString _xmltvId;
    QStringList _categories;
    QString _logo;
};

#endif // TANO_CHANNEL_H_