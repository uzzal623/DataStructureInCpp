#include <iostream>
#include <limits>
using namespace std;

struct Line {
    long long slope, intercept;
    Line(long long slope = 0, long long intercept = numeric_limits<long long>::min())
        : slope(slope), intercept(intercept) {}
    
    long long getValue(long long x) {
        return slope * x + intercept;
    }
};

struct LiChaoTree {
    int size;
    vector<Line> tree;

    LiChaoTree(int n) : size(n) {
        tree.resize(4 * n, Line());
    }

    void addLine(Line newLine, int node, int l, int r) {
        int mid = (l + r) / 2;
        bool left = newLine.getValue(l) > tree[node].getValue(l);
        bool middle = newLine.getValue(mid) > tree[node].getValue(mid);

        if (middle) {
            swap(tree[node], newLine);
        }
        if (l == r) return;

        if (left != middle) {
            addLine(newLine, 2 * node, l, mid);
        } else {
            addLine(newLine, 2 * node + 1, mid + 1, r);
        }
    }

    void addLine(Line newLine) {
        addLine(newLine, 1, 0, size - 1);
    }

    long long query(int x, int node, int l, int r) {
        if (l == r) {
            return tree[node].getValue(x);
        }
        int mid = (l + r) / 2;
        if (x <= mid) {
            return max(tree[node].getValue(x), query(x, 2 * node, l, mid));
        } else {
            return max(tree[node].getValue(x), query(x, 2 * node + 1, mid + 1, r));
        }
    }

    long long query(int x) {
        return query(x, 1, 0, size - 1);
    }
};

int main() {
    LiChaoTree tree(10);
    tree.addLine(Line(2, 3));  // Line: y = 2x + 3
    tree.addLine(Line(-1, 10));  // Line: y = -x + 10
    cout << "Maximum value at x = 2: " << tree.query(2) << endl;
    return 0;
}
