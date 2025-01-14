//https://en.wikipedia.org/wiki/Cartesian_tree
//Runs in O(n)
//Example application: you can solve https://codeforces.com/contest/1998/problem/E1 in linear time.

tuple<vector<int>, vector<int>, int> buildCartesianTreeMax(const vector<int> &A)
{
    int n = (int)A.size();
    vector<int> left(n, -1), right(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        int last = -1;
        while (!s.empty() && A[s.top()] < A[i]) {
            last = s.top();
            s.pop();
        }
        if (!s.empty()) {
            right[s.top()] = i;
        }
        if (last != -1) {
            left[i] = last;
        }
        s.push(i);
    }
    int root = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] > A[root]) {
            root = i;
        }
    }
    return make_tuple(left, right, root);
}
