//
// Created by Andrew Graser on 2/26/2024.
//

#ifndef SANDBOX_ENTRYPOINT_H
#define SANDBOX_ENTRYPOINT_H

extern Tungsten::Application* CreateApplication();

int main(int argc, char *argv[]) {
    auto app = CreateApplication();
    app->Run();

    delete app;

    return 0;
}

#endif //SANDBOX_ENTRYPOINT_H
