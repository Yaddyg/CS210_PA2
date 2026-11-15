#pragma once
#include "Scene.h"

// The whole story. It knows the first scene and nothing else.
//
// RULES (do not change):
//   - Keep every name and signature exactly as written.
//   - The private helpers must be recursive. No loops that walk down the tree.
//   - This class must work for ANY T. Never mention Moment in here.
template <typename T>
class StoryTree {
private:
    Scene<T>* root_;

    // TODO 6: how many scenes are in the story that starts at scene? DONE
    // An empty story has 0 scenes.
    int countScenes(Scene<T> *scene) const {
        if (scene == nullptr) {
            return 0;
        }
        return 1 + countScenes(scene->getChoice(0))
               + countScenes(scene->getChoice(1))
               + countScenes(scene->getChoice(2));
    }

    // TODO 7: how many endings are in the story that starts at scene? DONE
    int countEndings(Scene<T> *scene) const {
        if (scene == nullptr) {
            return 0;
        }
        if (scene->isEnding()) {
            return 1;
        }

        return countEndings(scene->getChoice(0))
               + countEndings(scene->getChoice(1))
               + countEndings(scene->getChoice(2));
    }

    // TODO 8: the most choices a player can make on the way to an ending. DONE
    // starting at scene. A single ending scene has height 0.
    // An empty story has height -1.
    int height(Scene<T> *scene) const {
        if (scene == nullptr) {
            return -1;
        }
        int height0 = height(scene->getChoice(0));
        int height1 = height(scene->getChoice(1));
        int height2 = height(scene->getChoice(2));

        int tallest = height0;

        if (height1 > tallest) {
            tallest = height1;
        }
        if (height2 > tallest) {
            tallest = height2;
        }
        return 1 + tallest;
    }



public:
    StoryTree() : root_(nullptr) {}

    ~StoryTree() {
        clear();
    }

    void setRoot(Scene<T>* root) {
        clear();
        root_ = root;
    }

    Scene<T>* getRoot() const {
        return root_;
    }

    bool isEmpty() const {
        return root_ == nullptr;
    }

    // TODO 9: free every scene in the story and leave the tree empty.
    // Hint: what does deleting a Scene already do for you?
    void clear() {
        delete root_;
        root_ = nullptr;

    }

    int countScenes() const {
        return countScenes(root_);
    }

    int countEndings() const {
        return countEndings(root_);
    }

    int height() const {
        return height(root_);
    }
};
