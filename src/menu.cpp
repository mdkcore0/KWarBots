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

#include <QDebug>
#include <QVBoxLayout>

#include "menu.h"
#include "game.h"

//#include <kross/core/manager.h>

namespace KWB{

Menu::Menu(QWidget *parent): QWidget(parent){
	KWB::Game *game = new KWB::Game(this);

	game->show();
	//myObject = new MyObject(this);

	//execScriptFile(myObject, "script.py");
}

/*
void MainWindow::execScriptFile(MyObject *myobject, const QString &file){
	action = new Kross::Action(myobject, file);

	action->addObject(myobject, "myobject", Kross::ChildrenInterface::AutoConnectSignals);

	//action->setInterpreter("python");
	//action->setCode("print 'hey there'");
	action->setFile(file);
	action->trigger();

	myobject->callInit();

	//if (action->hadError())
	//	qDebug() << action->errorMessage();

	//connect(&Kross::Manager::self(), SIGNAL(started(Kross::Action *)),
	//		this, SLOT(started(Kross::Action *)));
	//connect(&Kross::Manager::self(), SIGNAL(finished(Kross::Action *)),
	//		this, SLOT(finished(Kross::Action *)));
}
*/
} // namespace

