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

#include <QPainter>
#include <QPixmapCache>

#include "imageloader.h"

namespace KWB{

ImageLoader::ImageLoader(const QString &path){
	m_svg = new QSvgRenderer(path);

	m_base = QColor(192, 192, 192); // base changeable color
	m_alternate = QColor(128, 128, 128); // alternate changeable color
	m_alternate2 = QColor(255, 255, 255); // alternate changeable color 2

	m_fileName = path.mid(path.lastIndexOf("/") + 1).remove(".svgz");
}

QPixmap ImageLoader::retrieve(const QString &element, const QSize &size, const QColor &color){
	// caching
	QPixmap pixmap;
	if (QPixmapCache::find("kwb_" + m_fileName + element + color.name(), pixmap))
		return pixmap;

	// loading
	if (!m_svg->elementExists(element))
		return QPixmap();

	QImage temp(size, QImage::Format_ARGB32_Premultiplied);
	temp.fill(0);

	QPainter p(&temp);

	m_svg->render(&p, element, temp.rect());

	// colouring
	if (color != Qt::transparent){
		int i, j;
		QColor rgb;

		for (j = 0; j < size.height(); j++)
			for (i = 0; i < size.width(); i++){
				rgb = temp.pixel(i, j);

				if (rgb == m_base)
					temp.setPixel(i, j, color.rgb());
				else if (rgb == m_alternate)
					temp.setPixel(i, j, color.darker().rgb());
				else if (rgb == m_alternate2)
					temp.setPixel(i, j, color.lighter().rgb());
			}
	}

	// well done!
	p.end();

	pixmap = QPixmap::fromImage(temp);
	QPixmapCache::insert("kwb_" + m_fileName + element + color.name(), pixmap);

	return pixmap;
}

QPixmap ImageLoader::retrieve(const QString &element, const QSize &size, const QColor &color1, const QColor &color2){
	// caching
	QPixmap pixmap;
	if (QPixmapCache::find("kwb_" + m_fileName + element + color1.name() + color2.name(), pixmap))
		return pixmap;

	// loading
	if (!m_svg->elementExists(element))
		return QPixmap();

	QImage temp(size, QImage::Format_ARGB32_Premultiplied);
	temp.fill(0);

	QPainter p(&temp);

	m_svg->render(&p, element, temp.rect());

	// colouring
	int i, j;
	QColor rgb;

	for (j = 0; j < size.height(); j++)
		for (i = 0; i < size.width(); i++){
			rgb = temp.pixel(i, j);

			if (rgb == m_base)
				temp.setPixel(i, j, color1.rgb());
			else if (rgb == m_alternate)
				temp.setPixel(i, j, color2.rgb());
		}

	// well done!
	p.end();

	pixmap = QPixmap::fromImage(temp);
	QPixmapCache::insert("kwb_" + m_fileName + element + color1.name() + color2.name(), pixmap);

	return pixmap;
}

} // namespace

