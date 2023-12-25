import networkx
import sys
import os
from collections import defaultdict
import matplotlib.pyplot as plt

file = open(sys.argv[1]).read().strip()
lines = file.split('\n')

connections = defaultdict(set)
for line in lines:
    module, connected_modules = line.split(':')
    for connected_module in connected_modules.split():
        connections[module].add(connected_module)
        connections[connected_module].add(module)

graph = networkx.DiGraph()
for module, connected_modules in connections.items():
    for connected_module in connected_modules:
        graph.add_edge(module, connected_module, capacity=1.0)
        graph.add_edge(connected_module, module, capacity=1.0)


for source_module in [list(connections.keys())[0]]:
    for target_module in connections.keys():
        if source_module != target_module:
            cut_value, (left_modules, right_modules) = networkx.minimum_cut(graph, source_module, target_module)
            if cut_value == 3:
                print("Part One: ", len(left_modules)*len(right_modules))
                break

if(len(sys.argv) > 2):
    print("Generating graph...", end='\r')
    networkx.draw(graph, with_labels=True)
    print("Saving graph...    ", end='\r')
    plt.savefig(sys.argv[2])
    if os.path.exists(sys.argv[2]) and os.path.getsize(sys.argv[2]) > 0:
        print("Graph saved to ", sys.argv[2])
    else:
        print("Failed to save graph to ", sys.argv[2])
    