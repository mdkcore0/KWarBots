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

#ifndef __ROBOTOBJECT_H__
#define __ROBOTOBJECT_H__

#include <QPoint>
#include <QString>
#include <QPixmap>

#include "object.h"
#include "botpack.h"
#include "animation.h"

namespace KWB{

// this class defines a Robot Object
class RobotObject: public Object{
	public:
		RobotObject(BotPack*, const QPoint&);
		virtual ~RobotObject();

		void start(bool forward = true);
		void stop();
		bool isAnimating();

		void definePos(const QPoint&);
		// return the bullet pixmap
		QPixmap bullet();

	Q_SIGNALS: // we can emit some signal, like for a colliding event

	private:
		QPixmap m_bullet;
		QPoint m_pos; // absolute position
};

} // namespace

#endif

