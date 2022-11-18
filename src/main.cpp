#include "Scene.h"

using namespace std;

int main(int argc, char* argv[]) {
    Scene *scene = new Scene();
    scene->go(argc, argv);
    delete scene;
    return 0;
}
