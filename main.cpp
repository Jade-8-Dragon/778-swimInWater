#include <vector>
#include <iostream>
#include <tuple>
#include <queue>
#include <functional>
#include <set>

using namespace std;

class Solution {
    public:
        int swimInWater(vector<vector<int>> &grid) {

            //declare outer edges of the grid
            int max_r = grid.size(), max_c = grid[0].size();
            //queue to pursue whatever path is the most promising at any given point
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
            //array of pairs to use to analyse all ajdacent cells for their relative height
            vector<pair<int, int>> direction = {{1,0},{0,1},{-1,0},{0,-1}};
            //a set(array with only unique elements) containing every cell already visited. They'll be checked with .count()
            set<pair<int, int>> seen;
            //prep the priority queue by pushing the top left corner of the grid
            pq.push({grid[0][0], 0, 0});

            //run while pq still has cells in it, a later return statement will also offer a way out
            while (!pq.empty()) {
                //instance variables for each cell in the queue
                auto [max_d, r, c] = pq.top();
                pq.pop();

                //if the current cell is at the desired location (bottom right) then we have the answer!
                if (r == max_r - 1 and c == max_c - 1) return max_d;

                //if this cell has already been covered then skip to the next iteration
                if (seen.count({r, c})) continue;
                //if not then make it seen
                seen.insert({r, c});

                //run through direction with dr and dc
                for (auto [dr, dc] : direction) {
                    //declare new coordinates surrounding the original cell
                    int nr = dr + r, nc = dc + c;
                    //if the cell being tested is within the proper bounds and not yet seen then proceed
                    if (nr >= 0 and nr < max_r and nc >= 0 and nc < max_c and !seen.count({nr, nc})) {
                        //maintain the highest value seen up to this point
                        int new_d = max(max_d, grid[nr][nc]);
                        //new cell with the continuous max and the new coordinates
                        pq.push({new_d, nr, nc});
                    }
                }

            }

            //else return -1
            return -1;
        }
};

int main() {
    Solution sol;

    //test case #1
    vector<vector<int>> test1;
    test1.push_back({0,2});
    test1.push_back({1,3});

    //test case #2
    vector<vector<int>> test2;
    test2.push_back({0,1,2,3,4});
    test2.push_back({24,23,22,21,5});
    test2.push_back({12,13,14,15,16});
    test2.push_back({11,17,18,19,20});
    test2.push_back({10,9,8,7,6});

    //print both test cases
    cout << "Test case #1" << endl << "Expected output: 3" << endl << "Actual output: " << sol.swimInWater(test1) << endl << endl;
    cout << "Test case #2" << endl << "Expected output: 16" << endl << "Actual output: " << sol.swimInWater(test2) << endl;

    return 0;
}