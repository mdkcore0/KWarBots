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

#include <QString>

#include <KAboutData>
#include <KMessageBox>
#include <KApplication>
#include <KCmdLineArgs>
#include <KLocalizedString>

#include "menu.h"

int main(int argc, char **argv){
	KAboutData aboutData("kwarbots",
		   0,
		   ki18n("KWarBots"),
		   "1.0",
		   ki18n("KWarBots Programming Game"),
		   KAboutData::License_GPL,
		   ki18n("(c) 2009"),
		   ki18n("Program your own robot and fight"),
		   "http://thecoreme.org/blog/projects/kwarbots");
	aboutData.addAuthor(ki18n("Rodrigo \"MDK\" Oliveira"), ki18n("Main author, developer"), "mdkcore@gmail.com");

	KCmdLineArgs::init(argc, argv, &aboutData);
	KApplication app;

	KWB::Menu *menu = new KWB::Menu();
	menu->show();

	return app.exec();
}

