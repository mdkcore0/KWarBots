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

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <QTimer>
#include <QObject>
#include <QPixmap>

#include "shared.h"

namespace KWB{

// this class defines an Animation class for KWarBots
class Animation: public QObject{
	Q_OBJECT

	public:
		Animation(const int&);
		Animation(QTimer *);
		~Animation();

		// add a pixmap to the animation
		void addPixmap(QPixmap*);
		// return the current frame
		QPixmap *currentFrame();

		// start animation
		void start(bool forward = true);
		// stop animation
		void stop();
		// return the status of the animation (running == true)
		bool isAnimating();

	private slots:
		void updateCurrentFrame();

	private:
		// forward or backward?
		bool m_forward;

		// frames of the object
		Frames m_frames;

		QTimer *m_timer;
		int m_fps;
		int m_count;
		int m_iterator;
		bool m_animating;
		bool m_externalTimer;
};

} // namespace

#endif

