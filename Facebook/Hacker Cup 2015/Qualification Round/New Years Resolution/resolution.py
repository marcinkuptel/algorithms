#!/usr/bin/env python3

import sys
import os

class Case:
	def __init__(self, case_number, target, foods):
		self.case_number = case_number
		self.__target = target
		self.__foods = foods

	def __str__(self):
		return "Case #{0}: Target: {1}".format(self.case_number, self.__target)

	def answer(self):

		foods_count = len(self.__foods)

		for x in range(0, 2**foods_count):
			sum = [0, 0, 0]
			for y in range(0, foods_count):
				mask = 1 << y
				
				if x & mask:
					sum[0] += self.__foods[y][0]
					sum[1] += self.__foods[y][1]
					sum[2] += self.__foods[y][2]
			if sum[0] == self.__target[0] and sum[1] == self.__target[1] and sum[2] == self.__target[2]:
				return True
			elif sum[0] > self.__target[0] or sum[1] > self.__target[1] or sum[2] > self.__target[2]:
				continue

		return False

def solve(filename):
	fh = None
	try:
		fh = open(filename, encoding="utf8")
		print("### File opened!")

		cases = int(fh.readline().strip())
		print("Number of cases: {0}".format(cases))

		casesList = []

		for x in range(1, cases+1):
			target = fh.readline().strip()
			target_separated = target.split(' ')
			converted = list(map(lambda x: int(x), target_separated))
			foods_count = int(fh.readline().strip())
			foods = []
			for y in range(1, foods_count+1):
				line = fh.readline().strip()
				line_separated = line.split(' ')
				line_converted = list(map(lambda x: int(x), line_separated))
				foods.append(line_converted)

			case = Case(x, converted, foods)
			casesList.append(case)

		for case in casesList:
			print("Case #{0}: {1}".format(case.case_number, "yes" if case.answer() else "no"))

	except (FileNotFoundError, EnvironmentError, ValueError, KeyError) as err:
		print("{0}: import error: {1}".format(os.path.basename(sys.argv[0]), err))
	finally:
		if fh is not None:
			fh.close()

if __name__ == "__main__":
	if len(sys.argv) == 2:
		solve(sys.argv[1])
	else:
		print("Wrong number of parameters")