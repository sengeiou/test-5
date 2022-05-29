#include <nnstreamer.h>
#include <nnstreamer-single.h>
#include <stdint.h>
#include <glib.h>
#include <glib/gstdio.h> /* GStatBuf */

#include "tct_common.h"

#define API_NAMESPACE   "nnstreamer"
#define FEATURE_ML    "http://tizen.org/feature/machine_learning"
#define FEATURE_ML_INFERENCE    "http://tizen.org/feature/machine_learning.inference"
#define SLEEP_TIME  1000000

#define IS_SUPPORT_FEATURE \
do { \
  if (!feature_ml || !feature_ml_inf) { \
    FPRINTF("[%s][%d][%s] Machine Learning feature is not supported!\\n", __FILE__, __LINE__, __FUNCTION__); \
    return 0; \
  } \
} while (0)

static bool feature_ml;
static bool feature_ml_inf;

#define wait_for_start(handle, state, status) \
do {\
  int counter = 0;\
  while ((state == ML_PIPELINE_STATE_PAUSED || \
          state == ML_PIPELINE_STATE_READY) && counter < 20) {\
    g_usleep (SLEEP_TIME);\
    counter ++;\
    status = ml_pipeline_get_state (handle, &state);\
    assert_eq (status, ML_ERROR_NONE);\
  }\
} while (0)

/**
 * @brief Struct to check the pipeline state changes.
 */
typedef struct
{
  gboolean paused;
  gboolean playing;
} TestPipeState;

/**
 * @function		test_pipe_state_callback
 * @description Pipeline state changed callback
 */
static void
test_pipe_state_callback (ml_pipeline_state_e state, void *user_data)
{
  TestPipeState *pipe_state;

  pipe_state = (TestPipeState *) user_data;

  switch (state) {
    case ML_PIPELINE_STATE_PAUSED:
      pipe_state->paused = TRUE;
      break;
    case ML_PIPELINE_STATE_PLAYING:
      pipe_state->playing = TRUE;
      break;
    default:
      break;
  }
}

/**
 * @function		test_sink_callback_count
 * @description A tensor-sink callback for sink handle in a pipeline
 */
static void
test_sink_callback_count (const ml_tensors_data_h data,
    const ml_tensors_info_h info, void *user_data)
{
  guint *count = (guint *) user_data;

  *count = *count + 1;
}

/**
 * @function		test_sink_callback_dm01
 * @description A tensor-sink callback for sink handle in a pipeline
 */
static void
test_sink_callback_dm01 (const ml_tensors_data_h data,
    const ml_tensors_info_h info, void *user_data)
{
  gchar *filepath = (gchar *) user_data;
  unsigned int i, num = 0;
  void *data_ptr;
  size_t data_size;
  int status;
  FILE *fp = g_fopen (filepath, "a");

  if (fp == NULL)
    return;

  ml_tensors_info_get_count (info, &num);

  for (i = 0; i < num; i++) {
    status = ml_tensors_data_get_tensor_data (data, i, &data_ptr, &data_size);
    if (status == ML_ERROR_NONE)
      fwrite (data_ptr, data_size, 1, fp);
  }

  fclose (fp);
}

/**
 * @function		file_cmp
 * @description compare the two files.
 */
static int
file_cmp (const gchar * f1, const gchar * f2)
{
  gboolean r;
  gchar *content1, *content2;
  gsize len1, len2;
  int cmp = 0;

  r = g_file_get_contents (f1, &content1, &len1, NULL);
  if (r != TRUE)
    return -1;

  r = g_file_get_contents (f2, &content2, &len2, NULL);
  if (r != TRUE) {
    g_free (content1);
    return -2;
  }

  if (len1 == len2) {
    cmp = memcmp (content1, content2, len1);
  } else {
    cmp = 1;
  }

  g_free (content1);
  g_free (content2);

  return cmp;
}
