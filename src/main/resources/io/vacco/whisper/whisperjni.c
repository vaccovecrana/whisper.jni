#include <stdlib.h>
#include <string.h>
#include <jni.h>
#include "whisper.h"

// Global references
static JavaVM *gJvm = NULL;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    gJvm = vm;
    return JNI_VERSION_1_6;
}

JNIEXPORT jlong JNICALL Java_io_vacco_whisper_Wp_initWhisper(JNIEnv *env, jclass clazz,
                                                        jstring jModelPath, jboolean jUseGpu, jint jGpuDevice,
                                                        jboolean jDtwTokenTimestamps, jstring jDtwAheadsPreset) {
    const char *modelPath = (*env)->GetStringUTFChars(env, jModelPath, NULL);
    const char *dtwAheadsPresetStr = (*env)->GetStringUTFChars(env, jDtwAheadsPreset, NULL);
    enum whisper_alignment_heads_preset dtwAheadsPreset;

    if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_NONE") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_NONE;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_N_TOP_MOST") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_N_TOP_MOST;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_CUSTOM") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_CUSTOM;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_TINY_EN") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_TINY_EN;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_TINY") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_TINY;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_BASE_EN") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_BASE_EN;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_BASE") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_BASE;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_SMALL_EN") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_SMALL_EN;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_SMALL") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_SMALL;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_MEDIUM_EN") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_MEDIUM_EN;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_MEDIUM") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_MEDIUM;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_LARGE_V1") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_LARGE_V1;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_LARGE_V2") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_LARGE_V2;
    } else if (strcmp(dtwAheadsPresetStr, "WHISPER_AHEADS_LARGE_V3") == 0) {
        dtwAheadsPreset = WHISPER_AHEADS_LARGE_V3;
    } else {
        dtwAheadsPreset = WHISPER_AHEADS_NONE;
    }

    struct whisper_context_params params;
    params.use_gpu = jUseGpu;
    params.gpu_device = jGpuDevice;
    params.dtw_token_timestamps = jDtwTokenTimestamps;
    params.dtw_aheads_preset = dtwAheadsPreset;

    struct whisper_context *context = whisper_init_from_file_with_params(modelPath, params);

    (*env)->ReleaseStringUTFChars(env, jModelPath, modelPath);
    (*env)->ReleaseStringUTFChars(env, jDtwAheadsPreset, dtwAheadsPresetStr);

    return (jlong) context;
}

JNIEXPORT void JNICALL Java_io_vacco_whisper_Wp_freeWhisper(JNIEnv *env, jclass clazz, jlong contextPointer) {
    struct whisper_context *context = (struct whisper_context *) contextPointer;
    whisper_free(context);
}

JNIEXPORT jlong JNICALL Java_io_vacco_whisper_Wp_createWhisperFullParams(JNIEnv *env, jclass clazz,
    jstring jStrategy,
    jint jNThreads, jint jNMaxTextCtx, jint jOffsetMs, jint jDurationMs,
    jboolean jTranslate, jboolean jNoContext,
    jboolean jSingleSegment, jboolean jPrintSpecial, jboolean jPrintProgress,
    jboolean jTokenTimestamps, jfloat jTholdPt, jfloat jTholdPtsum, jint jMaxLen, jboolean jSplitOnWord, jint jMaxTokens,
    jboolean jTdrzEnable,
    jstring jSuppressRegex, jstring jInitialPrompt,
    jlong jPromptTokens, jint jPromptNTokens, jstring jLanguage, jboolean jDetectLanguage,
    jboolean jSuppressBlank, jboolean jSuppressNonSpeechTokens,
    jfloat jTemperature, jfloat jMaxInitialTs, jfloat jLengthPenalty,
    jfloat jTemperatureInc, jfloat jEntropyThold, jfloat jLogprobThold,
    jint jGreedyBestOf, jint jBeamSize, jfloat jBeamPatience,
    jlong jNewSegmentCallback, jlong jProgressCallback) {

    struct whisper_full_params *params = malloc(sizeof(struct whisper_full_params));
    if (params == NULL) {
        return 0;
    }

    const char *strategy = (*env)->GetStringUTFChars(env, jStrategy, NULL);
    if (strcmp(strategy, "WHISPER_SAMPLING_GREEDY") == 0) {
        params->strategy = WHISPER_SAMPLING_GREEDY;
    } else if (strcmp(strategy, "WHISPER_SAMPLING_BEAM_SEARCH") == 0) {
        params->strategy = WHISPER_SAMPLING_BEAM_SEARCH;
    } else {
        params->strategy = WHISPER_SAMPLING_GREEDY;
    }
    (*env)->ReleaseStringUTFChars(env, jStrategy, strategy);

    // Assigning integer and boolean values directly
    params->n_threads = jNThreads;
    params->n_max_text_ctx = jNMaxTextCtx;
    params->offset_ms = jOffsetMs;
    params->duration_ms = jDurationMs;
    params->translate = jTranslate;
    params->no_context = jNoContext;
    params->single_segment = jSingleSegment;
    params->print_special = jPrintSpecial;
    params->print_progress = jPrintProgress;
    params->token_timestamps = jTokenTimestamps;
    params->thold_pt = jTholdPt;
    params->thold_ptsum = jTholdPtsum;
    params->max_len = jMaxLen;
    params->split_on_word = jSplitOnWord;
    params->max_tokens = jMaxTokens;
    params->tdrz_enable = jTdrzEnable;

    // Handling strings
    const char *suppressRegex = (*env)->GetStringUTFChars(env, jSuppressRegex, NULL);
    params->suppress_regex = strdup(suppressRegex); // strdup allocates memory, remember to free it later
    (*env)->ReleaseStringUTFChars(env, jSuppressRegex, suppressRegex);

    const char *initialPrompt = (*env)->GetStringUTFChars(env, jInitialPrompt, NULL);
    params->initial_prompt = strdup(initialPrompt);
    (*env)->ReleaseStringUTFChars(env, jInitialPrompt, initialPrompt);

    // Assuming prompt_tokens is previously allocated and its pointer is passed as long
    params->prompt_tokens = (const whisper_token *) jPromptTokens;
    params->prompt_n_tokens = jPromptNTokens;

    const char *language = (*env)->GetStringUTFChars(env, jLanguage, NULL);
    params->language = strdup(language);
    (*env)->ReleaseStringUTFChars(env, jLanguage, language);

    params->detect_language = jDetectLanguage;
    params->suppress_blank = jSuppressBlank;
    params->suppress_non_speech_tokens = jSuppressNonSpeechTokens;

    // Floating-point parameters
    params->temperature = jTemperature;
    params->max_initial_ts = jMaxInitialTs;
    params->length_penalty = jLengthPenalty;
    params->temperature_inc = jTemperatureInc;
    params->entropy_thold = jEntropyThold;
    params->logprob_thold = jLogprobThold;

    // Nested struct initializations
    params->greedy.best_of = jGreedyBestOf;
    params->beam_search.beam_size = jBeamSize;
    params->beam_search.patience = jBeamPatience;

    // Handling callbacks and user data
    params->new_segment_callback = (whisper_new_segment_callback) jNewSegmentCallback;
    params->progress_callback = (whisper_progress_callback) jProgressCallback;

    return (jlong) params;
}

static jobject gCallbackObject = NULL;
static jmethodID gCallbackMethodID = NULL;

void cWhisperNewSegmentCallback(struct whisper_context * ctx, struct whisper_state * state, int n_new, void * user_data) {
    JNIEnv *env;
    (*gJvm)->AttachCurrentThread(gJvm, (void**)&env, NULL);
    jlong ctxPointer = (jlong)ctx;
    jlong statePointer = (jlong)state;
    (*env)->CallVoidMethod(env, gCallbackObject, gCallbackMethodID, ctxPointer, statePointer, n_new);
    (*gJvm)->DetachCurrentThread(gJvm);
}

JNIEXPORT jlong JNICALL Java_io_vacco_whisper_Wp_registerNewSegmentCallback(JNIEnv *env, jclass clazz, jobject callback) {
    if (callback == NULL) {
        return (jlong)NULL;
    }
    gCallbackObject = (*env)->NewGlobalRef(env, callback);
    jclass callbackClass = (*env)->GetObjectClass(env, callback);
    gCallbackMethodID = (*env)->GetMethodID(env, callbackClass, "onNewSegment", "(JJJ)V");
    return (jlong) &cWhisperNewSegmentCallback;
}

static jobject gProgressCallbackObject = NULL;
static jmethodID gProgressCallbackMethodID = NULL;

void cWhisperProgressCallback(struct whisper_context * ctx, struct whisper_state * state, int progress, void * user_data) {
    JNIEnv *env;
    (*gJvm)->AttachCurrentThread(gJvm, (void**) &env, NULL);
    jlong ctxPointer = (jlong) ctx;
    jlong statePointer = (jlong) state;
    (*env)->CallVoidMethod(env, gProgressCallbackObject, gProgressCallbackMethodID, ctxPointer, statePointer, progress);
    (*gJvm)->DetachCurrentThread(gJvm);
}

JNIEXPORT jlong JNICALL Java_io_vacco_whisper_Wp_registerProgressCallback(JNIEnv *env, jclass clazz, jobject callback) {
    if (callback == NULL) {
        return (jlong)NULL;
    }
    gProgressCallbackObject = (*env)->NewGlobalRef(env, callback);
    jclass callbackClass = (*env)->GetObjectClass(env, callback);
    gProgressCallbackMethodID = (*env)->GetMethodID(env, callbackClass, "onProgress", "(JJI)V");
    return (jlong) &cWhisperProgressCallback;
}

JNIEXPORT void JNICALL Java_io_vacco_whisper_Wp_clearGlobalReferences(JNIEnv *env, jclass clazz) {
    if (gCallbackObject != NULL) {
        (*env)->DeleteGlobalRef(env, gCallbackObject);
        gCallbackObject = NULL;
    }
    if (gProgressCallbackObject != NULL) {
        (*env)->DeleteGlobalRef(env, gProgressCallbackObject);
        gProgressCallbackObject = NULL;
    }
}