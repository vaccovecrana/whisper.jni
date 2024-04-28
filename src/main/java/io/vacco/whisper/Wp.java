package io.vacco.whisper;

public class Wp {

  public static void initNative() {
    var os = String.format("%s-%s", System.getProperty("os.name"), System.getProperty("os.arch"));
    switch (os) {
      case "Linux-amd64":
        WpNative.loadLibraryFromJar("/io/vacco/whisper/libwhisperjni.so");
        break;
      default:
        var msg = String.format("No native binaries available for [%s]. PRs are welcome :)", os);
        throw new UnsupportedOperationException(msg);
    }
  }

  public static native long initWhisper(String modelPath, boolean useGpu, int gpuDevice,
                                        boolean dtwTokenTimestamps, String dtwAheadsPreset);

  public static native void freeWhisper(long contextPointer);

  public static native long createWhisperFullParams(
      String strategy,
      int nThreads, int nMaxTextCtx, int offsetMs, int durationMs,
      boolean translate, boolean noContext, boolean singleSegment,
      boolean printSpecial, boolean printProgress, boolean tokenTimestamps,
      float tholdPt, float tholdPtsum, int maxLen,
      boolean splitOnWord, int maxTokens, boolean tdrzEnable,
      String suppressRegex, String initialPrompt,
      long promptTokens, int promptNTokens, String language, boolean detectLanguage,
      boolean suppressBlank, boolean suppressNonSpeechTokens,
      float temperature, float maxInitialTs, float lengthPenalty,
      float temperatureInc, float entropyThold, float logprobThold,
      int greedyBestOf, int beamSize, float beamPatience,
      long newSegmentCallback, long progressCallback
  );

  public static native long registerNewSegmentCallback(WpNewSegmentCallback callback);
  public static native long registerProgressCallback(WpProgressCallback callback);

  public static native void clearGlobalReferences();

}