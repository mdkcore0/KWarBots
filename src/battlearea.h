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

#ifndef __BATTLEAREA_H__
#define __BATTLEAREA_H__

#include <QKeyEvent>
#include <QGraphicsScene>

#include "map.h"
#include "robot.h"

namespace KWB{

class Robot;

// this class defines the BattleArea of KWarBots
class BattleArea: public QGraphicsScene{
	Q_OBJECT

	public:
		BattleArea(Map*);
		~BattleArea();

		// update to a new game map
		//void updateArea(Map *map);

	public slots:
		void itemCollision(QGraphicsItem*);
		void objectCollision(QGraphicsItem*);
		void bulletCollision(QGraphicsItem*);
		void deleteItem(QGraphicsItem*);

	private:
		Robot *m_robot;
		// battle area field size
		int m_width, m_height;

	protected:
		// some user key press
		void keyPressEvent(QKeyEvent *event);
};

} // namespace

#endif

