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

#include <QSize>
#include <QPixmap>
#include <QPainter>

#include "bulletobject.h"

namespace KWB{

BulletObject::BulletObject(const QPixmap &bullet, const int &fps, const QPoint &startPoint, const Direction &direction): Object(startPoint), m_range(0){
	QSize m_size(SIZE, SIZE);

	setPixmap(bullet);

	setData(0, "Object");
	setData(1, "Bullet");
	setZValue(3);

	m_speed = fps / 1;

	m_bulletTime = new QTimer(this);
	m_bulletTime->setInterval(m_speed);

	connect(m_bulletTime, SIGNAL(timeout()), this, SLOT(updateBulletPosition()));

	definePos(startPoint);

	m_direction = direction;

	switch (m_direction){
		case DirectionUp:
			setRotation(0);
			break;
		case DirectionRight:
			setRotation(90);
			break;
		case DirectionDown:
			setRotation(180);
			break;
		case DirectionLeft:
			setRotation(-90);
			break;
	}

	m_bulletTime->start();
}

BulletObject::~BulletObject(){
}

void BulletObject::definePos(const QPoint &pos){
	m_pos = pos;

	setPos(m_pos);
}

void BulletObject::checkCollision(){
	foreach (QGraphicsItem *item, collidingItems()){
		if (item->zValue() == zValue() - 1){
			QString kind = item->data(0).toString();

			if ((kind == "Object") || (kind == "Robot")){
				hide();
				m_bulletTime->stop();

				emit bulletCollision(item);
			}
		}
	}
}

void BulletObject::updateBulletPosition(){
	switch (m_direction){
		case DirectionUp:
			definePos(m_pos + QPoint(0, -STEP));
			break;
		case DirectionRight:
			definePos(m_pos + QPoint(STEP, 0));
			break;
		case DirectionDown:
			definePos(m_pos + QPoint(0, STEP));
			break;
		case DirectionLeft:
			definePos(m_pos + QPoint(-STEP, 0));
			break;
	}

	m_range++;

	checkCollision();

	if (m_range > MAXBULLETRANGE){ // TODO
		m_bulletTime->stop();

		emit deleteMe(this);
		deleteLater();
	}
}

} // namespace

