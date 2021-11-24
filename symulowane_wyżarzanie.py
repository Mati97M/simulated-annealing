import random
import math

#####################algorythm settings
T = 1.0
frozing_factor = 0.8

steps_number = 10
tries = 5

####################functions
def given_function(x):
	return 3 * math.sin(math.pi * x / 5) + math.sin(math.pi * x) ##3sin(πx / 5) + sin(πx)

def getRange(x):
	if x < 0:
		print("Warning! x < 0 !!!")	##[0, 10]           ##[x-2T, x+2T]
	a = x - 2.0 * T
	b = x + 2.0 * T
	if a < 0:
		a = 0.0
	return [a,b]

def random_on_try(x):
	result = 0.0
	range = getRange(x)
	a = range[0]
	b =  range[1]
	if a > b:
		print("Warning begin is bigger than end!")
	else:
		result = random.uniform(a,b)
	return result

#####################################################


	##initializing x & F(x)
x = random.uniform(0.0,10.0)
Fx = given_function(x)
print("initial x = {}    initial F(x) = {}".format(x,Fx))

##maksimum funkcji f(x) = 3sin(πx / 5) + sin(πx)
for i in range(0, steps_number):
	print("Current tempterature:    {}".format(T))
	for j in range(0, tries):
		temp_x = random_on_try(x)
		temp_Fx = given_function(temp_x)
		if temp_Fx > Fx:   ##dla maksymalizacji
			x = temp_x
			Fx = temp_Fx
			print("better solution found in step: {}\t| try: {}".format(i,j))
			print("x = {} \tF(x) = {}".format(x,Fx))
		else:
			offer_to_accept = math.exp((temp_Fx - Fx) / T)
			level_of_accepting = random.uniform(0.0,1.0)
			if offer_to_accept > level_of_accepting:   ##update x F(x)
				x = temp_x
				Fx = temp_Fx
				print("Worse solution excepeted in step: {} | try: {}".format(i,j))
				print("x = {}   F(x) = {}".format(x,Fx))
				print("level_of_accepting: {}   offer_to_accept was: {}".format(level_of_accepting,offer_to_accept ))

	T *= frozing_factor ## updating temperature
	print("solution:    x = {}   F(x) = {}".format(x,Fx))
