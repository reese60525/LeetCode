import random


def generate_test_data(n, m):
    """
    Generates test data for two trees with n and m nodes.
    The edges are formatted as [[node0, node1], ...].
    """

    def generate_tree_edges(node_count):
        edges = []
        for i in range(1, node_count):
            parent = random.randint(0, i - 1)
            edges.append([parent, i])
        return edges

    # Generate edges for two trees
    edges1 = generate_tree_edges(n)
    edges2 = generate_tree_edges(m)

    return edges1, edges2


# Generate test data
n, m = 10**2, 10**2
edges1, edges2 = generate_test_data(n, m)

# Save test data to files for user to inspect or use
import json

with open("/edges1.json", "w") as f:
    json.dump(edges1, f)
with open("d:/code/onlinejudge/edges2.json", "w") as f:
    json.dump(edges2, f)

# Output success message
"Test data generated and saved as edges1.json and edges2.json"
