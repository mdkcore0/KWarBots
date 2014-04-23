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

#include <QDebug>///
#include <QStringList>

#include "map.h"

namespace KWB{

Map::Map(const QString &file){
	m_mapFile = new QFile(file);
	
	// TODO: insert some error message
	if (!m_mapFile->open(QIODevice::ReadOnly | QIODevice::Text)) return;

	parse();

	m_mapFile->close();
}

Map::~Map(){
}

// single valued variables must has 1 line and finishes with ';'. ex.: "size = 20;"
void Map::parse(){
	QTextStream reading(m_mapFile);

	while (!reading.atEnd()){
		QString line = reading.readLine();
		QStringList list = line.split("=");
		QString option = list.at(0).trimmed().toLower(); // lowercase string with no whitespaces

		// Map related variables
		if (option == "size"){ // map size
			if (!parseSize(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Size Error";
		} else if (option == "name"){ // map name
			if (!parseName(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Name Error";
		} else if (option == "description"){ // map description
			if (!parseDescription(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Description Error";
		} else if (option == "enemies"){ // # of enemies on the map
			if (!parseEnemies(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Enemies Number Error";
		}
		// Objects/Items matrix related variables
	       	else if (option == "map_list"){ // objects map
			if (!parseMapList(reading))
				// TODO: error handling
				qDebug() << "Map::Map List Load Error";
		}
		// Textures/Images related variables
		else if (option == "ammo_texture"){ // SVG texture to use on an ammo item
			if (!parseAmmoTexture(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Ammo Texture Load Error";
		} else if (option == "block_texture"){ // SVG texture to use on a block object
			if (!parseBlockTexture(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Block Texture Load Error";
		} else if (option == "block_color"){ // color for a block object
			if (!parseBlockColor(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Block Color Load Error";
		} else if (option == "energy_texture"){ // SVG texture to use on an energy item
			if (!parseEnergyTexture(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Energy Texture Load Error";
		} else if (option == "path_texture"){ // SVG texture to use on a path object
			if (!parsePathTexture(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Path Texture Load Error";
		} else if (option == "path_color"){ // color for a path object
			if (!parsePathColor(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Path Color Load Error";
		} else if (option == "path_alt_color"){ // color for a path object
			if (!parsePathAltColor(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Path Alternate Color Load Error";
		} else if (option == "wall_texture"){ // SVG texture to use on an wall object
			if (!parseWallTexture(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Wall Texture Load Error";
		} else if (option == "wall_color"){ // color for an water object
			if (!parseWallColor(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Wall Color Load Error";
		} else if (option == "water_texture"){ // SVG texture to use on an water object
			if (!parseWaterTexture(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Water Texture Load Error";
		} else if (option == "weapon_texture"){ // SVG texture to use on an weapon item
			if (!parseWeaponTexture(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Block Weapon Load Error";
		// Items related variables
		} else if (option == "ammo_value"){ // # ammo value
			if (!parseAmmoValue(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Ammo Value Number Error";
		} else if (option == "energy_value"){ // # energy value
			if (!parseEnergyValue(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Energy Value Number Error";
		} else if (option == "weapon_value"){ // # weapon value
			if (!parseWeaponValue(list.at(1)))
				// TODO: error handling
				qDebug() << "Map::Weapon Value Number Error";
		}
		// Sounds/Musics related variables
		// TODO
		// a simple line break
		else if (option.isNull()) continue;
		// Unknown variable
		else{
			// TODO: error handling
			qDebug() << "Map::Unknown Variable " << option;
			qDebug() << "Map::Exiting...";
			return;
		}

		//if (line.contains(";"))
		//	qDebug() << line;
	}
}

/************** Map related variables **************/

bool Map::parseSize(const QString &str){
	bool ok;

	m_size = str.split(";").at(0).toInt(&ok);

	return ok;
}

int Map::size() const{
	return m_size;
}

bool Map::parseName(const QString &str){
	m_name = str.split(";").at(0).split("\"").at(1);

	return (m_name.isEmpty()) ? false : true;
}

QString Map::name() const{
	return m_name;
}

bool Map::parseDescription(const QString &str){
	m_description = str.split(";").at(0).split("\"").at(1);

	return (m_description.isEmpty()) ? false : true;
}

QString Map::description() const{
	return m_description;
}

bool Map::parseEnemies(const QString &str){
	bool ok;

	m_enemies = str.split(";").at(0).toInt(&ok);

	return ok;
}

int Map::enemies() const{
	return m_enemies;
}

/************** Objects/Items matrix related variables **************/

bool Map::parseMapList(QTextStream &stream){
	QChar c;
	int i = 0;

	stream >> c;
	do{
		if (!c.isSpace()){
			m_mapList << c;
			i++;
		}

		stream >> c;
	} while (c != QChar(';'));

	return (i == m_size * m_size) ? true : false;
}

MapList *Map::mapList(){
	return &m_mapList;
}

/************** Sound/Music related variables **************/
// TODO

/************** Texture/Images related variables **************/

bool Map::parseAmmoTexture(const QString &str){
	m_ammoTexture = str.split(";").at(0).trimmed();

	return (m_ammoTexture.isEmpty()) ? false : true;
}

QString Map::ammoTexture() const{
	return m_ammoTexture;
}

bool Map::parseAmmoValue(const QString &str){
	bool ok;

	m_ammoValue = str.split(";").at(0).toInt(&ok);

	return ok;
}

int Map::ammoValue() const{
	return m_ammoValue;
}

bool Map::parseBlockTexture(const QString &str){
	m_blockTexture = str.split(";").at(0).trimmed();

	return (m_blockTexture.isEmpty()) ? false : true;
}

QString Map::blockTexture() const{
	return m_blockTexture;
}

bool Map::parseBlockColor(const QString &str){
	m_blockColor = QColor(str.split(";").at(0).trimmed());

	return m_blockColor.isValid();
}

QColor Map::blockColor() const{
	return m_blockColor;
}

bool Map::parseEnergyTexture(const QString &str){
	m_energyTexture = str.split(";").at(0).trimmed();

	return (m_energyTexture.isEmpty()) ? false : true;
}

QString Map::energyTexture() const{
	return m_energyTexture;
}

bool Map::parseEnergyValue(const QString &str){
	bool ok;

	m_energyValue = str.split(";").at(0).toInt(&ok);

	return ok;
}

int Map::energyValue() const{
	return m_energyValue;
}

bool Map::parsePathTexture(const QString &str){
	m_pathTexture = str.split(";").at(0).trimmed();

	return (m_pathTexture.isEmpty()) ? false : true;
}

QString Map::pathTexture() const{
	return m_pathTexture;
}

bool Map::parsePathColor(const QString &str){
	m_pathColor = QColor(str.split(";").at(0).trimmed());

	return m_pathColor.isValid();
}

bool Map::parsePathAltColor(const QString &str){
	m_pathAltColor = QColor(str.split(";").at(0).trimmed());

	return m_pathAltColor.isValid();
}

QColor Map::pathColor() const{
	return m_pathColor;
}

QColor Map::pathAltColor() const{
	return m_pathAltColor;
}

bool Map::parseWallTexture(const QString &str){
	m_wallTexture = str.split(";").at(0).trimmed();

	return (m_wallTexture.isEmpty()) ? false : true;
}

QString Map::wallTexture() const{
	return m_wallTexture;
}

bool Map::parseWallColor(const QString &str){
	m_wallColor = QColor(str.split(";").at(0).trimmed());

	return m_wallColor.isValid();
}

QColor Map::wallColor() const{
	return m_wallColor;
}

bool Map::parseWaterTexture(const QString &str){
	m_waterTexture = str.split(";").at(0).trimmed();

	return (m_waterTexture.isEmpty()) ? false : true;
}

QString Map::waterTexture() const{
	return m_waterTexture;
}

bool Map::parseWeaponTexture(const QString &str){
	m_weaponTexture = str.split(";").at(0).trimmed();

	return (m_weaponTexture.isEmpty()) ? false : true;
}

QString Map::weaponTexture() const{
	return m_weaponTexture;
}

bool Map::parseWeaponValue(const QString &str){
	bool ok;

	m_weaponValue = str.split(";").at(0).toInt(&ok);

	return ok;
}

int Map::weaponValue() const{
	return m_weaponValue;
}

} // namespace

