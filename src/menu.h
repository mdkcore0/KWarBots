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

#ifndef __MENU_H__
#define __MENU_H__

#include <QWidget>
//#include <QComboBox>
//#include <QLabel>
//#include <QLineEdit>
//#include <kross/core/action.h>

//#include "myobject.h"
namespace KWB{

// this class describes the main window (like the menu, options, ...)
class Menu: public QWidget{
	Q_OBJECT
	
	public:
		Menu(QWidget *parent = 0);
		//void execScriptFile(MyObject *myobject, const QString &file);

	private:
		//MyObject *myObject;
		//Kross::Action *action;
//		QLineEdit *txtInputString;
//		QLabel *lblMessage;
//		QComboBox *cmbInterpreters;
};

} // namespace

#endif

