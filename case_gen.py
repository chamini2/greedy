#! /usr/bin/env python
import sys
import random


number_of_cases = {}
number_of_cases["big"] = 20
number_of_cases["medium"] = 15
number_of_cases["small"] = 10

number_of_vertex = {}
number_of_vertex["big"] = [90000, 90000] # 92k nodes maximum
number_of_vertex["medium"] = [100, 500]
number_of_vertex["small"] = [1, 20]

number_of_queries = {}
number_of_queries["big"] = [25, 35]
number_of_queries["medium"] = [15, 25]
number_of_queries["small"] = [1, 10]

query_type = ["Q", "R"]

if len(sys.argv) < 2:
    print "Needs to specify problem number and case type <small, big or medium>"
    exit(1)


problem      = sys.argv[1]
problem_type = sys.argv[2]

print "Generating " + problem_type + " test case for problem " + problem

f = open(problem + problem_type + ".in", 'w')

cases = number_of_cases[problem_type]

f.write(str(cases) + '\n\n')

vertex_range = number_of_vertex[problem_type]
for i in xrange(0, cases): 
    vertex = random.randint(vertex_range[0], vertex_range[1])
    f.write(str(vertex) + '\n')
    for j in xrange(1, vertex):
            if j != vertex:
                f.write(str(j) + " " + str(j + 1) + '\n') 

    queries = number_of_queries[problem_type][random.randint(0,1)]
    f.write(str(queries) + '\n')

    for j in xrange(0, queries):
        qtype = random.randint(0,1)
        f.write(query_type[qtype])
        if query_type[qtype] == "R":
            element = random.randint(1, vertex)
            f.write(" " + str(element))

        f.write('\n')
