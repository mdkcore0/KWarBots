/*
 *	Copyright 2009-2010 Rodrigo Gonçalves de Oliveira <mdkcore@gmail.com - rodrigo.golive@gmail.com>
 *	http://thecoreme.org/blog/projects/kwarbots
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __BOTPACK_H__
#define __BOTPACK_H__

#include <QChar>
#include <QList>
#include <QFile>
#include <QColor>
#include <QString>
#include <QTextStream>

namespace KWB{

//typedef QList<QChar> BotPackList;

// this class defines a BotPack, with robot textures, colors and other things
class BotPack{
	public:
		BotPack(const QString&);
		~BotPack();

		QString name() const;
		QString description() const;
		// TODO: sound
		QString imageFile() const;
		QColor bodyColor() const;
		QColor bulletColor() const;
		QColor weaponColor() const;
		QColor propulsionColor() const;

	private:
		void parse();

		// BotPack related variables
		QString m_name;
		bool parseName(const QString&);
		
		QString m_description;
		bool parseDescription(const QString&);
		
		// Sounds/Music related variables
		// TODO
		
		// Images related variables
		QString m_imageFile;
		bool parseImageFile(const QString&);

		QColor m_bodyColor;
		bool parseBodyColor(const QString&);

		QColor m_bulletColor;
		bool parseBulletColor(const QString&);

		QColor m_weaponColor;
		bool parseWeaponColor(const QString&);

		QColor m_propulsionColor;
		bool parsePropulsionColor(const QString&);
		///////////////////////////////////////////

		QFile *m_botPackFile;
};

} // namespace

#endif

