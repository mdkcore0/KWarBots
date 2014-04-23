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

#include "botpack.h"

namespace KWB{

BotPack::BotPack(const QString &file){
	m_botPackFile = new QFile(file);
	
	// TODO: insert some error message
	if (!m_botPackFile->open(QIODevice::ReadOnly | QIODevice::Text)) return;

	parse();

	m_botPackFile->close();
}

BotPack::~BotPack(){
}

// single valued variables must has 1 line and finishes with ';'. ex.: "size = 20;"
void BotPack::parse(){
	QTextStream reading(m_botPackFile);

	while (!reading.atEnd()){
		QString line = reading.readLine();
		QStringList list = line.split("=");
		QString option = list.at(0).trimmed().toLower(); // lowercase string with no whitespaces

		// BotPack related variables
		if (option == "name"){ // botpack name
			if (!parseName(list.at(1)))
				// TODO: error handling
				qDebug() << "BotPack::Name Error";
		} else if (option == "description"){ // botpack description
			if (!parseDescription(list.at(1)))
				// TODO: error handling
				qDebug() << "BotPack::Description Error";
		}
		// Images related variables
		else if (option == "image_file"){ // SVG image to use on an ammo item
			if (!parseImageFile(list.at(1)))
				// TODO: error handling
				qDebug() << "BotPack::Image File Load Error";
		} else if (option == "body_color"){ // color for the body
			if (!parseBodyColor(list.at(1)))
				// TODO: error handling
				qDebug() << "BotPack::Body Color Load Error";
		} else if (option == "bullet_color"){ // color for the bullet
			if (!parseBulletColor(list.at(1)))
				// TODO: error handling
				qDebug() << "BotPack::Bullet Color Load Error";
		} else if (option == "weapon_color"){ // color for the bullet
			if (!parseWeaponColor(list.at(1)))
				// TODO: error handling
				qDebug() << "BotPack::Weapon Color Load Error";
		} else if (option == "propulsion_color"){ // color for the bullet
			if (!parsePropulsionColor(list.at(1)))
				// TODO: error handling
				qDebug() << "BotPack::Propulsion Color Load Error";
		}
		// Sounds/Musics related variables
		// TODO
		// a simple line break
		else if (option.isNull()) continue;
		// Unknown variable
		else{
			// TODO: error handling
			qDebug() << "BotPack::Unknown Variable " << option;
			qDebug() << "BotPack::Exiting...";
			return;
		}

		//if (line.contains(";"))
		//	qDebug() << line;
	}
}

/************** BotPack related variables **************/

bool BotPack::parseName(const QString &str){
	m_name = str.split(";").at(0).split("\"").at(1);

	return (m_name.isEmpty()) ? false : true;
}

QString BotPack::name() const{
	return m_name;
}

bool BotPack::parseDescription(const QString &str){
	m_description = str.split(";").at(0).split("\"").at(1);

	return (m_description.isEmpty()) ? false : true;
}

QString BotPack::description() const{
	return m_description;
}

/************** Sound/Music related variables **************/
// TODO

/************** Images related variables **************/

bool BotPack::parseImageFile(const QString &str){
	m_imageFile = str.split(";").at(0).trimmed();

	return (m_imageFile.isEmpty()) ? false : true;
}

QString BotPack::imageFile() const{
	return m_imageFile;
}

bool BotPack::parseBodyColor(const QString &str){
	m_bodyColor = QColor(str.split(";").at(0).trimmed());

	return m_bodyColor.isValid();
}

QColor BotPack::bodyColor() const{
	return m_bodyColor;
}

bool BotPack::parseBulletColor(const QString &str){
	m_bulletColor = QColor(str.split(";").at(0).trimmed());

	return m_bulletColor.isValid();
}

QColor BotPack::bulletColor() const{
	return m_bulletColor;
}

bool BotPack::parseWeaponColor(const QString &str){
	m_weaponColor = QColor(str.split(";").at(0).trimmed());

	return m_weaponColor.isValid();
}

QColor BotPack::weaponColor() const{
	return m_weaponColor;
}

bool BotPack::parsePropulsionColor(const QString &str){
	m_propulsionColor = QColor(str.split(";").at(0).trimmed());

	return m_propulsionColor.isValid();
}

QColor BotPack::propulsionColor() const{
	return m_propulsionColor;
}

} // namespace

