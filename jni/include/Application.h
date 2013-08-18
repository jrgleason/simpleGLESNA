#ifndef APPLICATION_H
#define APPLICATION_H

#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <android/native_activity.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))


class Application{
  public: 
        Application(android_app *context)
        {
            this->display = EGL_NO_DISPLAY;
            this->surface = EGL_NO_SURFACE;
            this->context = EGL_NO_CONTEXT;
            this->width = 0;
            this->height = 0;
            this->androidContext = context;
        }
        int initWindow(android_app *app);
        void handleCommand(struct android_app* app, int32_t cmd);        
        void run();
        void positInit();
  protected:
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
        android_app *androidContext;
        int width;
        int height;
        GLuint shaderProgramObject;  
};
#endif
