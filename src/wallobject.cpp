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

#include "wallobject.h"
#include "imageloader.h"
#include <QDebug>

namespace KWB{

WallObject::WallObject(const QString &imageFile, const QPoint &pos, const QColor &color): Object(imageFile, pos), m_color(color), m_state(100){
	QSize m_size(SIZE, SIZE);

	ImageLoader loader(imageFile);

	// position 0 on m_wallState
	image[0] = loader.retrieve("100", m_size, m_color);
	m_wallState << &image[0];
	// position 1 on m_wallState
	image[1] = loader.retrieve("75", m_size, m_color);
	m_wallState << &image[1];
	// position 2 on m_wallState
	image[2] = loader.retrieve("50", m_size, m_color);
	m_wallState << &image[2];
	// position 3 on m_wallState
	image[3] = loader.retrieve("25", m_size, m_color);
	m_wallState << &image[3];

	setPixmap(*m_wallState.at(0));

	setData(0, "Object");
	setData(1, "Wall");
	setZValue(2);
}

WallObject::~WallObject(){
}

void WallObject::damage(const int &value){
	m_state -= value;

	if (m_state <= 0) emit deleteMe(this);
	else if (m_state <= 25) setPixmap(*m_wallState.at(3));
	else if (m_state <= 50) setPixmap(*m_wallState.at(2));
	else if (m_state <= 75) setPixmap(*m_wallState.at(1));
}

} // namespace

