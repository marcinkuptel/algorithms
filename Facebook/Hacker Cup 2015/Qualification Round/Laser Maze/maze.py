#!/usr/bin/env python3

import sys
import os
import collections
import operator

class LaserMazeCase:

	start = (-1, -1)
	goal = (-1, -1)

	def __init__(self, caseNumber, maze):
		self.maze = maze
		self.caseNumber = caseNumber
		self.queue = collections.deque()
		self.parents = []
		for line in self.maze:
			self.parents.append([-1]*len(self.maze[0]))
		self.pathLength = []
		for line in self.maze:
			self.pathLength.append([-1]*len(self.maze[0]))	
		self.dangerous = self.precomputeDangerousCells()
		print(self.dangerous)

	def printSolution(self):
		print("Case #{0}".format(self.caseNumber))
		self.start = self.findStart()
		self.goal = self.findGoal()
		seenPositions = set()

		if self.start != (-1, -1) and self.goal != (-1, -1):
			self.queue.appendleft(self.start)
			seenPositions.add(self.start)
			self.setPathLength(self.start, 0)
			self.setParent(self.start, self.start)

			while(len(self.queue) != 0):
				current = self.queue.pop()
				pathLength = self.getPathLength(current)
				positions = self.validPositionsFromPosition(current, seenPositions, pathLength+1)
				for position in positions:
					self.setParent(position, current)
					self.setPathLength(position, self.getPathLength(current) + 1)
					seenPositions.add(position)
					self.queue.appendleft(position)
			for line in self.pathLength:
				print(line)
		else:
			print("### Could not find start or goal!")

		#print("Case #{0}: ".format(self.caseNumber))

	def findStart(self):
		return self.findCharacter('S')

	def findGoal(self):
		return self.findCharacter('G')

	def findCharacter(self, char):
		for i in range(0, len(self.maze)):
			line = self.maze[i]
			for j in range(0, len(line)):
				if line[j] == char:
					return (j, i)
		return (-1, -1)

	def validPositionsFromPosition(self, position, visited, pathLength):
		validPositions = []
		moves = [(0, -1), (+1, 0), (0, +1), (-1, 0)]
		dangerousCells = self.dangerous[pathLength%4]
		for move in moves:
			pos = (position[0] + move[0], position[1] + move[1])
			if pos not in visited and pos not in dangerousCells and self.inside(pos):
				if self.maze[pos[1]][pos[0]] in ".G":
					validPositions.append(pos)
		return validPositions

	def setParent(self, position, parent):
		self.parents[position[1]][position[0]] = parent

	def getParent(self, position):
		return self.parents[position[1]][position[0]]

	def setPathLength(self, position, length):
		self.pathLength[position[1]][position[0]] = length

	def getPathLength(self, position):
		length = 0
		try:
			length = self.pathLength[position[1]][position[0]]
		except TypeError as err:
			print("Error: Case #{0}, Position:{1}, {2}".format(self.caseNumber, position, err))
		return length

	def precomputeDangerousCells(self):
		cells = (set(), set(), set(), set())
		for x in range(0, 4):
			for i in range(0, len(self.maze)):
				for j in range(0, len(self.maze[0])):
					char = self.maze[i][j]
					if char in "<^>v":
						dangerousCells = self.dangerousCellsForTurret((j, i), x)
						cells[x].update(dangerousCells)
		return cells

	def dangerousCellsForTurret(self, turretPosition, rotation):
		dangerousCells = []
		turrets = "<^>v"
		moveVectors = ((-1, 0), (0, -1), (1, 0), (0, 1))
		char = self.maze[turretPosition[1]][turretPosition[0]]
		index = turrets.index(char)
		nextPosition = (index + rotation)%4
		moveVector = moveVectors[nextPosition]
		tempChar = '.'
		position = tuple(map(operator.add, turretPosition, moveVector))
		
		while self.inside(position):
			tempChar = self.maze[position[1]][position[0]]
			if tempChar not in ".G":
				break
			dangerousCells.append(position)
			position = tuple(map(operator.add, position, moveVector))

		return dangerousCells

	def inside(self, pos):
		if pos[0] >=0 and pos[0] < len(self.maze[0]):
			if pos[1] >= 0 and pos[1] < len(self.maze):
				return True
		return False

class LaserMaze:
	def __init__(self, mazeCases):
		self.mazeCases = mazeCases

	def printSolution(self):
		for mazeCase in self.mazeCases:
			mazeCase.printSolution()

class LaserMazeReader:
	@classmethod
	def laserMazeFromFile(cls, fileLocation):
		fh = None
		laserMaze = None
		try:
			fh = open(fileLocation, encoding="utf8")
			print("### File opened")

			caseCount = int(fh.readline().strip())
			laserMazeCases = []

			for case in range(0, caseCount):
				(height, width) = map(int, fh.readline().strip().split(' '))
				maze = []
				for x in range(0, height):
					line = fh.readline().strip()
					maze.append(line)

				laserMazeCase = LaserMazeCase(case + 1, maze)
				laserMazeCases.append(laserMazeCase)

			laserMaze = LaserMaze(laserMazeCases)

		except (FileNotFoundError, EnvironmentError, ValueError, KeyError) as err:
			print("{0}: import error: {1}".format(os.path.basename(sys.argv[0]), err))
		finally:
			if fh is not None:
				fh.close()
				print("### File closed")

		return laserMaze

if __name__ == "__main__":
	if len(sys.argv) == 2:
		laserMaze = LaserMazeReader.laserMazeFromFile(sys.argv[1])
		laserMaze.printSolution()
	else:
		print("Wrong number of parameters!")