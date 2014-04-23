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

#include "animation.h"

namespace KWB{

Animation::Animation(const int &fps): m_fps(fps), m_count(0), m_iterator(0), m_animating(false), m_externalTimer(false){
	m_timer = new QTimer(this);
	m_timer->setInterval(m_fps);

	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateCurrentFrame()));
}

Animation::Animation(QTimer *timer): m_fps(0), m_count(0), m_iterator(0), m_animating(false), m_externalTimer(true){
	connect(timer, SIGNAL(timeout()), this, SLOT(updateCurrentFrame()));
}

Animation::~Animation(){
}

void Animation::addPixmap(QPixmap *newFrame){
	m_frames << newFrame;

	m_count = m_frames.count();
}

QPixmap *Animation::currentFrame(){
	return m_frames.at(m_iterator);
}

void Animation::start(bool forward){
	m_animating = true;
	m_forward = forward;

	if (!m_externalTimer)
		m_timer->start();
}

void Animation::stop(){
	m_animating = false;

	if (!m_externalTimer)
		m_timer->stop();
}

bool Animation::isAnimating(){
	return m_animating;
}

void Animation::updateCurrentFrame(){
	if (m_forward)
		m_iterator = (m_iterator + 1) % m_count;
	else
		m_iterator = (m_iterator - 1 + m_count) % m_count;
}

} // namespace

