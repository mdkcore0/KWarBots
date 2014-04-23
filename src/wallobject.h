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

#ifndef __WALLOBJECT_H__
#define __WALLOBJECT_H__

#include <QColor>

#include "object.h"

namespace KWB{

// this class defines a WallObject, that can be destroyed
class WallObject: public Object{
	Q_OBJECT

	public:
		WallObject(const QString&, const QPoint&, const QColor&);
		virtual ~WallObject();

		void damage(const int&);

	Q_SIGNALS: // we can emit some signal, like for a colliding event

	signals:
		void deleteMe(QGraphicsItem*);

	private:
		QPixmap image[4]; // the temporary images

		Frames m_wallState;
		QColor m_color;
		int m_state;
};

} // namespace

#endif

