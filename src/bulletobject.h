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

#ifndef __BULLETOBJECT_H__
#define __BULLETOBJECT_H__

#include <QPoint>
#include <QColor>
#include <QTimer>
#include <QString>
#include <QPixmap>

#include "object.h"

namespace KWB{

#define STEP	1
#define MAXBULLETRANGE	400

// this class defines a Bullet Object
class BulletObject: public Object{
	Q_OBJECT

	public:
		BulletObject(const QPixmap&, const int&, const QPoint&, const Direction&);
		virtual ~BulletObject();

	Q_SIGNALS: // we can emit some signal, like for a colliding event

	private slots:
		void updateBulletPosition();

	signals:
		void bulletCollision(QGraphicsItem*);
		void deleteMe(QGraphicsItem*);

	private:
		void definePos(const QPoint&);
		void checkCollision();

		QTimer *m_bulletTime;
		QPoint m_pos; // absolute position
		Direction m_direction;
		int m_speed;
		int m_range;
};

} // namespace

#endif

