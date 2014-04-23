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

#include "robotobject.h"
#include "imageloader.h"

namespace KWB{

RobotObject::RobotObject(BotPack *bpack, const QPoint &pos): Object(pos){
	m_animation = new Animation(25 * 2);/// TODO

	QSize m_size(SIZE, SIZE);//// ver Object -> m_size
	QPixmap body, propulsion, weapon;
	int i, count = 3;

	ImageLoader loader("data/robots/graphics/" + bpack->imageFile() + ".svgz");

	// TODO: ERROR HANDLER
	body = loader.retrieve("body", m_size, bpack->bodyColor());
	weapon = loader.retrieve("weapon", m_size, bpack->weaponColor());
	m_bullet = loader.retrieve("bullet", m_size, bpack->bulletColor());

	for (i = 1; i <= count; i++){
		propulsion = loader.retrieve(QString("propulsion0%1").arg(i), m_size, bpack->propulsionColor());

		QPixmap *temp = new QPixmap(m_size);
		temp->fill(Qt::transparent);

		QPainter p;
		p.begin(temp);
			QRect r(QPoint(0, 0), m_size);

			p.drawPixmap(r, propulsion);
			p.drawPixmap(r, body);
			p.drawPixmap(r, weapon);
		p.end();

		m_animation->addPixmap(temp);
	}

	setPixmap(*m_animation->currentFrame());

	setData(0, "Robot");
	setData(1, "Robot");
	setZValue(4);
}

RobotObject::~RobotObject(){
}

void RobotObject::start(bool forward){
	m_animation->start(forward);
}

void RobotObject::stop(){
	m_animation->stop();
}

bool RobotObject::isAnimating(){
	return m_animation->isAnimating();
}

void RobotObject::definePos(const QPoint &pos){
	m_pos = pos;

	setPos(m_pos);
}

QPixmap RobotObject::bullet(){
	return m_bullet;
}

} // namespace

