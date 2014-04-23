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

#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <QTime>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>

#include <kross/core/action.h>

#include "botpack.h"
#include "battlearea.h"
#include "robotobject.h"

namespace KWB{

class BattleArea;
class RobotObject;

#define STEP	1

// this class defines a Robot on KWarBots
class Robot: public QObject, public QGraphicsPixmapItem{
	Q_OBJECT
	Q_ENUMS(Movement ShotReturn)

	public:
		// Return messages
		enum Movement {MovingBackward = -1, MovingForward = 1}; // moving backward or forward
		enum ShotReturn {ShotOk, ShotNoMoreAmmo, ShotTooEarly};

		//Robot(BotPack *pack); // TODO; will contain the robot script, iamges and sounds
		Robot(BotPack*, BattleArea*, const QPoint&); // TODO: create a Radar, to show enemies, position, items...
		~Robot();

		// return the current Robot direction
		//Direction currentDirection();

		// return the robot object
		RobotObject *robotObject();


	public Q_SLOTS: // functions that the user will access
		// these functions controls the robot movements
		void turnLeft();
		void turnRight();
		void moveForward();
		void moveBackward();
		void invertMove();
		//void setSpeed(const int&); TODO FUTURE
		void stop();
		// return true if the Robot is moving
		bool isMoving();
		// return the current Robot direction
		int direction();
		// return the current movement of the Robot
		int going();
		// true if the Robot collided with something
		bool collided();
		// just shot
		int shot();

	Q_SIGNALS: // function that the user will program :)
		void main(); // yes, we have a main too

	private slots: // do the actions according the user programmed events
		void updateRobot();

	signals:
		void itemCollision(QGraphicsItem*);
		void objectCollision(QGraphicsItem*);

	private:
		/****** SCRIPT RELATED ******/
		void execScript(const QString&); // load and execute the user script file
		Kross::Action *m_action;
		/****************************/

		// colliding with some object?
		void checkCollision();

		// Robot pixmap
		RobotObject *m_robotObject;

		// yes, the timer
		QTimer *m_timer;
		// a pointer to the current battle area
		BattleArea *m_battleArea;
		// the BattleArea rect
		QRectF m_battleAreaRect;
		// half battle area width and height
		int m_halfAreaWidth, m_halfAreaHeight;
		// current position on the battle area
		QPoint m_pos;
		// size of the Robot pixmap
		QSize m_size;
		// robot graphics offset
		int m_offsetValue;

		// the currently direction of the Robot
		Direction m_direction;
		// the Robot is moving... ?
		bool m_isMoving;
		// ... forward or backward?
		Movement m_going;
		// speed
		//float m_speed, m_maximunSpeedFactor; TODO FUTURE
		// the Robot collided with something?
		bool m_collided;
		// number of bullets
		int m_bullets;
		// time between last shot
		QTime m_lastShotTime;
		int m_timeBetweenShots;
};

} // namespace

#endif

