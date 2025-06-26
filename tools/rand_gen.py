import random
import sys

MAX = 2147483647
MIN = -2147483648
RAN = 500


for i in range (RAN):
	x = random.randint(MIN, MAX)
	print(x, end="")
	if i != RAN - 1:
		print(" ", end="")
