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

#include <KGlobal>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KStandardDirs>

#include "botpack.h"
#include "ammoitem.h"
#include "battlearea.h"
#include "tileobject.h"
#include "wallobject.h"
#include "energyitem.h"
#include "weaponitem.h"
#include "waterobject.h"
#include "blockobject.h"
#include "terrainobject.h"

namespace KWB{

BattleArea::BattleArea(Map *map){
	setItemIndexMethod(QGraphicsScene::NoIndex);

	///
	QTimer *timer = new QTimer();
	timer->setInterval(1000);

	m_width = m_height = map->size() * SIZE;
	setSceneRect(0, 0, m_width, m_height);

	BotPack *bpack = new BotPack("data/robots/botpacks/tank-0.bpack"); // must be dynamic, too (maybe by reference)

	MapList *mapList = map->mapList();
	int mapSize = map->size();
	int i, j;
	int listpos = 0;

	// the TileObject used as BattleArea "background"
	TileObject *tile = new TileObject("data/textures/" + map->pathTexture() + ".svgz", map->pathColor(), map->pathAltColor());
	setBackgroundBrush(tile->pixmap());

	// must add on KWB::Map a method to load the map
	for (i = 0; i < mapSize; i++){
		for (j = 0; j < mapSize; j++){
			listpos = (j * mapSize) + i;
			
			// iteratte trough the map list (objects and items)
			if (mapList->at(listpos) == Ammo){
				AmmoItem *ammo = new AmmoItem("data/items/" + map->ammoTexture() + ".svgz", QPoint(i, j), map->ammoValue());
				addItem(ammo);
			} else if (mapList->at(listpos) == Block){
				BlockObject *block = new BlockObject("data/textures/" + map->blockTexture() + ".svgz", QPoint(i, j), map->blockColor());
				addItem(block);
			} else if (mapList->at(listpos) == Enemy){
				// TODO
			} else if (mapList->at(listpos) == Energy){
				EnergyItem *energy = new EnergyItem("data/items/" + map->energyTexture() + ".svgz", QPoint(i, j), map->energyValue());
				addItem(energy);
			} else if (mapList->at(listpos) == StartPoint){
				// the user programmed Robot
				m_robot = new Robot(bpack, this, QPoint(i, j));
				addItem(m_robot->robotObject()); 
			} else if (mapList->at(listpos) == Wall){
				WallObject *wall = new WallObject("data/textures/" + map->wallTexture() + ".svgz", QPoint(i, j), map->wallColor());
				addItem(wall);

				connect(wall, SIGNAL(deleteMe(QGraphicsItem*)), this, SLOT(deleteItem(QGraphicsItem*)));
			} else if (mapList->at(listpos) == Water){
				WaterObject *water = new WaterObject("data/textures/" + map->waterTexture() + ".svgz", QPoint(i, j), timer);
				addItem(water);
			} else if (mapList->at(listpos) == Weapon){
				WeaponItem *weapon = new WeaponItem("data/items/" + map->weaponTexture() + ".svgz", QPoint(i, j), map->weaponValue());
				addItem(weapon);
			}
		}
	}

	connect(m_robot, SIGNAL(itemCollision(QGraphicsItem*)), this, SLOT(itemCollision(QGraphicsItem*)));
	connect(m_robot, SIGNAL(objectCollision(QGraphicsItem*)), this, SLOT(objectCollision(QGraphicsItem*)));

	timer->start();
	///
	//qDebug() << "---- DIR: " << KGlobal::dirs()->installPath("data") + KCmdLineArgs::aboutData()->appName();
}

BattleArea::~BattleArea(){
}

// Just for tests
void BattleArea::keyPressEvent(QKeyEvent *event){
	switch (event->key()){
		case Qt::Key_Left:
			m_robot->turnLeft();
			break;
		case Qt::Key_Right:
			m_robot->turnRight();
			break;
		case Qt::Key_Up:
			m_robot->moveForward();
			break;
		case Qt::Key_Down:
			m_robot->moveBackward();
			break;
		case Qt::Key_Space:
			m_robot->stop();
			break;
		case Qt::Key_F:
			m_robot->shot();
			break;
		default:
			break;
	}
}

void BattleArea::itemCollision(QGraphicsItem *item){
	// TODO: get item information
	deleteItem(item);
}

void BattleArea::objectCollision(QGraphicsItem *item){
	// TODO
}

void BattleArea::bulletCollision(QGraphicsItem *item){
	// TODO
	if (item->data(1).toString() == "Wall"){
		WallObject *wall = qgraphicsitem_cast<WallObject *>(item);
		wall->damage(10);
	}
}

void BattleArea::deleteItem(QGraphicsItem *item){
	removeItem(item);
}

} // namespace

