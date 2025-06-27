
#include<bits/stdc++.h>
#include "../Model/RubiksCube.h"


#ifndef IDASTARSOLVER_H
#define IDASTARSOLVER_H

template<typename T, typename H>
class IDAstarSolver {
private:
    CornerPatternDatabase cornerDB;
    vector<RubiksCube::MOVE> moves;
    unordered_map<T,RubiksCube::MOVE,H> move_done;
    unordered_map<T,bool,H> visited;

    struct Node {
        T cube;
        int depth;
        int estimate;

        Node(T _cube, int _depth, int _estimate) : cube(_cube), depth(_depth), estimate(_estimate){};
    };

    struct compareCube {
        bool operator()(pair<Node,int> const&p1, pair<Node,int> const&p2) {
            auto n1 = p1.first;
            auto n2 = p2.first;

            if (n1.depth + n1.estimate == n2.depth + n2.estimate) {
                return n1.estimate > n2.estimate;
            }else {
                return n1.depth + n1.estimate > n2.depth + n2.estimate;
            }
        }
    };


    void resetStructure() {
        moves.clear();
        visited.clear();
        move_done.clear();
    }

    // returns {solved cube, bound}: if the cube was solved
    // returns {rubiksCube, next bound}: if the cube was not solved

    pair<T,int> IDAstar(int bound) {
        // priority queue contains pair(Node, move done to reach that)

        priority_queue<pair<Node,int>,vector<pair<Node,int>>,compareCube> pq;
        Node start = Node(rubiksCube, 0, 0);
        pq.push_back(make_pair(start,0));

        int next_bound = 100;

        while (!pq.empty()) {
            auto p = pq.top();
            Node node = p.first;

            pq.pop();

            if (visited[node.cube]) continue;

            visited[node.cube] = true;
            move_done[node.cube] = RubiksCube::MOVE(p.second);

            if (node.cube.isSolved()) return make_pair(node.cube,bound);

            node.depth ++;
            for (int i=0;i<18;i++) {
                auto curr_move = RubiksCube::MOVE(i);
                node.cube.move(curr_move);

                if (!visited[node.cube]) {
                    node.estimate = 0;
                    if (node.depth + node.estimate > bound) {
                        next_bound = min(next_bound, node.depth + node.estimate);
                    }else {
                        pq.push({node,i});
                    }
                }
                node.cube.invert(curr_move);
            }
        }

        return make_pair(rubiksCube, next_bound);
    }

public:
    T rubiksCube;

    IDAstarSolver(T _rubiksCube) {
        rubiksCube = _rubiksCube;

    }

    vector<RubiksCube::MOVE> solve() {
        int bound = 1;

        auto p = IDAstar((bound));

        while (p.second != bound) {
            resetStructure();
            bound = p.second;
            bound = IDAstar(bound);
        }

        T solved_cube = p.first;

        T curr_cube = solved_cube;
        while (curr_cube != rubiksCube) {
            RubiksCube::MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }

        rubiksCube = solved_cube;
        reverse(moves.begin(),moves.end());

        return moves;
    }
};


#endif //IDASTARSOLVER_H
