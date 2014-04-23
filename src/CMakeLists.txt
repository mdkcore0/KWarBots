set(kwarbots_SRCS
	main.cpp
	menu.cpp
	game.cpp
	battlearea.cpp
	robot.cpp
	object.cpp
	robotobject.cpp
	tileobject.cpp
	blockobject.cpp
	wallobject.cpp
	waterobject.cpp
	terrainobject.cpp
	map.cpp
	imageloader.cpp
	animation.cpp
	botpack.cpp
	ammoitem.cpp
	energyitem.cpp
	weaponitem.cpp
	bulletobject.cpp
	)

kde4_add_executable(kwarbots ${kwarbots_SRCS})
target_link_libraries(kwarbots ${KDE4_KDEUI_LIBS} ${KDE4_KROSSUI_LIBS})

