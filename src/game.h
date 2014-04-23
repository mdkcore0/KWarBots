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

#ifndef __GAME_H__
#define __GAME_H__

#include <QWidget>
#include <QGraphicsView>
//#include <QGraphicsScene>

#include "battlearea.h"

namespace KWB{

// this class defines the Game area of KWarBots
class Game: public QWidget{
	Q_OBJECT
	
	public:
		Game(QWidget *parent = 0);
		~Game();

	private:
		BattleArea *m_battleArea;
		QGraphicsView *m_view;
};

} // namespace

#endif

