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

#ifndef __MAP_H__
#define __MAP_H__

#include <QChar>
#include <QList>
#include <QFile>
#include <QColor>
#include <QString>
#include <QTextStream>

namespace KWB{

#define Ammo		'm' // item
#define	Block		'b' // object
#define Enemy		'e' // object
#define Energy		'f' // item
#define Nothing		'n' // item
#define Path		'p' // object
#define StartPoint	's' // object
#define	Wall		'w' // object
#define Water		'a' // object
#define Weapon		'h' // item

	typedef QList<QChar> MapList;

	// this class defines a Map, with textures, items and position matrix
	class Map{
		public:
			Map(const QString&);
			~Map();

			int size() const;
			QString name() const;
			QString description() const;

			int enemies() const;

			MapList *mapList();
			// TODO: sound

			QString ammoTexture() const;
			int ammoValue() const;

			QString blockTexture() const;
			QColor blockColor() const;

			QString energyTexture() const;
			int energyValue() const;

			QString pathTexture() const;
			QColor pathColor() const;
			QColor pathAltColor() const;

			QString wallTexture() const;
			QColor wallColor() const;

			QString waterTexture() const;

			QString weaponTexture() const;
			int weaponValue() const;

		private:
			void parse();

			// Map related variables
			int m_size;
			bool parseSize(const QString&);

			QString m_name;
			bool parseName(const QString&);
			
			QString m_description;
			bool parseDescription(const QString&);
			
			int m_enemies;
			bool parseEnemies(const QString&);
			
			// Objects/Items matrix related variables
			MapList m_mapList;
			bool parseMapList(QTextStream&);

			// Sounds/Music related variables
			// TODO
			
			// Textures/Images related variables
			QString m_ammoTexture;
			int m_ammoValue;
			bool parseAmmoTexture(const QString&);
			bool parseAmmoValue(const QString&);

		QString m_blockTexture;
		QColor m_blockColor;
		bool parseBlockTexture(const QString&);
		bool parseBlockColor(const QString&);

		QString m_energyTexture;
		int m_energyValue;
		bool parseEnergyTexture(const QString&);
		bool parseEnergyValue(const QString&);

		QString m_pathTexture;
		QColor m_pathColor;
		QColor m_pathAltColor;
		bool parsePathTexture(const QString&);
		bool parsePathColor(const QString&);
		bool parsePathAltColor(const QString&);

		QString m_wallTexture;
		QColor m_wallColor;
		bool parseWallTexture(const QString&);
		bool parseWallColor(const QString&);

		QString m_waterTexture;
		bool parseWaterTexture(const QString&);

		QString m_weaponTexture;
		int m_weaponValue;
		bool parseWeaponTexture(const QString&);
		bool parseWeaponValue(const QString&);
		///////////////////////////////////////////

		QFile *m_mapFile;
};

} // namespace

#endif

