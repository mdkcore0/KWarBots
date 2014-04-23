#!/usr/bin/env kross

import sys
import Robot

count = 50
forward = False
shots = 0

def main():
	global count, forward, shots

	if (Robot.isMoving() == False & count == 0):
		Robot.moveForward()

	if (Robot.collided() == True):
		Robot.moveBackward()
		forward = True

	if (count == 0):
		Robot.stop()

		if (shots < 10):
			shotRet = Robot.shot()
			if (shotRet == Robot.ShotOk):
				shots += 1
			elif (shotRet == Robot.ShotNoMoreAmmo):
				Robot.invertMove()
		else:
			shots = 0
			count = 50
			forward = False
	elif (forward):
		count -= 1

