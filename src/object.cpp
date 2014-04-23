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

#include "object.h"

namespace KWB{

Object::Object(const QPoint &pos): m_pos(position(pos)){
// for animated ones
	setOffset(-(QPoint(SIZE / 2, SIZE / 2)));
	setPos(m_pos);
}

Object::Object(const QString &imageFile, const QPoint &pos): m_imageFile(imageFile), m_pos(position(pos)){
	setPos(m_pos); // TODO
}

Object::Object(const QString &imageFile): m_imageFile(imageFile){
}

Object::~Object(){
}

void Object::update(){
	// will control the sprites
	setPixmap(*m_animation->currentFrame());
}

QString Object::kind() const{
	return data(0).toString();
}

QString Object::name() const{
	return data(1).toString();
}

} // namespace

