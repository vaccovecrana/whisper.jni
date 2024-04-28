package io.vacco.whisper;

public interface WpProgressCallback {
  void onProgress(long contextPointer, long statePointer, int progress);
}
