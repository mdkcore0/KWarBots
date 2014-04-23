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

#include <kross/core/manager.h>

#include <QPainter>
#include <QDebug>

#include "robot.h"
#include "imageloader.h"
#include "bulletobject.h"

namespace KWB{

Robot::Robot(BotPack *bpack, BattleArea *area, const QPoint &pos):
	m_battleArea(area),
	m_pos(position(pos) + QPoint(SIZE / 2, SIZE / 2)),
	m_bullets(79),
	//m_bullets(10),
	m_timeBetweenShots(1000){ // need to use postion() function here
	//m_timeBetweenShots(3000){ // need to use postion() function here
	// TODO
	m_size = QSize(SIZE, SIZE);

	m_robotObject = new RobotObject(bpack, pos); // note: use the original position here
	if (!m_robotObject){
		// TODO ERROR MESSAGE
		return;
	}

	/***** INITIAL VALUES *****/
	//setOffset(-(QPoint(m_size.width() / 2, m_size.height() / 2)));
	m_offsetValue = (m_size.width() / 2) + 2;

	m_direction = DirectionUp; // TODO according the BotPack
	m_isMoving = false;
	m_going = MovingForward; // will initially move forward

	//m_maximunSpeedFactor = 1.0; // TODO BotPack
	//m_speed = 1.0; TODO FUTURE
	
	m_collided = false;
	
	m_battleAreaRect = m_battleArea->sceneRect();
	m_halfAreaWidth = m_battleAreaRect.width() / 2;
	m_halfAreaHeight = m_battleAreaRect.height() / 2;
	/**************************/

	m_timer = new QTimer();
	m_timer->setInterval(25);
	//m_timer->setInterval(int(1000 / Game::FPS)); FPS: 40
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateRobot()));
	connect(m_timer, SIGNAL(timeout()), this, SIGNAL(main())); // from Kross
	connect(m_timer, SIGNAL(timeout()), m_robotObject, SLOT(update()));

	execScript("src/robot.py");

	m_timer->start();
}

Robot::~Robot(){
}

void Robot::execScript(const QString &script){
	m_action = new Kross::Action(this, script);

	m_action->addObject(this, "Robot", Kross::ChildrenInterface::AutoConnectSignals);

	m_action->setInterpreter("python");
	m_action->setFile(script);
	m_action->trigger();
}

RobotObject *Robot::robotObject(){
	return m_robotObject;
}

/*Robot::Direction Robot::currentDirection(){
	return m_direction;
}*/

void Robot::checkCollision(){
	// here we check boundary collisions
	if (m_isMoving && !m_collided){
		switch (m_direction){
			case DirectionUp:
				if (!m_battleAreaRect.contains(m_pos.x(), m_pos.y() - STEP -
							(m_going * (m_offsetValue + (m_pos.y() > m_halfAreaHeight ? 0 : - 2)))))
					m_collided = true;
				else{
					m_pos.setY(m_pos.y() - (STEP * m_going) /** speed*/);
					m_robotObject->definePos(m_pos);
				}
				break;
			case DirectionRight:
				if (!m_battleAreaRect.contains(m_pos.x() + STEP +
							(m_going * (m_offsetValue + (m_pos.x() > m_halfAreaWidth ? -2 : 0))), m_pos.y()))
					m_collided = true;
				else{
					m_pos.setX(m_pos.x() + (STEP * m_going) /** speed*/);
					m_robotObject->definePos(m_pos);
				}
				break;
			case DirectionDown:
				if (!m_battleAreaRect.contains(m_pos.x(), m_pos.y() - STEP +
							(m_going * (m_offsetValue + (m_pos.y() > m_halfAreaHeight ? 0 : - 2)))))
					m_collided = true;
				else{
					m_pos.setY(m_pos.y() + (STEP * m_going) /** speed*/);
					m_robotObject->definePos(m_pos);
				}
				break;
			case DirectionLeft:
				if (!m_battleAreaRect.contains(m_pos.x() - STEP -
							(m_going * (m_offsetValue + (m_pos.x() > m_halfAreaWidth ? 0 : -2))), m_pos.y()))
					m_collided = true;
				else{
					m_pos.setX(m_pos.x() - (STEP * m_going) /** speed*/);
					m_robotObject->definePos(m_pos);
				}
				break;
		}
	}

	// now check for object/item collisions
	if (!m_collided){
		foreach (QGraphicsItem *item, m_robotObject->collidingItems()){
			if (item->zValue() == m_robotObject->zValue() - 2){
				QString kind = item->data(0).toString();

				if (kind == "Item"){
					emit itemCollision(item);
				} else if (kind == "Object"){
					m_collided = true;

					emit objectCollision(item);

					switch (m_direction){
						case DirectionUp:
							m_pos.setY(m_pos.y() + m_going);
							m_robotObject->definePos(m_pos);
							break;
						case DirectionRight:
							m_pos.setX(m_pos.x() - m_going);
							m_robotObject->definePos(m_pos);
							break;
						case DirectionDown:
							m_pos.setY(m_pos.y() - m_going);
							m_robotObject->definePos(m_pos);
							break;
						case DirectionLeft:
							m_pos.setX(m_pos.x() + m_going);
							m_robotObject->definePos(m_pos);
							break;
					}
				}

				return;
			}
		}
	}
}

void Robot::updateRobot(){
	// check for collisions
	checkCollision();
}

/****** SCRIPT RELATED ******/
// Just turn the Robot left
void Robot::turnLeft(){
	m_robotObject->rotate(-90);

	m_direction = (m_direction == DirectionUp) ? DirectionLeft : (Direction)((m_direction - 1) % 4);

	if (m_collided) m_collided = false;
}

// Just turn the Robot right
void Robot::turnRight(){
	//bool wasMoving = isMoving();

	//stop();
	m_robotObject->rotate(90);

	/*if (wasMoving){
		if (m_going == Forward)
			moveForward();
		else
			moveBackward();
	}*/

	m_direction = (Direction)((m_direction + 1) % 4);

	if (m_collided) m_collided = false;
}

// Put the robot on "walking" state; moving forward
void Robot::moveForward(){
	m_isMoving = true;

	// invert moving animation OR start animation
	if (m_going == MovingBackward || !m_robotObject->isAnimating())
		m_robotObject->start();

	m_going = MovingForward;

	if (m_collided) m_collided = false;
}

// Put the robot on "walking" state; moving backward
void Robot::moveBackward(){
	m_isMoving = true;

	if (m_going == MovingForward || !m_robotObject->isAnimating())
		m_robotObject->start(false);

	m_going = MovingBackward;

	if (m_collided) m_collided = false;
}

void Robot::invertMove(){
	if (m_going == MovingForward){
		m_going = MovingBackward;
		m_robotObject->start(false);
	} else{
		m_going = MovingForward;
		m_robotObject->start();
	}

	if (m_collided) m_collided = false;
}

//void Robot::setSpeed(const int &speed){ // TODO FUTURE
//	m_speed = ()
//}

// Stop the Robot movement
void Robot::stop(){
	m_isMoving = false;
	m_robotObject->stop();
}

bool Robot::isMoving(){
	return m_isMoving;
}

int Robot::direction(){
	return (int)m_direction;
}

int Robot::going(){
	return (int)m_going;
}

bool Robot::collided(){
	return m_collided;
}

// to compare use ShotReturn values; need to retun an int to expose to python
int Robot::shot(){
	if (m_bullets < 0)
		return ShotNoMoreAmmo;
	else if (m_lastShotTime.elapsed() < m_timeBetweenShots)
		return ShotTooEarly;
	else{
		BulletObject *bullet = new BulletObject(m_robotObject->bullet(), 10, // fps
				m_pos, m_direction); // we need to correct the bullet offset
		m_battleArea->addItem(bullet);

		connect(bullet, SIGNAL(bulletCollision(QGraphicsItem*)), m_battleArea, SLOT(bulletCollision(QGraphicsItem*)));
		connect(bullet, SIGNAL(deleteMe(QGraphicsItem*)), m_battleArea, SLOT(deleteItem(QGraphicsItem*)));

		m_bullets--;
		m_lastShotTime.restart();
	}

	return ShotOk;
}

} // namespace

