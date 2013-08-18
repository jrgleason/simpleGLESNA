#include <jni.h>
#include <errno.h>
#include <android_native_app_glue.h>
#include "Application.h"

void android_main(struct android_app* state)
{
  Application app(state);
  app_dummy();
  app.run();
}
