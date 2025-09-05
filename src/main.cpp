#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_set>


struct Box {

    Box(int bl, int tr) : bl_(bl), tr_(tr) {}

    bool operator==(const Box& other) const {
        return other.bl_ == this->bl_ && other.tr_ == this->tr_;
    }

    struct Hash {
        std::size_t operator()(const Box& b) const {
            std::size_t tr = std::hash<int>()(b.tr_);
            std::size_t bl = std::hash<int>()(b.bl_);
            return tr^(bl<<1);
        }
    };

    int bl_{0};
    int tr_{0};
};

struct BoxComparitor {

    bool operator()(const Box& B, const Box& A) {
        return (B.bl_ == A.bl_ && B.tr_ == A.tr_);
    }
    static bool compare(const Box& B, const Box& A) {
        return (B.bl_ == A.bl_ && B.tr_ == A.tr_);
    }

};


int main() {

    Box a(10, 5);
    Box b(15, 5);
    Box c(10, 5);

    std::vector<Box> boxes {a, b, c};

    std::cout << "----------------Setup Finsihed---------------------------------------------------" << std::endl;

    std::vector<Box> lambda_boxes;

    for(const auto& b:boxes) {
        if(lambda_boxes.empty()) {
            lambda_boxes.push_back(b);
            continue;
        }
        auto it = std::find_if(lambda_boxes.begin(), lambda_boxes.end(), [&](const Box& a){
            return (b.bl_ == a.bl_ && b.tr_ == a.tr_);
        });

        if( it == lambda_boxes.end()) {
            lambda_boxes.push_back(b);
        }
    }

    assert(lambda_boxes.size() == 2);
    assert(lambda_boxes[0] == a);
    assert(lambda_boxes[1] == b);

    std::cout << "----------------Lambda Tests Passed ---------------------------------------------" << std::endl;


    std::vector<Box> static_boxes;

    for(const auto& b:boxes) {
        if(static_boxes.empty()) {
            static_boxes.push_back(b);
            continue;
        }
        bool found = false;

        for(const auto& n_b:static_boxes) {
            if(BoxComparitor::compare(n_b, b)) {
                found = true;
            }
        }

        if(!found) {
            static_boxes.push_back(b);
        }
    }

    assert(static_boxes.size() == 2);
    assert(static_boxes[0] == a);
    assert(static_boxes[1] == b);

    std::cout << "----------------Static Function Tests Passed ------------------------------------" << std::endl;


    std::vector<Box> functor_boxes;
    BoxComparitor cmp;

    for(const auto& b:boxes) {
        if(functor_boxes.empty()) {
            functor_boxes.push_back(b);
            continue;
        }
        bool found = false;

        for(const auto& n_b:functor_boxes) {
            if(cmp(n_b, b)) {
                found = true;
            }
        }

        if(!found) {
            functor_boxes.push_back(b);
        }
    }

    assert(functor_boxes.size() == 2);
    assert(functor_boxes[0] == a);
    assert(functor_boxes[1] == b);

    std::cout << "----------------Functor Tests Passed --------------------------------------------" << std::endl;

    std::vector<Box> functor_lambda_boxes;
    BoxComparitor cmp_lambda;

    for(const auto& b:boxes) {
        if(functor_lambda_boxes.empty()) {
            functor_lambda_boxes.push_back(b);
            continue;
        }
        bool found = false;

        if (std::any_of(functor_lambda_boxes.begin(), functor_lambda_boxes.end(), [&](const Box& exisiting){
            return cmp_lambda(exisiting, b);
        })){
            found = true;
        }

        if(!found) {
            functor_lambda_boxes.push_back(b);
        }
    }

    assert(functor_lambda_boxes.size() == 2);
    assert(functor_lambda_boxes[0] == a);
    assert(functor_lambda_boxes[1] == b);

    std::cout << "----------------Functor In Lambda Tests Passed ----------------------------------" << std::endl;

    std::unordered_set<Box, Box::Hash> boxSet;

    for(const auto& b:boxes) {
        boxSet.insert(b);
    }

    assert(boxSet.size() == 2);
    Box non_exist(50, 100);
    assert(boxSet.count(a));
    assert(boxSet.count(b));
    assert(!boxSet.count(non_exist));

    std::cout << "----------------Hash Tests Passed -----------------------------------------------" << std::endl;

    return 0;

}
