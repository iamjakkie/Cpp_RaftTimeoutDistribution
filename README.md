# Cpp_RaftTimeoutDistribution

The goal of this tiny program is to calculate and save the plot of:
- distribution of the generated timeouts for nodes in Raft
- number of collisions for a given number of machines & runs

The idea is to be aware that some nodes can keep on waking up in the exact same time and start requesting votes, what might affect your implementation of Raft algorithm.