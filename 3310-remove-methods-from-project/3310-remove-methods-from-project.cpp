class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
         vector<bool> isSuspicious(n, false);
      
        // Track visited nodes for the second DFS
        vector<bool> visited(n, false);
      
        // Adjacency lists for the graph
        vector<vector<int>> undirectedGraph(n);  // Bidirectional edges
        vector<vector<int>> directedGraph(n);    // Original directed edges
      
        // Build both directed and undirected graphs from invocations
        for (const auto& invocation : invocations) {
            int caller = invocation[0];
            int callee = invocation[1];
          
            // Build undirected graph (both directions)
            undirectedGraph[caller].push_back(callee);
            undirectedGraph[callee].push_back(caller);
          
            // Build directed graph (original direction only)
            directedGraph[caller].push_back(callee);
        }
      
        // First DFS: Mark all methods reachable from the buggy method k as suspicious
        // Following the directed edges (caller -> callee)
        auto markSuspiciousFromBuggy = [&](this auto&& markSuspiciousFromBuggy, int currentMethod) -> void {
            isSuspicious[currentMethod] = true;
          
            // Mark all methods that this method calls as suspicious
            for (int calledMethod : directedGraph[currentMethod]) {
                if (!isSuspicious[calledMethod]) {
                    markSuspiciousFromBuggy(calledMethod);
                }
            }
        };
      
        // Start marking suspicious methods from the known buggy method k
        markSuspiciousFromBuggy(k);
      
        // Second DFS: Starting from non-suspicious methods, traverse the undirected graph
        // If we can reach suspicious methods from non-suspicious ones, 
        // those suspicious methods cannot be removed (they're called by safe code)
        auto markConnectedAsNonRemovable = [&](this auto&& markConnectedAsNonRemovable, int currentMethod) -> void {
            visited[currentMethod] = true;
          
            // Traverse all connected methods in the undirected graph
            for (int connectedMethod : undirectedGraph[currentMethod]) {
                if (!visited[connectedMethod]) {
                    // If we reach a suspicious method from a non-suspicious one,
                    // mark it as non-suspicious (cannot be removed)
                    isSuspicious[connectedMethod] = false;
                    markConnectedAsNonRemovable(connectedMethod);
                }
            }
        };
      
        // Check all non-suspicious methods and mark their connected components
        for (int methodId = 0; methodId < n; ++methodId) {
            if (!isSuspicious[methodId] && !visited[methodId]) {
                markConnectedAsNonRemovable(methodId);
            }
        }
      
        // Collect all methods that are not suspicious (these are the remaining methods)
        vector<int> remainingMethodsList;
        for (int methodId = 0; methodId < n; ++methodId) {
            if (!isSuspicious[methodId]) {
                remainingMethodsList.push_back(methodId);
            }
        }
      
        return remainingMethodsList;
    }
};