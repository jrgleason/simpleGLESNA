#include "Application.h"

int Application::initWindow(android_app *app)
{
    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 5,
            EGL_GREEN_SIZE, 6,
            EGL_RED_SIZE, 5,
            EGL_DEPTH_SIZE, 1,
            EGL_NONE
    };

    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    LOGI("The pointer is %d\n Currently it is %d",display, this->display);
    eglInitialize(display, 0, 0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);


    EGLint context_attr[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    surface = eglCreateWindowSurface(display, config, app->window, NULL);
    context = eglCreateContext(display, config, NULL, context_attr);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);
    LOGI("The pointer is %d\n",display);
    LOGI("+++++++++++++++++++++++++++++++++++++++++++++++");
    LOGI((const char*)glGetString(GL_VERSION));
    LOGI("+++++++++++++++++++++++++++++++++++++++++++++++");
    LOGI("Getting Display");
    this->display = display;
    LOGI("Getting Context");
    // this->context = context;
    // this->surface = surface;
    // this->width = w;
    // this->height = h;
    positInit();
    LOGI("Finishing");
    return 0;
}

void Application::positInit(){
  
}

static void handle_cmd(struct android_app* app, int32_t cmd){
  Application *glesApp = (Application *)app->userData;
  glesApp->handleCommand(app, cmd);
}

void Application::handleCommand(struct android_app* app, int32_t cmd) {
  switch (cmd) {
  case APP_CMD_SAVE_STATE:
      break;
  case APP_CMD_INIT_WINDOW:
      if (app->window != NULL) {
          LOGI("Initing window it was not null");
          initWindow(app);
      }
      else{
          LOGE("Window was null");
      }
      break;
  case APP_CMD_TERM_WINDOW:
      // term_display();
      break;
  case APP_CMD_GAINED_FOCUS:
      break;
  case APP_CMD_LOST_FOCUS:
      break;
  }
}

void Application::run(){
  androidContext->onAppCmd = handle_cmd;
  while (1) {
    int ident;
    int events;
    struct android_poll_source* source;
    while ((ident=ALooper_pollAll(-1, NULL, &events,
                (void**)&source)) >= 0) {
      if (source != NULL) {
        source->process(androidContext, source);
      }
      if (androidContext->destroyRequested != 0) {
        // term_display();
        return;
      }
    }
  }
}
