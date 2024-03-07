#include <node.h>
#include <windows.h>

using namespace v8;

// Function to check if the mouse has moved
void HasMouseMoved(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Get the argument (callback function)
    Local<Function> callback = Local<Function>::Cast(args[0]);

    // Get the last mouse position
    POINT lastMousePos;
    GetCursorPos(&lastMousePos);

    // Set up an interval to check for mouse movement
    while (true) {
        Sleep(1000); // Sleep for 1 second (adjust as needed)

        POINT currentMousePos;
        GetCursorPos(&currentMousePos);

        // Check if the mouse has moved
        if (currentMousePos.x != lastMousePos.x || currentMousePos.y != lastMousePos.y) {
            // Call the callback function with true (mouse has moved)
            const unsigned argc = 1;
            Local<Value> argv[argc] = {Boolean::New(isolate, true)};
            callback->Call(Null(isolate), argc, argv);
            return;
        }
    }
}

// Initialize the addon
void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "hasMouseMoved", HasMouseMoved);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
